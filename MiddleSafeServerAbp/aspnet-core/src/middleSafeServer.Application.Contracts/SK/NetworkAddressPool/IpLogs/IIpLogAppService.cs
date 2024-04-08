using middleSafeServer.SK.CommonDto;
using System.Threading.Tasks;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.NetworkAddressPool.IpLogs
{
    public interface IIpLogAppService : IApplicationService
    {
        Task<CardClientOuputDto<IpLogInputOutputDto>> TryUseIp(CardClientInputDto<IpLogInputDto> input);

    }
}
