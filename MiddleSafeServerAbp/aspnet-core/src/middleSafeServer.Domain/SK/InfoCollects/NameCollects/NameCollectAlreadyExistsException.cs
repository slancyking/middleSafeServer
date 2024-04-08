using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.InfoCollects.ImageCollects
{
    public class NameCollectAlreadyExistsException : BusinessException
    {
        public NameCollectAlreadyExistsException(string name,string agentName) : base(middleSafeServerDomainErrorCodes.NameCollectAlreadyExists)
        {
            WithData("name", name);
            WithData("agentName", agentName);
        }
    }
}
