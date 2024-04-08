using System.Threading.Tasks;
using Volo.Abp.Application.Services;
using System;

namespace middleSafeServer.SK.WebSettings
{
    public interface IWebSettingAppService : IApplicationService
    {
        Task<GetWebSettingOutputDto> GetWebSettingDef();

        Task UpdateWebSetting(Guid id, UpdateWebSettingInputDto input);
    }
}
