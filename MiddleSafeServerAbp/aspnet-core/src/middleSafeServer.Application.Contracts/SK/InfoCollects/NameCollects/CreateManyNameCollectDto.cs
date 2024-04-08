using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class CreateManyNameCollectDto : CardClientRequstBase
    {
        public List<CreateNameCollectDto> NameCollects { get; set; }


        /// <summary>
        /// 卡密登陆凭证
        /// </summary>
        [Required]
        [MaxLength(128)]
        public string Token { get; set; }

    }
}
