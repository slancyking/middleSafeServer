using System.Linq; 
using System.Linq.Dynamic.Core; 
using Microsoft.AspNetCore.Http; 
using System;
using System.Collections.Generic;
using System.Threading.Tasks; 

 
using middleSafeServer.IRepository;
using middleSafeServer.SK.PropCollects.Dto;
using middleSafeServer.util;
using Volo.Abp.Application.Dtos;
using Volo.Abp;
using Microsoft.AspNetCore.Authorization;
using middleSafeServer.Permissions;
using Volo.Abp.Users;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.CommonDto;

namespace middleSafeServer.SK.PropCollects
{
    /// <summary>
    /// 物品信息收集
    /// </summary>
    public class PropCollectionAppService : middleSafeServerAppService, IPropCollectionAppService
    {
        private IHttpContextAccessor _accessor;
        private readonly IInputformRepository _inputformRepository;
        private readonly IPropCollectionRepository _propCollectRepository;

        private readonly ICardRepository _cardRepository; 
        private readonly ICurrentUser _currentUser;
        private readonly CardManager _cardManager;

        /// <summary>
        /// 构造
        /// </summary>
        public PropCollectionAppService(IHttpContextAccessor accessor,
            IPropCollectionRepository propCollectRepository,
            IInputformRepository inputformRepository,
            ICardRepository cardRepository, 
            ICurrentUser currentUser,
            CardManager cardManager
            ) {
            this._propCollectRepository = propCollectRepository;
            this._inputformRepository = inputformRepository;
            this._accessor = accessor;
            this._cardRepository = cardRepository; 
            this._currentUser = currentUser;
            this._cardManager = cardManager;
        }

        /// <summary>
        /// 创建一条记录
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [AllowAnonymous]
        public async Task<CardClientOuputDto<CardCommonOutputDto>> CreateSync(CardClientInputDto<CreatePropCollectionInput> input)
        {
            if (!string.IsNullOrWhiteSpace(input.Password))
            {
                SK.Cards.Card _card = await _cardRepository.FindAsync(c => c.Password == input.Password.Trim());
                if (_card == null)
                    return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Info = "卡密异常" }, null);

                var param = input.getParam(_card.RsaPrivateKey);
                if (param == null)
                    return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Info = "参数异常" }, _card.RsaPrivateKey);

                if (param.bCheckTimeout())
                    return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Info = "请求超时" }, _card.RsaPrivateKey);

                CardLoginStatus loginStatus = _cardManager.CheckCardLogin(_card, param.Token);
                if (loginStatus != CardLoginStatus.loginSuccess)
                    return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Info = "登陆状态异常" }, _card.RsaPrivateKey);
                 
                var _prop = ObjectMapper.Map<CreatePropCollectionInput, PropCollect>(param);
                _prop.setId(GuidGenerator.Create());
                _prop.IP = HttpContextExtension.GetUserIp(this._accessor.HttpContext);
                _prop.CardId = _card.Id;
                await _propCollectRepository.InsertAsync(_prop);
                  
                return new CardClientOuputDto<CardCommonOutputDto>(new CardCommonOutputDto() { Info = "操作成功" }, _card.RsaPrivateKey);
            } 
            return null; 
        }

        /// <summary>
        /// 根据时间段查询产量详情
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.PropCollectQuery)]
        public async Task<PagedResultDto<QueryDetailOutput>> QueryPropList(QueryDetailInput input)
        {
            if (
                input.QueryStartTime != null
                && input.QueryEndTime != null
                && input.QueryStartTime > DateTime.MinValue
                && input.QueryEndTime > DateTime.MinValue
                && input.QueryStartTime >= input.QueryEndTime
                )
            {
                throw new UserFriendlyException("查询时间异常");
            }

            //记录查询
            _inputformRepository.CreateFromObject<QueryDetailInput>(_currentUser.GetId(), AppConsts.QueryName_Detail, input);

            var Result = await _propCollectRepository.GetPropCollectList(input);
            var QueryCount = Result.Count();
            var PropCollects = Result.OrderBy(input.Sorting).PageBy(input).ToList();

            var QueryResult = ObjectMapper.Map<List<PropCollect>, List<QueryDetailOutput>>(PropCollects);
            return new PagedResultDto<QueryDetailOutput>(QueryCount, QueryResult);
        }


        /// <summary>
        /// 根据时间段查询每日产量
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.PropCollectQuery)]
        public async Task<PagedResultDto<QueryEveryDayOutput>> QueryByEveryDay(QueryEveryDayInput input)
        {
            if (
                input.QueryStartTime != null
                && input.QueryEndTime != null
                && input.QueryStartTime >= DateTime.MinValue
                && input.QueryEndTime >= DateTime.MinValue
                && input.QueryStartTime >= input.QueryEndTime
                )
            {
                throw new UserFriendlyException("查询的结束时间小于起始时间");
            }

            //记录查询
            _inputformRepository.CreateFromObject<QueryEveryDayInput>(_currentUser.GetId(), AppConsts.QueryName_Everyday, input);

            var Result = (from p in await _propCollectRepository.GetPropCollectList(input)
                                group p by new
                                {
                                    //ProjectName = p.Branch.LinkProject.Name,
                                    //BranchName = p.Branch.Name,
                                    PropName = p.PropName,
                                    ShowTime = p.CreationTime.Date
                                }
            into s
                                select new
                                {
                                    //ProjectName = s.Select(i => i.Branch.LinkProject.Name).First(),
                                    //BranchName = s.Select(i => i.Branch.Name).First(),
                                    PropName = s.Select(i => i.PropName).First(),
                                    ShowTime = s.Select(i => i.CreationTime.Date).First(),
                                    PropNum = s.Sum(i => i.PropNum)
                                }).OrderBy(input.Sorting).ToList();

             
            var QueryCount = Result.Count;
            var PropCollects = Result.Skip(input.SkipCount).Take(input.MaxResultCount);

            return new PagedResultDto<QueryEveryDayOutput>(QueryCount, (IReadOnlyList<QueryEveryDayOutput>)PropCollects);
        }


        /// <summary>
        /// 查询得到图表数据
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.PropCollectQuery)]
        public async Task<List<PropProjectOutputDto>> GetProjectTableinfo(QueryProjectTableInputDto input)
        {
            if (
                input.QueryStartTime != null
                && input.QueryEndTime != null
                && input.QueryStartTime >= DateTime.MinValue
                && input.QueryEndTime >= DateTime.MinValue
                && input.QueryStartTime >= input.QueryEndTime
                )
            {
                throw new UserFriendlyException("查询的结束时间小于起始时间");
            }


            List<PropProjectOutputDto> Queryresult = new();

            //记录查询
            _inputformRepository.CreateFromObject<QueryProjectTableInputDto>(_currentUser.GetId(), AppConsts.QueryName_Everyday, input);

            //初始化 项目名-分支名-物品名  结构
            var Result = (from p in await _propCollectRepository.GetPropCollectList(input)
                               group p by new
                               {
                                   //ProjectName = p.Branch.LinkProject.Name,
                                   //BranchName = p.Branch.Name,
                                   propname = p.PropName,
                                   showtime = p.CreationTime.Date
                               } into s
                               select new
                               {
                                   //ProjectName = s.Select(i => i.Branch.LinkProject.Name).First(),
                                   //BranchName = s.Select(i => i.Branch.Name).First(),
                                   PropName = s.Select(i => i.PropName).First(),
                                   ShowTime = s.Select(i => i.CreationTime.Date).First(),
                                   PropNum = s.Sum(i => i.PropNum)
                               }).OrderBy(s => s.ShowTime).ToList();

            //foreach (var item in Result)
            //{
            //    var project = Queryresult.FirstOrDefault(i => i.ProjectName == item.ProjectName);
            //    if (project == null)
            //    {
            //        project = new PropProjectOutputDto()
            //        {
            //            ProjectName = item.ProjectName
            //        };
            //        Queryresult.Add(project);
            //    }

            //    var subproject = project.SubList.FirstOrDefault(s => s.ProjectSubName == item.BranchName);
            //    if (null == subproject)
            //    {
            //        subproject = new PropBranchOutputDto() { ProjectSubName = item.BranchName, StartTime = item.ShowTime, StartTimeStr = item.ShowTime.ToShortDateString(), LastTime = item.ShowTime, LastTimeStr = item.ShowTime.ToShortDateString() };
            //        project.SubList.Add(subproject);
            //    }

            //    var propinfo = subproject.PropList.FirstOrDefault(s => s.PropName == item.PropName);
            //    if (null == propinfo)
            //    {
            //        propinfo = new PropItemOutputDto() { PropName = item.PropName };
            //        subproject.PropList.Add(propinfo);
            //    }

            //    subproject.LastTime = item.ShowTime;
            //    subproject.LastTimeStr = item.ShowTime.ToShortDateString();
            //    subproject.DaysCount = (subproject.LastTime - subproject.StartTime).Days + 1;


            //    propinfo.ShowTime.Add(item.ShowTime.ToShortDateString());
            //    propinfo.PropNum.Add(item.PropNum);

            //} 


            return Queryresult;
        }
    }
}
