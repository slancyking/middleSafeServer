
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks; 

namespace middleSafeServer.SK.InfoAgents
{
    /// <summary>
    /// 项目分支 输入 实体
    /// </summary> 
    public class UpdateInfoAgentDto
    { 

        /// <summary>
        /// 项目分支名
        /// </summary>
        [Required]
        [StringLength(SKConsts.MaxNameLength)]
        public string Name { get; set; }

        /// <summary>
        /// 项目分支备注
        /// </summary>
        public string Description { get; set; }
    }
}
