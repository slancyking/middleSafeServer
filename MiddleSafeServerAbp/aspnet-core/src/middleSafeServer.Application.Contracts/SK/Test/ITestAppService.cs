using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.Test
{
    public interface ITestAppService : IApplicationService
    {
        Task<string> MailEntrypt(string content);

        Task MailTets();

        Task<string> LocalizerTest();

    }
}
