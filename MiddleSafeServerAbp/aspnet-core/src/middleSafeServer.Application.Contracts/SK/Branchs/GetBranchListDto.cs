
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.Branchs
{
    /// <summary>
    /// 获取分支分页 输入实体
    /// </summary>
    public class GetBranchListDto : PagedAndSortedResultRequestDto
    {
        /// <summary>
        /// 项目id
        /// </summary>
        public Guid? _projectId { get; set; }

        /// <summary>
        /// 关键字
        /// </summary>
        public string Filter { get; set; }
    }
}
