using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 卡密登陆输入实体
    /// </summary>
    public class CardLoginInputDto
    {

        /// <summary>
        /// 分支id
        /// </summary>
        [Required]
        public Guid BranchId { get; set; }

        /// <summary>
        /// 卡密
        /// </summary>
        [Required]
        public string CardPassword { get; set; }
         
    }
}
