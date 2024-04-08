
using middleSafeServer.IRepository;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.PropCollects.Dto
{
    /// <summary>
    /// 查询每日物品统计请求结构
    /// </summary>
    public class QueryEveryDayInput : QueryPropCollectInputCommon, IPagedResultRequest, ISortedResultRequest
    {
        /// <summary>
        /// 排序字段
        /// </summary>
        public string Sorting { get; set; }

        /// <summary>
        /// 最大返回结果数目
        /// </summary>
        [Range(1, AppConsts.MaxPageSize)]
        public int MaxResultCount { get; set; }

        /// <summary>
        /// 跳过条目
        /// </summary>
        [Range(0, int.MaxValue)]
        public int SkipCount { get; set; }

        /// <summary>
        /// 支持分页的InputDto
        /// </summary>
        public QueryEveryDayInput()
        {
            MaxResultCount = AppConsts.DefaultPageSize;
            Sorting = "ProjectName";
        }
    }
}
