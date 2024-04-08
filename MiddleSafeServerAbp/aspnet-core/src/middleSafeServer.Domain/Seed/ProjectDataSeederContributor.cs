using middleSafeServer.SK.Branchs;
using middleSafeServer.SK.Projects;
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
    public class ProjectDataSeederContributor : IDataSeedContributor, ITransientDependency
    {
        private readonly ProjectsManager _projectsManager;
        private readonly IProjectRepository _projectRepository;
        IRepository<Branch, Guid> _branchRepository;

        public ProjectDataSeederContributor(ProjectsManager projectsManager, IProjectRepository projectRepository, IRepository<Branch, Guid> branchRepository) {
            
            _branchRepository = branchRepository;
            _projectsManager = projectsManager;
            _projectRepository = projectRepository;
        }

        public async Task SeedAsync(DataSeedContext context)
        {
  
            if (await _projectRepository.GetCountAsync() <= 0)
            {
                var proOne = await _projectRepository.InsertAsync(
                    await _projectsManager.CreateAsync("测试项目1",2,"备注111")
                );
                var ProTwo = await _projectRepository.InsertAsync(
                    await _projectsManager.CreateAsync("测试项目2",2 ,"remark222")
                );
                 
                await _branchRepository.InsertAsync(
                    new Branch()
                    {
                        Remark = "Test_branch_Remark1",
                        IsOpen = true,
                        ProjectId = proOne.Id,
                        Name = "Branch1"
                    },
                    autoSave: true
                );
                await _branchRepository.InsertAsync(
                    new Branch()
                    {
                        Remark = "Test_branch_Remark2",
                        IsOpen = true,
                        ProjectId = ProTwo.Id,
                        Name = "Branch2"
                    },
                    autoSave: true
                );
                await _branchRepository.InsertAsync(
                    new Branch()
                    {
                        Remark = "Test_branch_Remark3",
                        IsOpen = true,
                        ProjectId = proOne.Id,
                        Name = "Branch3"
                    },
                    autoSave: true
                );

            }
        }

    }
}
