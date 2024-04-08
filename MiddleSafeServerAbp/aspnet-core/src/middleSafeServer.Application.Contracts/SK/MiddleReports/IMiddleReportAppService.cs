using middleSafeServer.SK.CommonDto;
using System.Threading.Tasks;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.MiddleReports
{
    public interface IMiddleReportAppService : IApplicationService
    {
        Task<CardClientOuputDto<MiddleReportOutputDto>> NormalReportAsync(CardClientInputDto<MiddleReportInputDto> input);

        Task<CardClientOuputDto<MiddleNomalQueryOutputDto>> NormalQueryAsync(CardClientInputDto<MiddleNomalQueryInputDto> input);

    }
}
