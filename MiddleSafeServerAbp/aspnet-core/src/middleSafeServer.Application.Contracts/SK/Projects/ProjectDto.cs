
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.Projects
{
    /// <summary>
    /// 项目 输出实体
    /// </summary> 
    public class ProjectDto: AuditedEntityDto<Guid>
    {   
        /// <summary>
        /// 项目名
        /// </summary>
        public string Name { get; set; }
        /// <summary>
        /// 每个ip最多几个用户使用
        /// </summary>
        public int IpMaxUserCount { get; set; }
        /// <summary>
        /// 项目备注
        /// </summary>
        public string Remark { get; set; }
    }
}
