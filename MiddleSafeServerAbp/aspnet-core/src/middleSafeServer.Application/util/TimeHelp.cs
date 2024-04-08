using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.util
{
    internal class TimeHelp
    {
        //long转DateTime
        internal static DateTime ConvertLongToDateTime(long d)
        {
            return DateTimeOffset.FromUnixTimeSeconds(d).DateTime.ToLocalTime();
        }
        //DateTime类型转成long 
        internal static long ConvertDataTimeToLong(DateTime dt)
        {
            DateTime dtStart = TimeZone.CurrentTimeZone.ToLocalTime(new DateTime(1970, 1, 1));
            TimeSpan toNow = dt.Subtract(dtStart);
            long timeStamp = toNow.Ticks;
            timeStamp = long.Parse(timeStamp.ToString().Substring(0, timeStamp.ToString().Length - 4));
            return timeStamp / 1000;
        } 

    }
}
