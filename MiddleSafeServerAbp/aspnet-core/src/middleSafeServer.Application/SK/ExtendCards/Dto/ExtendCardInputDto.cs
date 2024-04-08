using middleSafeServer.SK.Cards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.ExtendCards.Dto
{
    /// <summary>
    /// 外部卡密 更新 输入实体
    /// </summary>
    public class ExtendCardInputDto
    {
        /// <summary>
        /// 索引
        /// </summary>
        public Guid Id { get; set; }

        /// <summary>
        /// 卡密
        /// </summary>
        public string Password { get; set; }
         
        /// <summary>
        /// 所属用户
        /// </summary>
        public Guid UserId { get; set; }

        /// <summary>
        /// 用户名
        /// </summary> 
        public string UserName { get; set; }

        /// <summary>
        /// 所属项目名
        /// </summary>
        public string ProjectName { get; set; }

        /// <summary>
        /// 所属分支名
        /// </summary>
        public string BranchName { get; set; }

        /// <summary>
        /// 卡密状态
        /// </summary>
        public CardStatus Status { get; set; }

        /// <summary>
        /// 备注
        /// </summary>
        public string Remark { get; set; }
    }
}
