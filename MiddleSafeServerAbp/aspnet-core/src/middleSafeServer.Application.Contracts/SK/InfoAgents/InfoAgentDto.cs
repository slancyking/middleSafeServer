 
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
    /// 项目分支 输出实体
    /// </summary   
    public class InfoAgentDto : EntityDto<Guid>
    { 

        /// <summary>
        /// 创建时间
        /// </summary>
        public DateTime CreationTime { get; set; }

        /// <summary>
        /// 是否启用
        /// </summary>
        public bool IsOpen { get; set; }

        /// <summary>
        /// 项目分支名
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 项目备注
        /// </summary>
        public string Description { get; set; }
    }
}
