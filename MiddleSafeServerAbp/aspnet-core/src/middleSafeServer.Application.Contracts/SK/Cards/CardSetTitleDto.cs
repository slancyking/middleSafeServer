using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 获取剩余时间
    /// </summary>
    public class CardSetTitleDto : CardClientRequstBase
    { 
        /// <summary>
        /// 登陆凭证
        /// </summary>
        public string Token { get; set; }
         
        /// <summary>
        /// 标题
        /// </summary>
        public string Title { get; set; }
    }
}
