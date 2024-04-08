
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Cards
{

    /// <summary>
    /// 更新卡密实体InputDto
    /// </summary>
    public class UpdateCardDto
    {

        /// <summary>
        /// 卡密
        /// </summary>
        public string Password { get; set; }

        /// <summary>
        /// 天数
        /// </summary>
        [Required]
        [Range(1, AppConsts.CreateCardMaxDay)]
        public int Days { get; set; }

        /// <summary>
        /// 卡密状态
        /// </summary>
        [Required]
        [Range(0, (int)CardStatus._COUNT - 1)]
        public CardStatus Status { get; set; }

        /// <summary>
        /// 备注
        /// </summary>
        [StringLength(512)]
        public string Remark { get; set; }

        /// <summary>
        /// 邮件
        /// </summary>
        [Required]
        [EmailAddress]
        [StringLength(AppConsts.MaxEmailAddressLength)]
        public string Mail { get; set; }
        /// <summary>
        /// 手机
        /// </summary>
        [Required]
        [Phone]
        [StringLength(AppConsts.MaxPhoneNumberLength)]
        public string Phone { get; set; }


        /// <summary>
        /// 过期时间
        /// </summary>
        public DateTime ExpiredTime { get; set; }

        /// <summary>
        /// 启用邮件通知
        /// </summary>
        public bool EnableMail { get; set; }

        /// <summary>
        /// 启用手机短信通知
        /// </summary>
        public bool EnablePhoneMsg { get; set; }

        /// <summary>
        /// 计费模式
        /// </summary>
        public CardChargingMode ChargingMode { get; set; }

    }
}
