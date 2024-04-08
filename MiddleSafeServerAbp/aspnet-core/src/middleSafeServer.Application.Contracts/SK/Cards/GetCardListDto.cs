
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 查询物品列表InputDto
    /// </summary>
    public class GetCardListDto : PagedAndSortedResultRequestDto
    {
        /// <summary>
        /// 过滤字符
        /// </summary>
        public string Filter { get; set; }
         
        /// <summary>
        /// 创建人用户ID
        /// </summary>
        public Guid? CreatorId { get; set; }

        /// <summary>
        /// 分支id
        /// </summary>
        public Guid? BranchId { get; set; }
         
        /// <summary>
        /// 邮件地址
        /// </summary>
        public string Mail { get; set; }

        /// <summary>
        /// 手机号码
        /// </summary>
        public string Phone { get; set; }


        /// <summary>
        /// 支持分页的InputDto
        /// </summary>
        public GetCardListDto()
        {
            MaxResultCount = AppConsts.DefaultPageSize;
        }
    }
}
