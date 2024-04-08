using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;

namespace middleSafeServer.SK.Projects
{
    public class ProjectAlreadyExistsException : BusinessException
    {
        public ProjectAlreadyExistsException(string name) : base(middleSafeServerDomainErrorCodes.ProjectAlreadyExists) {
            WithData("name", name);
        } 
    }
}
