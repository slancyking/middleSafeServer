using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.Cards
{
    internal class CardDaysOutRangeException : BusinessException
    {
        public CardDaysOutRangeException(int days,int maxDays) : base(middleSafeServerDomainErrorCodes.cardDaysOutOfRange)
        {
            WithData("days", days.ToString());
            WithData("MaxDays", maxDays.ToString());
        }
    }
}
