using middleSafeServer.SK.CommonDto;
using System.ComponentModel.DataAnnotations;

namespace middleSafeServer.SK.NetworkAddressPool.IpLogs
{
    /// <summary>
    /// 中间报告输入实体
    /// </summary>
    public class IpLogInputDto : CardClientRequstBase
    {
        /// <summary>
        /// ip地址
        /// </summary>
        public string IpAddress { get; set; }

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
         
        /// <summary>
        /// 卡密登陆凭证
        /// </summary>
        [Required]
        [MaxLength(128)]
        public string Token { get; set; }
    }
}
