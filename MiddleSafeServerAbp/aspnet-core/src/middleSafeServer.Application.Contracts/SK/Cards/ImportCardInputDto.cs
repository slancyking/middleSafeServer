using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 导入卡密输入
    /// </summary>
    public class ImportCardInputDto
    {
        /// <summary>
        /// 分支id
        /// </summary>
        [Required]
        public Guid BranchId { get; set; }
        /// <summary>
        /// 卡密列表
        /// </summary>
        [Required]
        public string Password { get; set; }

        /// <summary>
        /// 过期时间
        /// </summary>
        [Required]
        public DateTime ExpiredTime { get; set; }

        /// <summary>
        /// 手机号
        /// </summary>
        public string Phone { get; set; }
            
        /// <summary>
        /// 邮箱
        /// </summary>
        public  string Mail { get; set; }
        
        /// <summary>
        /// 备注
        /// </summary>
        public string Remark { get; set; }
    }
}
