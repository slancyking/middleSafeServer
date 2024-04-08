using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.InfoAgents
{
    public class InfoAgentAlreadyExistsException : BusinessException
    {
        public InfoAgentAlreadyExistsException(string name) : base(middleSafeServerDomainErrorCodes.InfoAgentAlreadyExists) {
            WithData("name", name);
        } 
    }
}
