using middleSafeServer.SK.InfoAgents;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using middleSafeServer.SK.InfoCollects.NameCollects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Data;
using Volo.Abp.DependencyInjection;
using Volo.Abp.Domain.Repositories;
using Volo.Abp.Identity;

namespace middleSafeServer.Seed
{
    public class InfoAgentDataSeederContributor : IDataSeedContributor, ITransientDependency
    {
        private readonly InfoAgentManager _infoAgentManager;
        private readonly IInfoAgentRepository _infoAgentRepository;
        private readonly NameCollectManager _nameCollectManager;
        private readonly INameCollectRepository _nameCollectRepository;

        public InfoAgentDataSeederContributor(InfoAgentManager infoAgentManager, IInfoAgentRepository infoAgentRepository , NameCollectManager nameCollectManager , INameCollectRepository nameCollectRepository )
        {

            _infoAgentManager = infoAgentManager;
            _infoAgentRepository = infoAgentRepository; 
            _nameCollectManager = nameCollectManager;
            _nameCollectRepository = nameCollectRepository;
        }

        public async Task SeedAsync(DataSeedContext context)
        {

            if (await _infoAgentRepository.GetCountAsync() <= 0)
            {
                var proOne = await _infoAgentRepository.InsertAsync(
                    await _infoAgentManager.CreateAsync("测试渠道1", true, "备注111")
                );
                var ProTwo = await _infoAgentRepository.InsertAsync(
                    await _infoAgentManager.CreateAsync("测试渠道2", true, "remark222")
                );

                 
            }
        }
    }
}
