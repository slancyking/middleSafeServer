using middleSafeServer.SK.Branchs;
using middleSafeServer.SK.Projects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Authorization.Permissions;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.Permissions
{
    public class AutoPermission : PermissionDefinitionProvider
    {
        private readonly IRepository<Project> _projectRepository;
        private readonly IRepository<Branch> _branchRepository;


        public AutoPermission(IRepository<Project> projectRepository, IRepository<Branch> branchRepository) {
            _projectRepository = projectRepository;
            _branchRepository = branchRepository;
        }


        public override async void Define(IPermissionDefinitionContext context)
        {
            //var projectGroup = context.AddGroup(middleSafeServerPermissions.projectGroup);
            //var projectList = await _projectRepository.GetQueryableAsync();

            //foreach (var project in projectList) {
            //    var currPro = projectGroup.AddPermission(project.Name);

            //    var branchList = await _branchRepository.GetQueryableAsync();
            //    branchList = branchList.Where(b => b.ProjectId == project.Id);
            //    foreach (var branch in branchList) {
            //        currPro.AddChild(project.Name + "_" + branch.Name);
            //    }
            //}

           



        }
    }
}
