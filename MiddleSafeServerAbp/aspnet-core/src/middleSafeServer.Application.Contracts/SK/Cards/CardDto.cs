 
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 单个卡密数据输出实体
    /// </summary> 
    public class CardDto : EntityDto<Guid>
    {
        /// <summary>
        /// 卡密
        /// </summary>
        public string Password { get; set; }

        /// <summary>
        /// 开始使用时间
        /// </summary>
        public DateTime StartTime { get; set; }

        /// <summary>
        /// 天数
        /// </summary>
        public int Days { get; set; }

        /// <summary>
        /// 登陆超时时间
        /// </summary>
        public DateTime LoginOvertime { get; set; }

        /// <summary>
        /// 登陆凭证
        /// </summary>
        public string LoginToken { get; set; }

        /// <summary>
        /// 邮箱地址
        /// </summary>
        public string Mail { get; set; }

        /// <summary>
        /// 手机号
        /// </summary>
        public string Phone { get; set; }

        /// <summary>
        /// 所属项目分支
        /// </summary>
        public Guid BranchId { get; set; }

        /// <summary>
        /// 卡密状态
        /// </summary>
        public CardStatus Status { get; set; }

        /// <summary>
        /// 卡密类型
        /// </summary>
        public CardType Type { get; set; }

        /// <summary>
        /// 备注
        /// </summary>
        public string Remark { get; set; }
         

        /// <summary>
        /// 到期时间
        /// </summary>
        public DateTime ExpiredTime { get; set; }

        /// <summary>
        /// 所属用户
        /// </summary>
        public Guid CreatorId { get; set; }
         
        /// <summary>
        /// 是否登录
        /// </summary>
        public bool IsLogin { get; set; }


        /// <summary>
        /// 启用邮件通知
        /// </summary>
        public bool EnableMail { get; set; }

        /// <summary>
        /// 启用手机短信通知
        /// </summary>
        public bool EnablePhoneMsg { get; set; }

        /// <summary>
        /// 卡密标题
        /// </summary>
        public string Title { get; set; }

        /// <summary>
        /// 计费模式
        /// </summary>
        public CardChargingMode ChargingMode { get; set; }
    }
}
