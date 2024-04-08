using System;
using System.Collections.Generic;
using System.Text;

namespace middleSafeServer.SK.CommonDto
{
    /// <summary>
    /// 客户端请求基类
    /// </summary>
    public class CardClientRequstBase
    {
        /// <summary>
        /// 客户端请求超时时间,单位秒
        /// </summary>
        private const int CardClientRequestTimeOut = 60;

        /// <summary>
        /// 请求时间
        /// </summary>
        public int PostUnix { get; set; }

        /// <summary>
        /// 检测是否超时,超时返回真
        /// </summary>
        /// <returns></returns>
        public bool bCheckTimeout() {  
            var pTime = DateTimeOffset.FromUnixTimeSeconds(PostUnix).DateTime.ToLocalTime(); 
            return pTime.AddSeconds(CardClientRequestTimeOut) < DateTime.Now;
        }

    }
}
