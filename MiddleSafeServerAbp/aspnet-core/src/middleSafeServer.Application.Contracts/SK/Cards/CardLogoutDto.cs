using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Cards
{
    public class CardLogoutDto : CardClientRequstBase
    { 
        /// <summary>
        /// 登陆凭证
        /// </summary>
        public string Token { get; set; }
    }
}
