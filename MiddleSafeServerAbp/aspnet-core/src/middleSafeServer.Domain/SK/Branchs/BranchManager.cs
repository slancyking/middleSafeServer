using JetBrains.Annotations;
using middleSafeServer.SK.Projects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Domain.Services;

namespace middleSafeServer.SK.Branchs
{
    public class BranchManager : DomainService
    {
        private readonly IBranchRepository _branchRepository;
        private readonly IProjectRepository _projectRepository;

        public BranchManager(IBranchRepository branchRepository, IProjectRepository projectRepository) {
            _branchRepository = branchRepository;
            _projectRepository = projectRepository;
        }


        public async Task<Branch> CreateAsync(
            [NotNull] string name,
            [NotNull] Guid projectId,
            [NotNull] bool isOpen,
            [CanBeNull] string remark = null)
        {
            Check.NotNullOrWhiteSpace(name, nameof(name));

            var project = await _projectRepository.FindAsync(projectId);
            if (project == null) {
                throw new ProjectAlreadyDeleteException(projectId.ToString());
            }


            var existingAuthor = await _branchRepository.FindByNameAsync(name);
            if (existingAuthor != null)
            {
                throw new BranchAlreadyExistsException(name);
            }

            return new Branch(
                GuidGenerator.Create(),
                name,
                projectId,
                isOpen,
                remark
            );
        }


        public async Task ChangeProjectAsync([NotNull] Branch branch, [NotNull] Guid projectId ) {
            Check.NotNull(branch, nameof(branch)); 
            var project = await _projectRepository.FindAsync(projectId);
            if (project == null)
                throw new ProjectAlreadyDeleteException(projectId.ToString());
            branch.ProjectId = projectId; 
        }


        public async Task ChangeNameAsync(
            [NotNull] Branch branch,
            [NotNull] string newName)
        {
            Check.NotNull(branch, nameof(branch));
            Check.NotNullOrWhiteSpace(newName, nameof(newName));

            var existingBranch = await _branchRepository.FindByNameAsync(newName);
            if (existingBranch != null && existingBranch.Id != branch.Id)
            {
                throw new BranchAlreadyExistsException(newName);
            }

            branch.ChangeName(newName);
        }

    }
}
