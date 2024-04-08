using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.ExtendCards.Dto
{
    /// <summary>
    /// 批量创建外部卡, 输入实体
    /// </summary>
    public class CreateExtendCardInputDto
    {
        /// <summary>
        /// 分支id
        /// </summary>
        [Required]
        public Guid? BranchId { get; set; }

        /// <summary>
        /// 外部卡密
        /// </summary>
        [MaxLength(10240)]
        public string ExtendCardStringLines { get; set; }

        /// <summary>
        /// 备注
        /// </summary>
        [MaxLength(512)]
        public string Remark { get; set; }
    }
}
