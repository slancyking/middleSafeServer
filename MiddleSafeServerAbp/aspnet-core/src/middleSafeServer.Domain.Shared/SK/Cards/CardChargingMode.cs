using System;
using System.Collections.Generic;
using System.Text;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 卡密计费模式
    /// </summary>
    public enum CardChargingMode : int
    {
        /// <summary>
        ///  开始使用计时不允许暂停
        /// </summary>
        timing = 0,
        /// <summary>
        /// 计时能暂停
        /// </summary>
        timingCanPause = 1,
        /// <summary>
        /// 计时自动暂停
        /// </summary>
        timeingAutoPause = 2,
        /// <summary>
        /// 实时
        /// </summary>
        realTime = 3
    }
}
