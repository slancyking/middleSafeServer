using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.InfoCollects.ImageCollects
{
    public class InfoAgentAlreadyDeleteException : BusinessException
    {
        public InfoAgentAlreadyDeleteException(string name) : base(middleSafeServerDomainErrorCodes.InfoAgentAlreadyDelete)
        {
            WithData("name", name);
        }
    }
}
