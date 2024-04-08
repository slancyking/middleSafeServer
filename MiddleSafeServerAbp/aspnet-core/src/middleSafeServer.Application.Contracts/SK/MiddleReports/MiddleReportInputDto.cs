using middleSafeServer.SK.CommonDto;
using System.ComponentModel.DataAnnotations;

namespace middleSafeServer.SK.MiddleReports
{
    /// <summary>
    /// 中间报告输入实体
    /// </summary>
    public class MiddleReportInputDto : CardClientRequstBase
    {
        /// <summary>
        /// 服务端的标志位,可以是进程id.之类的
        /// </summary>
        [Required]
        [MaxLength(128)]
        public string Flag { get; set; }

        /// <summary>
        /// 秘钥索引
        /// </summary>
        public int KeyIndex { get; set; }

        /// <summary>
        /// 随机端口
        /// </summary>
        [Required]
        [Range(1, ushort.MaxValue)]
        public int RandomPort { get; set; }

        /// <summary>
        /// 随机秘钥
        /// </summary>
        [Required]
        [MaxLength(128)]
        public string RandomKey { get; set; }
         
          
        /// <summary>
        /// 卡密登陆凭证
        /// </summary>
        [Required]
        [MaxLength(128)]
        public string Token { get; set; }
    }
}
