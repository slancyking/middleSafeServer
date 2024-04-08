using JetBrains.Annotations;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Domain.Services;

namespace middleSafeServer.SK.Projects
{
    public class ProjectsManager : DomainService
    {
        private readonly IProjectRepository  _projectRepository;


        public ProjectsManager(IProjectRepository projectRepository) {
            _projectRepository = projectRepository;
        }


        public async Task<Project> CreateAsync(
            [NotNull] string name, [NotNull] int ipMaxUserCount,
            [CanBeNull] string remark = null)
        {
            Check.NotNullOrWhiteSpace(name, nameof(name));

            var existingAuthor = await _projectRepository.FindByNameAsync(name);
            if (existingAuthor != null)
            {
                throw new ProjectAlreadyExistsException(name);
            }

            return new Project(
                GuidGenerator.Create(),
                name, ipMaxUserCount,
                remark
            );
        }


        public async Task ChangeNameAsync(
            [NotNull] Project project,
            [NotNull] string newName)
        {
            Check.NotNull(project, nameof(project));
            Check.NotNullOrWhiteSpace(newName, nameof(newName));

            var existingProject = await _projectRepository.FindByNameAsync(newName);
            if (existingProject != null && existingProject.Id != project.Id)
            {
                throw new ProjectAlreadyExistsException(newName);
            }

            project.ChangeName(newName);
        }

    }
}
