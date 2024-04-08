using middleSafeServer.SK.WebSettings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Data;
using Volo.Abp.DependencyInjection;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.Seed
{
    public class WebSettingDataSeederContributor : IDataSeedContributor, ITransientDependency
    {
        private readonly IRepository<WebSetting, Guid> _webSettingRepository;

        public WebSettingDataSeederContributor(IRepository<WebSetting, Guid> webSettingRepository)
        {

            _webSettingRepository = webSettingRepository;
        }

        public async Task SeedAsync(DataSeedContext context)
        {

            if (await _webSettingRepository.GetCountAsync() <= 0)
            {
                WebSetting defSetting = new WebSetting();
                defSetting.IsMailReportDrop = true;
                defSetting.IsSmsReportDrop = false;
                defSetting.IsSmsReportServiceResource = false;

               await  _webSettingRepository.InsertAsync(defSetting);
            }
        }

    }
}
