using JetBrains.Annotations;
using middleSafeServer.SK.InfoAgents;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using middleSafeServer.SK.Projects;
using middleSafeServer.util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Domain.Services;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class NameCollectManager : DomainService
    {
        private readonly INameCollectRepository _nameCollectRepository;
        private readonly IInfoAgentRepository _infoAgentRepository;

        public NameCollectManager(INameCollectRepository nameCollectRepository, IInfoAgentRepository infoAgentRepository) {
            _nameCollectRepository = nameCollectRepository;
            _infoAgentRepository = infoAgentRepository;
        }
         
        public async Task<NameCollect> CreateAsync(
            [NotNull] Guid InfoAgentId,
            [NotNull] string name,
            [NotNull] int sex,
             Guid? imageCollectId,
            [NotNull] string headIconUrl,
            [NotNull] string extendJson
            )
        { 
            var infoAgent = await _infoAgentRepository.FindAsync(InfoAgentId);
            if (infoAgent == null)
            {
                throw new InfoAgentAlreadyDeleteException(infoAgent.ToString());
            }

            var existName = await _nameCollectRepository.FindName(name, CommonCrypt.stringToHashNumber(name) , InfoAgentId);
            if (existName != null)
                return null;
             
            return new NameCollect(  GuidGenerator.Create(), InfoAgentId, name, sex, imageCollectId, headIconUrl, extendJson );
        }

        public async Task ChangeInfoAgentAsync([NotNull] NameCollect nameCollect, [NotNull] Guid infoAgentid)
        {
            Check.NotNull(nameCollect, nameof(nameCollect));
            var infoAgent = await _infoAgentRepository.FindAsync(infoAgentid);
            if (infoAgent == null)
            {
                throw new InfoAgentAlreadyDeleteException(infoAgent.ToString());
            }

            var existsName = await _nameCollectRepository.FindName(nameCollect.Name, CommonCrypt.stringToHashNumber(nameCollect.Name), infoAgentid);
            if(existsName != null)
                throw new NameCollectAlreadyExistsException(nameCollect.Name, infoAgent.Name);

            nameCollect.InfoAgentId = infoAgentid;
        }

        public async Task ChangeNameAsync([NotNull] NameCollect nameCollect, [NotNull] string newName)
        {
            Check.NotNull(nameCollect, nameof(nameCollect));

            var infoAgent = await _infoAgentRepository.FindAsync(nameCollect.InfoAgentId);
            if (infoAgent == null)
            {
                throw new InfoAgentAlreadyDeleteException(infoAgent.ToString());
            }

            var existsName = await _nameCollectRepository.FindName(newName, CommonCrypt.stringToHashNumber(newName), nameCollect.InfoAgentId);
            if (existsName != null)
                throw new NameCollectAlreadyExistsException(newName, infoAgent.Name);

            nameCollect.ChangeName(newName);
        }


    }
}
