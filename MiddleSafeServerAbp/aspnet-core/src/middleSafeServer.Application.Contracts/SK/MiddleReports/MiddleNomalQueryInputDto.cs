using middleSafeServer.SK.CommonDto;
using System.ComponentModel.DataAnnotations;

namespace middleSafeServer.SK.MiddleReports
{
    /// <summary>
    /// 中间 自然查询 输入实体
    /// </summary>
    public class MiddleNomalQueryInputDto : CardClientRequstBase
    {
        /// <summary>
        /// 服务端的标志位,可以是进程id.之类的
        /// </summary>
        [Required]
        [MaxLength(128)]
        public string Flag { get; set; }
           
        /// <summary>
        /// 卡密登陆凭证
        /// </summary>
        [Required]
        [MaxLength(128)]
        public string Token { get; set; }

    }
}
