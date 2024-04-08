using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.Text;

namespace middleSafeServer.SK.Cards
{
    public class CardPauseDto : CardClientRequstBase
    {
        /// <summary>
        /// 登陆凭证
        /// </summary>
        public string Token { get; set; }
    }
}
