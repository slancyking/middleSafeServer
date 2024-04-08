using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.Branchs
{
    public class ProjectAlreadyDeleteException : BusinessException
    {
        public ProjectAlreadyDeleteException(string name) : base(middleSafeServerDomainErrorCodes.ProjectAlreadyDelete)
        {
            WithData("name", name);
        }
    }
}
