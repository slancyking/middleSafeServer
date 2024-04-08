using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace middleSafeServer.SK.Projects
{
    /// <summary>
    /// 更新项目输入实体
    /// </summary>
    public class UpdateProjectDto
    {
        /// <summary>
        /// 项目名
        /// </summary>
        [Required]
        [StringLength(SKConsts.MaxNameLength)]
        public string Name { get; set; }
        /// <summary>
        /// 每个ip最多几个用户使用
        /// </summary>
        [Required]
        public int IpMaxUserCount { get; set; }
        /// <summary>
        /// 备注
        /// </summary>
        public string Remark { get; set; }
    }
}
