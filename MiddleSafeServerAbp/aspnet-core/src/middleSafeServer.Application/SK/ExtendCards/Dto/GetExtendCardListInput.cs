
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.ExtendCards.Dto
{
    /// <summary>
    /// 查询外部卡密 输入 实体
    /// </summary>
    public class GetExtendCardListInput : IPagedResultRequest
    {
        /// <summary>
        /// 项目id
        /// </summary>
        public Guid? ProjectId { get; set; }
        /// <summary>
        /// 分支id
        /// </summary>
        public Guid? BranchId { get; set; }


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
        public GetExtendCardListInput()
        {
            MaxResultCount = AppConsts.DefaultPageSize;
        }
    }
}
