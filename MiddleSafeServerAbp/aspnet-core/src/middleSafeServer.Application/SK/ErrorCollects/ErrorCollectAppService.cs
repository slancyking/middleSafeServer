using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using middleSafeServer.Permissions;
using middleSafeServer.SK.Branchs;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.CommonDto;
using middleSafeServer.util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Dynamic.Core;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using System.Globalization;
namespace middleSafeServer.SK.ErrorCollects
{
    [Authorize]
    public class ErrorCollectAppService : middleSafeServerAppService, IErrorCollectAppService
    {
        private readonly IBranchRepository _branchRepository;
        private readonly IErrorCollectRepository _errorCollectRepository;
        private readonly ICardRepository _cardRepository;
        private readonly CardManager _cardManager;
        private IHttpContextAccessor _accessor;

        public ErrorCollectAppService(IErrorCollectRepository errorCollectRepository, ICardRepository cardRepository, CardManager cardManager, IHttpContextAccessor httpContextAccessor , IBranchRepository branchRepository ) { 
            _errorCollectRepository = errorCollectRepository;
            _cardRepository = cardRepository;
            _cardManager = cardManager;
            _accessor = httpContextAccessor;
            _branchRepository = branchRepository;
        }

        /// <summary>
        /// 由卡密客户端创建
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [AllowAnonymous]
        public async Task<CardClientOuputDto<CardCommonOutputDto>> ClientErrorCollectAsync(CardClientInputDto<CreateErrorCollectInputDto> input)
        {
            if (!string.IsNullOrWhiteSpace(input.Password))
            {
                SK.Cards.Card _card = await _cardRepository.FindAsync(c => c.Password == input.Password.Trim());
                if (_card == null)
                    return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Result = -100, Info = "卡密无效" }, null);

                var param = input.getParam(_card.RsaPrivateKey);
                if (param == null)
                    return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Result = -98, Info = "解密异常" }, null);

                if (param.bCheckTimeout())
                    return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Result = -101, Info = "请求超时" }, null);

                CardLoginStatus loginStatus = _cardManager.CheckCardLogin(_card, param.Token);
                if (loginStatus != CardLoginStatus.loginSuccess)
                    return new CardClientOuputDto<CardCommonOutputDto>(
                    new CardCommonOutputDto() { Result = (int)loginStatus, Info = CardLoginStatusString.GetStatusString(loginStatus) },
                    null);

                var ec = new ErrorCollect(GuidGenerator.Create(), _card.BranchId, _card.Id, param.ErrorTitle, param.ErrorMessage, param.BackStackTraceBack, HttpContextExtension.GetUserIp(this._accessor.HttpContext));
                 
                await _errorCollectRepository.InsertAsync(ec);
                 
                return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Result = 0, Info = "操作成功" }, _card.RsaPrivateKey);
            }
            return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Result = -100, Info = "卡密无效" }, null);
        }

        /// <summary>
        /// 后台删除
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.ErrorCollectDelete)]
        public async Task DeleteAsync(Guid id)
        {
            await _errorCollectRepository.DeleteAsync(id);
        }

        /// <summary>
        /// 后台删除相同
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        [Authorize(middleSafeServerPermissions.ErrorCollectDeleteSame)]
        public async Task DeleteSameErrorMessage(Guid id)
        {
            await _errorCollectRepository.DeleteSameErrorById(id);
        }

        /// <summary>
        /// 获取单个
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        [Authorize(middleSafeServerPermissions.ErrorCollectGet)]
        public async Task<ErrorCollectDto> GetAsync(Guid id)
        {
            var errorCollect = await _errorCollectRepository.GetAsync(id);
            if (errorCollect == null)
                return null;

            var errorCollectDto = ObjectMapper.Map<ErrorCollect, ErrorCollectDto>(errorCollect);

            var branch = await _branchRepository.GetAsync(errorCollect.BranchId);
            if (branch != null) {
                errorCollectDto.BranchName = branch.Name;
            } 
            return errorCollectDto;
        }

        /// <summary>
        /// 获取列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        [Authorize(middleSafeServerPermissions.ErrorCollectGetList)]
        public async Task<PagedResultDto<ErrorCollectDto>> GetListAsync(GetErrorCollectListDto input)
        {


            string sortType = NormalizeSorting(input.Sorting);


            var queryable = await _errorCollectRepository.GetQueryableAsync();

            queryable = queryable.WhereIf(!string.IsNullOrWhiteSpace(input.errorTitle), q => q.ErrorTitle.Equals(input.errorTitle));
            queryable = queryable.WhereIf(input.branchId != null, q => q.BranchId.Equals(input.branchId));
            queryable = queryable.WhereIf(!string.IsNullOrWhiteSpace(input.errorMessage), q => q.ErrorMessage.Contains(input.errorMessage));
             
            var query = from errorCollect in queryable
                        join branch in await _branchRepository.GetQueryableAsync() on errorCollect.BranchId equals branch.Id 
                        select new { errorCollect, branch } 
                        ;
            try {
                query = query
                    .OrderBy(sortType) //这 引用 using System.Linq.Dynamic.Core;
                    .Skip(input.SkipCount)
                    .Take(input.MaxResultCount);
                var queryResult = await AsyncExecuter.ToListAsync(query);

                var errorCollectDtos = queryResult.Select(x =>
                {
                    var errorCollectDtos = ObjectMapper.Map<ErrorCollect, ErrorCollectDto>(x.errorCollect);
                    errorCollectDtos.BranchName = x.branch.Name;
                    return errorCollectDtos;
                }).ToList();
                var totalCount = queryable.Count();

                return new PagedResultDto<ErrorCollectDto>(
                    totalCount,
                    errorCollectDtos
                );
            }
            catch(Exception e)
            {
                return null;

            }
            



           

        }

        private static string NormalizeSorting(string sorting)
        { 
              
            if (sorting.IsNullOrEmpty())
            {
                return $"errorCollect.{nameof(ErrorCollectDto.ErrorTitle)}";
            }

            if (sorting.Contains("BranchName")) {
                return $"errorCollect.{nameof(ErrorCollectDto.BranchId)}";
            }

            return $"errorCollect.{sorting.ToPascalCase()}"; 
        }



    }
}
