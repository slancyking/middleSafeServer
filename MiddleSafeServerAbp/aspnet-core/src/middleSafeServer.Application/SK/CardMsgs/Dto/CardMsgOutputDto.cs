
using AutoMapper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.CardMsgs.Dto
{
    /// <summary>
    /// 查询卡密消息 输出实体
    /// </summary>
    [AutoMap(typeof(CardMsg))]
    public class CardMsgOutputDto
    {
        /// <summary>
        /// 消息id
        /// </summary>
        public Guid Id { get; set; }
        /// <summary>
        /// 消息时间
        /// </summary>
        public DateTime CreationTime { get; set; }
        /// <summary>
        /// 所属卡密id
        /// </summary>
        public Guid PersonalCardId { get; set; }
        /// <summary>
        /// 卡密
        /// </summary>
        public string CardPassword { get; set; }
        /// <summary>
        /// 卡密备注
        /// </summary>
        public string CardRemark { get; set; }

        /// <summary>
        /// 已读?
        /// </summary>
        public bool IsRead { get; set; }

        /// <summary>
        /// 消息内容
        /// </summary>
        public string Info { get; set; }
    }
}
