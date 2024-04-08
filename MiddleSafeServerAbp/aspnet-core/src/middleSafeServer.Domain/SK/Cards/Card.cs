using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel.DataAnnotations.Schema;
using Volo.Abp.Domain.Entities;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities.Auditing;
using JetBrains.Annotations;
using Volo.Abp;
using middleSafeServer.util;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 卡密实体
    /// </summary>
    public class Card : FullAuditedAggregateRoot<Guid>
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
        /// 通讯用的私钥,服务器端用
        /// </summary>
        public string RsaPrivateKey { get; set; }

        /// <summary>
        /// 通讯用的公钥,客户端用
        /// </summary>
        public string RsaPublicKey { get; set; }

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
        /// 计费模式
        /// </summary>
        public CardChargingMode ChargingMode { get; set; }

        /// <summary>
        /// 过期时间
        /// </summary>
        public DateTime ExpiredTime { get; set; }

        /// <summary>
        /// 剩余时间 单位秒
        /// </summary>
        public long SurplusSecond { get; set; }

        /// <summary>
        /// 最后心跳时间
        /// </summary>
        public DateTime LastPingTime { get; set; }

        /// <summary>
        /// 是否暂停
        /// </summary>
        public bool IsPause { get; set; }

        /// <summary>
        /// 备注
        /// </summary>
        public string Remark { get; set; }

        /// <summary>
        /// 启用邮件通知
        /// </summary>
        public bool EnableMail { get; set; }

        /// <summary>
        /// 启用手机短信通知
        /// </summary>
        public bool EnablePhoneMsg { get; set; }

        /// <summary>
        /// 抬头,可由客户端 设置
        /// </summary>
        public string Title { get; set; }

        private Card() {

        }

        internal Card(
            CardChargingMode mode,
            DateTime expiredTime,
            Guid id,
            [NotNull] string password,
            [NotNull] DateTime startTime,
            [NotNull] int days,
            [NotNull] Guid branchId,
            [NotNull] CardStatus status,
            [NotNull] CardType type,
            [NotNull] bool enableMail,
            [NotNull] bool enablePhoneMsg,
            [CanBeNull] string phone = null,
            [CanBeNull] string mail = null,
            [CanBeNull] string remark = null
            )
            : base(id)
        {
            SetPassword(password);
            ChargingMode = mode;
            ExpiredTime = expiredTime;
            LoginOvertime = DateTime.MinValue;
            LoginToken = String.Empty;
            StartTime = startTime;
            Days = days;
            SurplusSecond = days * 24 * 3600;
            SetEmail(mail);
            SetPhone(phone);
            BranchId = branchId;
            Status = status;
            Type = type;
            Remark = remark;
            EnableMail = enableMail;
            EnablePhoneMsg = enablePhoneMsg;
            Title = "";
        }


        internal Card ChangePassword([NotNull] string password)
        {
            SetPassword(password);
            return this;
        }


        private void SetPassword([NotNull] string password)
        {
            Password = Check.NotNullOrWhiteSpace(
                password,
                nameof(password),
                maxLength: SKConsts.MaxCardPassword
            );
        }

        internal Card ChangeMail([CanBeNull] string mail)
        {
            SetEmail(mail);
            return this;
        }

        private void SetEmail([CanBeNull] string mail)
        {
            Mail = Check.Length(
                mail,
                nameof(mail),
                maxLength: SKConsts.MaxEmailAddressLength
            );
        }

        internal void ChangeTitle([CanBeNull] string title)
        {
            Title = Check.Length(
                title,
                nameof(title),
                maxLength: SKConsts.MaxEmailAddressLength
            );
        }

        /// <summary>
        /// 可以暂停
        /// </summary>
        /// <returns></returns>
        internal bool canPause() {
            return ChargingMode == CardChargingMode.timingCanPause || ChargingMode == CardChargingMode.timeingAutoPause;
        }
        /// <summary>
        /// 自动暂停
        /// </summary>
        /// <returns></returns>
        internal bool isAutoPause() {
            return ChargingMode == CardChargingMode.timeingAutoPause;
        }


        internal Card ChangePhone([CanBeNull] string phone)
        {
            SetPhone(phone);
            return this;
        }

        private void SetPhone([CanBeNull] string phone)
        {
            Phone = Check.Length(
                phone,
                nameof(phone),
                maxLength: SKConsts.MaxPhoneNumberLength
            );
        }


        internal void AddDays(int days) {
            Days += days;
        }

        internal CardLoginStatus checkLogin([NotNull] string token) {
            if (LoginToken != token)
                return CardLoginStatus.loginStatusLost;
            if (LoginOvertime < DateTime.Now)
                return CardLoginStatus.loginTimeout;
            if (ExpiredTime < DateTime.Now)
                return CardLoginStatus.outofDays;
            if (SurplusSecond <= 0)
                return CardLoginStatus.timeNotEnough;

            return CardLoginStatus.loginSuccess;
        }


        internal CardLoginStatus Login() {

            if (LoginOvertime > DateTime.Now)
                return CardLoginStatus.logined;
            if (Status == CardStatus.TEMPBLOCKED || Status == CardStatus.BLOCKED)
                return CardLoginStatus.binded;

            if (ExpiredTime < DateTime.Now)
                return CardLoginStatus.outofDays;
            if (SurplusSecond <= 0)
                return CardLoginStatus.timeNotEnough;


            if (ChargingMode == CardChargingMode.timing && StartTime == DateTime.MinValue && Status == CardStatus.UNUSE)
            {
                Status = CardStatus.INUSE;
                StartTime = DateTime.Now;
                ExpiredTime = DateTime.Now.AddDays(Days);
                SurplusSecond = Days * 24 * 60 * 60;
            }
            
            LoginToken = Guid.NewGuid().ToString();
            LoginOvertime = DateTime.Now.AddMinutes(SKConsts.CardPingAddTime);
            RSACrypt2.RSAKEY rsaKey = RSACrypt2.GetKey(SKConsts.RSAKeyLength);

            RsaPrivateKey = rsaKey.PrivateKey;
            RsaPublicKey = rsaKey.PublicKey;
            unPause();
            return CardLoginStatus.loginSuccess;
        }


        internal void unPause() {
            if (!IsPause && LastPingTime != DateTime.MinValue)
                SurplusSecond -= (long)(DateTime.Now - LastPingTime).TotalSeconds;

            IsPause = false;
            LastPingTime = DateTime.Now;
        }

        internal void pause() { 
            if (canPause() && !isAutoPause()) {
                LastPingTime = DateTime.MinValue;
                IsPause = true;
            } 
            Logout();
        }

        public bool Logout() {  

            if (isAutoPause()) {
                LastPingTime = DateTime.MinValue;
                IsPause = true;
            } 

            LoginToken = "";
            LoginOvertime = DateTime.Now.AddMinutes(-30); 
            return true;
        }


    }
}
