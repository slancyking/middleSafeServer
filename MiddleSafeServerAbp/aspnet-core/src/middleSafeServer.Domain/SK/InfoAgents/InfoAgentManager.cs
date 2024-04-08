using JetBrains.Annotations;
using middleSafeServer.SK.Projects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Domain.Services;

namespace middleSafeServer.SK.InfoAgents
{
    public class InfoAgentManager : DomainService
    {
        private readonly IInfoAgentRepository _infoAgentRepository;

        public InfoAgentManager(IInfoAgentRepository infoAgentRepository) {
            _infoAgentRepository = infoAgentRepository;
        }


        public async Task<InfoAgent> CreateAsync(
            [NotNull] string name, 
            [NotNull] bool isOpen,
            [CanBeNull] string description = null)
        {
            Check.NotNullOrWhiteSpace(name, nameof(name));
             

            var existingAuthor = await _infoAgentRepository.FindByNameAsync(name);
            if (existingAuthor != null)
            {
                throw new InfoAgentAlreadyExistsException(name);
            }

            return new InfoAgent(
                GuidGenerator.Create(),
                name, 
                isOpen,
                description
            );
        }

          
        public async Task ChangeNameAsync(
            [NotNull] InfoAgent branch,
            [NotNull] string newName)
        {
            Check.NotNull(branch, nameof(branch));
            Check.NotNullOrWhiteSpace(newName, nameof(newName));

            var existingBranch = await _infoAgentRepository.FindByNameAsync(newName);
            if (existingBranch != null && existingBranch.Id != branch.Id)
            {
                throw new InfoAgentAlreadyExistsException(newName);
            }

            branch.ChangeName(newName);
        }

    }
}
