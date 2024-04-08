using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 卡密登陆以及心跳输出
    /// </summary>
    public class CardCommonOutputDto
    {
        /// <summary>
        /// 结果代码
        /// </summary>
        public int Result { get; set; }
        /// <summary>
        /// 信息文本
        /// </summary>
        public string Info { get; set; }
    }
}
