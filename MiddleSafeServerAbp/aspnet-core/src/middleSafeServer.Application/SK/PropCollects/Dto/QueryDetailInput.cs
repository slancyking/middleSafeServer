
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
    public class QueryDetailInput : QueryPropCollectInputCommon, IPagedResultRequest, ISortedResultRequest
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
        public QueryDetailInput()
        {
            MaxResultCount = AppConsts.DefaultPageSize;
            Sorting = "Id";
        }
    }
}
