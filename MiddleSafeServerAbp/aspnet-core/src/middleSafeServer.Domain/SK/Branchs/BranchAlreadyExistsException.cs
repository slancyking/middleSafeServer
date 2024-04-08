using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.Branchs
{
    public class BranchAlreadyExistsException : BusinessException
    {
        public BranchAlreadyExistsException(string name) : base(middleSafeServerDomainErrorCodes.BranchAlreadyExists) {
            WithData("name", name);
        } 
    }
}
