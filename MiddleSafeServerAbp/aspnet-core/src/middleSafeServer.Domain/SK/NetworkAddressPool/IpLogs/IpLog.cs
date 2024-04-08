using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;

namespace middleSafeServer.SK.NetworkAddressPool.IpLogs
{
    public class IpLog : Entity<Guid>, IHasCreationTime
    {
        /// <summary>
        /// 创建时间
        /// </summary>
        public DateTime CreationTime { get; set; }

        /// <summary>
        /// ip地址
        /// </summary>
        public string IpAddress { get; set; }

        /// <summary>
        /// 记录超时时间
        /// </summary>
        public DateTime ExpireTime { get; set; }

        /// <summary>
        /// 所属卡密
        /// </summary>
        public Guid CardId { get; set; }

        /// <summary>
        /// 所属项目
        /// </summary>
        public Guid ProjectId { get; set; }


        /// <summary>
        /// 记录标志
        /// </summary>
        public string LogMark { get; set; }

        /// <summary>
        /// 国家
        /// </summary>
        public string Nation { get; set; }

        /// <summary>
        /// ip所属省份
        /// </summary>
        public string Province { get; set; }

        /// <summary>
        /// ip所属城市
        /// </summary>
        public string City { get; set; }

        /// <summary>
        /// ip所属区
        /// </summary>
        public string District { get; set; }

        public IpLog(Guid id, string ipAddress, Guid cardId, Guid projectId, string logMark, string nation, string province, string city, string district) : base(id)
        {
            CreationTime = DateTime.Now;
            updateExpireTime();
            this.IpAddress = ipAddress;
            this.CardId = cardId;
            this.ProjectId = projectId;
            this.LogMark = logMark;
            this.Nation = nation;
            this.Province = province;
            this.City = city;
        }

        /// <summary>
        /// 更新过期时间
        /// </summary>
        public void updateExpireTime() {
            ExpireTime = DateTime.Now.AddMinutes(SKConsts.IpLogExpiredTime);
        }

        /// <summary>
        /// 是否过期
        /// </summary>
        /// <returns></returns>
        public bool bExpired() { 
            return (DateTime.Now.Subtract(ExpireTime).TotalSeconds > 0);
        }

    }
}
