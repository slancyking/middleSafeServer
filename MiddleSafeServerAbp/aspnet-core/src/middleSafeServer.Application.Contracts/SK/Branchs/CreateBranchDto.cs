using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Branchs
{
    /// <summary>
    /// 创建项目分支 输入实体
    /// </summary>
    public class CreateBranchDto
    {
        /// <summary>
        /// 项目分支名
        /// </summary>
        [Required]
        [StringLength(SKConsts.MaxNameLength)] 
        public string Name { get; set; }

        /// <summary>
        /// 项目id
        /// </summary>
        [Required]
        public Guid ProjectId { get; set; }

        /// <summary>
        /// 是否启用
        /// </summary>
        [Required]
        public bool IsOpen { get; set; }


        /// <summary>
        /// 项目备注
        /// </summary>
        public string Remark { get; set; }
    }
}
