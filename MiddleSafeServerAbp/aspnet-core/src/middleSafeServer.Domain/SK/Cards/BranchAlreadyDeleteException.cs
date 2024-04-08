using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.Cards
{
    public class BranchAlreadyDeleteException : BusinessException
    {
        public BranchAlreadyDeleteException(string branchId) : base(middleSafeServerDomainErrorCodes.BranchAlreadyDelete)
        {
            WithData("branchId", branchId);
        }
    }
}
