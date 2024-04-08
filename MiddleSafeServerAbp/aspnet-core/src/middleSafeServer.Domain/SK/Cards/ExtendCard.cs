
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;
using Volo.Abp.Users;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 外部卡密
    /// </summary>
    public class ExtendCard : Entity<Guid>, IHasCreationTime
    {
         
        /// <summary>
        /// 卡密
        /// </summary>
        public string Password { get; set; }

        /// <summary>
        /// 创建时间
        /// </summary>
        public DateTime CreationTime { get; set; }

        /// <summary>
        /// 所属用户
        /// </summary>
        public Guid UserId { get; set; }

        /// <summary>
        /// 所属项目分支
        /// </summary>
        public Guid? BranchId { get; set; }
        [ForeignKey("BranchId")]
        public SK.Branchs.Branch LinkBranch { get; set; }
         

        /// <summary>
        /// 卡密状态
        /// </summary>
        public CardStatus Status { get; set; }

        /// <summary>
        /// 备注
        /// </summary>
        public string Remark { get; set; }


        public ExtendCard() {
            this.CreationTime = DateTime.Now;
        }

    }
}
