using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Cards
{
    public class CardLoginOutpuDto
    {
        /// <summary>
        /// 结果
        /// </summary>
        public int Result { get; set; }
        /// <summary>
        /// 信息
        /// </summary>
        public string Info { get; set; }
        /// <summary>
        /// 登陆凭证
        /// </summary>
        public string Token { get; set; }

        /// <summary>
        /// 客户端秘钥
        /// </summary>
        public string TokenEx { get; set; }

        /// <summary>
        /// 强制过期时间Unix时间戳
        /// </summary>
        public long Expired { get; set; }


        /// <summary>
        /// 剩余时间 单位秒
        /// </summary>
        public long SurplusSecond { get; set; }
    }
}
