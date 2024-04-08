using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Cards
{
    public enum CardStatus : int
    {
        /// <summary>
        /// 未启用
        /// </summary>
        UNUSE = 0,
        /// <summary>
        /// 已启用
        /// </summary>
        INUSE,
        /// <summary>
        /// 临时封禁
        /// </summary>
        TEMPBLOCKED,
        /// <summary>
        /// 封禁
        /// </summary>
        BLOCKED,
        /// <summary>
        /// 枚举总数
        /// </summary>
        _COUNT
    }
}
