
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.InfoAgents
{
    /// <summary>
    /// 获取分支分页 输入实体
    /// </summary>
    public class GetInfoAgentListDto : PagedAndSortedResultRequestDto
    { 
        /// <summary>
        /// 关键字
        /// </summary>
        public string Filter { get; set; }
    }
}
