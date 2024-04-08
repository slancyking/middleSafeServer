
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http; 
 
using middleSafeServer.IRepository;
using middleSafeServer.Permissions;
using middleSafeServer.SK.ExtendCards.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Users;

namespace middleSafeServer.SK.ExtendCards
{
    /// <summary>
    /// 外部卡 管理服务
    /// </summary>
    public class ExtendCardAppService : middleSafeServerAppService, IExtendCardAppService
    {
        private IHttpContextAccessor _accessor;
        private readonly IExtendCardRepository _extendCardRepository;
        private readonly ICurrentUser _currentUser;

        /// <summary>
        /// 构造
        /// </summary>
        /// <param name="extendCardRepository"></param>
        /// <param name="accessor"></param>         
        public ExtendCardAppService(IExtendCardRepository extendCardRepository,
            IHttpContextAccessor accessor
            , ICurrentUser currentUser)
        {
            _accessor = accessor;
            _extendCardRepository = extendCardRepository; 
            _currentUser = currentUser;
        }


        /// <summary>
        /// 批量创建
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception> 
        [Authorize(middleSafeServerPermissions.ExtendCardCreate)] 
        public async Task Create(CreateExtendCardInputDto input)
        {
            if (string.IsNullOrWhiteSpace(input.ExtendCardStringLines))
                return; 

            List<string> striparr = input.ExtendCardStringLines.Split(new string[] { "\r\n" }, StringSplitOptions.None).ToList();
            striparr = striparr.Where(s => !string.IsNullOrEmpty(s)).ToList();
            var _userId = _currentUser.GetId();

            List<SK.Cards.ExtendCard> tmpInsert = new List<Cards.ExtendCard>();
            foreach (var strip in striparr) {
                SK.Cards.ExtendCard _c = new SK.Cards.ExtendCard()
                {
                    BranchId = input.BranchId,
                    Password = strip.Trim(),
                    Status = SK.Cards.CardStatus.INUSE,
                    UserId = _userId,
                    Remark = input.Remark
                };
                tmpInsert.Add(_c);  
            }
            await _extendCardRepository.InsertManyAsync(tmpInsert);
        }

        /// <summary>
        /// 获取单个外部卡密
        /// </summary>
        /// <param name="CardId"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        public async Task<ExtendCardOutputDto> GetCard(Guid CardId)
        {
            var extendCard = await _extendCardRepository.GetAsync(CardId);
            return ObjectMapper.Map<SK.Cards.ExtendCard, ExtendCardOutputDto>(extendCard);
        }

        /// <summary>
        /// 更新外部卡密
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        public async Task UpdateCard(ExtendCardInputDto input)
        {
            var extendCard = await _extendCardRepository.GetAsync(input.Id);

            ObjectMapper.Map(input, extendCard);

            var result = _extendCardRepository.UpdateAsync(extendCard);
        }

        /// <summary>
        /// 获取外部卡密列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        public async Task<PagedResultDto<ExtendCardOutputDto>> GetCardList(GetExtendCardListInput input)
        {
            var extendCardList = await _extendCardRepository.GetQueryableAsync();
            extendCardList = extendCardList.WhereIf(input.ProjectId != null, p => p.LinkBranch.ProjectId == input.ProjectId)
                .WhereIf(input.BranchId != null, p => p.BranchId == input.BranchId);

            var m_count = extendCardList.Count();
            extendCardList = extendCardList.PageBy(input);

            return new PagedResultDto<ExtendCardOutputDto>(m_count, ObjectMapper.Map<IQueryable<SK.Cards.ExtendCard>, List<ExtendCardOutputDto>>(extendCardList));
        }
    }
}
