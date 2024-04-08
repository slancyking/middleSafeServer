using AutoMapper;
using middleSafeServer.SK.Cards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.ExtendCards.Dto
{
    /// <summary>
    /// 单个外部卡密数据输出实体
    /// </summary>
    [AutoMap(typeof(ExtendCard))]
    public class ExtendCardOutputDto
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
        /// 创建时间
        /// </summary>
        public DateTime CreationTime { get; set; }
         
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
