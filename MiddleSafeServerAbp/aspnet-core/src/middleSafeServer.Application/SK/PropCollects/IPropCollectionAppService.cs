
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.CommonDto;
using middleSafeServer.SK.PropCollects.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.PropCollects
{
    public interface IPropCollectionAppService : IApplicationService
    {
        /// <summary>
        /// 创建一条记录
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<CardClientOuputDto<CardCommonOutputDto>> CreateSync(CardClientInputDto<CreatePropCollectionInput> input);

        /// <summary>
        /// 查询物品详情列表
        /// </summary>
        /// <param name="input"></param> 
        /// <returns></returns>
        Task<PagedResultDto<QueryDetailOutput>> QueryPropList(QueryDetailInput input);

        /// <summary>
        /// 根据时间段查询每日产量
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<PagedResultDto<QueryEveryDayOutput>> QueryByEveryDay(QueryEveryDayInput input);


        /// <summary>
        /// 获取项目图表数据
        /// </summary>
        /// <returns></returns>
        Task<List<PropProjectOutputDto>> GetProjectTableinfo(QueryProjectTableInputDto input);

    }
}
