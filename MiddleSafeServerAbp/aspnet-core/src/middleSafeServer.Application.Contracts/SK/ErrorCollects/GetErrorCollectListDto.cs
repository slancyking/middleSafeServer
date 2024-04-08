
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.ErrorCollects
{
    /// <summary>
    /// 获取分支分页 输入实体
    /// </summary>
    public class GetErrorCollectListDto : PagedAndSortedResultRequestDto
    {
        /// <summary>
        /// 项目id
        /// </summary>
        public Guid? branchId { get; set; }

        public string errorTitle  { get; set; }
        public string errorMessage { get; set; }
    }
}
