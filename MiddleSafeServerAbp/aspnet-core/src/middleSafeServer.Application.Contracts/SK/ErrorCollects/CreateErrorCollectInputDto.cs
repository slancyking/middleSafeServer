using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace middleSafeServer.SK.ErrorCollects
{
    public class CreateErrorCollectInputDto : CardClientRequstBase
    {
        /// <summary>
        /// 卡密登陆凭证
        /// </summary>
        [Required]
        [MaxLength(128)]
        public string Token { get; set; }

        [Required]
        [MaxLength(128)]
        public string ErrorTitle { get; set; }
        [Required]
        [MaxLength(1024)]
        public string ErrorMessage { get; set; }
        [Required]
        [MaxLength(1024)]
        public string BackStackTraceBack { get; set; }
    }
}
