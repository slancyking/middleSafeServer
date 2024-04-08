using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.InfoCollects.NameCollectCounts
{
    public class NameCollectCountAlreadyExistsException : BusinessException
    {
        public NameCollectCountAlreadyExistsException(string agentId) : base(middleSafeServerDomainErrorCodes.NameCollectCountAlreadyExists)
        { 
            WithData("agentId", agentId);
        }
    }
}
