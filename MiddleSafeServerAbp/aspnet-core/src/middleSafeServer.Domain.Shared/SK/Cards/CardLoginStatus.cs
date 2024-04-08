using System;
using System.Collections.Generic;
using System.Text;

namespace middleSafeServer.SK.Cards
{
    public enum CardLoginStatus : int
    {
        /// <summary>
        /// 大于或等于0时,登陆状态正常
        /// </summary>
        loginSuccess = 0,
        /// <summary>
        /// 登陆状态丢失
        /// </summary>
        loginStatusLost = -1,
        /// <summary>
        /// 登陆超时
        /// </summary>
        loginTimeout = -2,
        /// <summary>
        /// 超出日期
        /// </summary>
        outofDays = -3,
        /// <summary>
        /// 卡密异常
        /// </summary>
        missCard = -4,
        /// <summary>
        /// 已登陆
        /// </summary>
        logined = -5,
        /// <summary>
        /// 卡密暂时被禁用
        /// </summary>
        binded = -6 ,
        /// <summary>
        /// 时间不足
        /// </summary>
        timeNotEnough
    }

    public static class CardLoginStatusString {
        public static string GetStatusString(CardLoginStatus status) {
            switch (status)
            {
                case CardLoginStatus.loginSuccess: 
                    return "登陆状态正常";
                case CardLoginStatus.loginStatusLost: 
                    return "登陆状态丢失";
                case CardLoginStatus.loginTimeout: 
                    return "登陆超时";
                case CardLoginStatus.outofDays: 
                    return "超出日期";
                case CardLoginStatus.missCard: 
                    return "卡密异常";
                case CardLoginStatus.logined: 
                    return "卡密已登陆,5分钟后再试";
                case CardLoginStatus.binded:
                    return "卡密暂时被禁用";
                default: break;
            }
            return "未知异常 " + status.ToString();
        }
    }


}
