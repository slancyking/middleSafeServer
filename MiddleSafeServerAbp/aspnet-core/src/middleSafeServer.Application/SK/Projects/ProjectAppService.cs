
using Microsoft.AspNetCore.Authorization;
using middleSafeServer.Permissions; 
  
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Authorization.Permissions;
using Volo.Abp.Domain.Repositories;
using Volo.Abp.Users;

namespace middleSafeServer.SK.Projects
{
    /// <summary>
    /// 项目管理
    /// </summary>
    public class ProjectAppService : middleSafeServerAppService, IProjectAppService
    {
        private readonly IProjectRepository _projectRepository; 
        //private readonly IPermissionDefinitionContext _permissionDefinitionContext;
         
        private readonly ProjectsManager _projectsManager;
        private readonly IPermissionDefinitionManager _permissionDefinitionManager;

        /// <summary>
        /// 构造
        /// </summary>
        /// <param name="projectRepository"></param>
        /// <param name="projectsManager"></param>
        /// <param name="permissionDefinitionManager"></param> 
        public ProjectAppService(IProjectRepository projectRepository, ProjectsManager projectsManager, IPermissionDefinitionManager permissionDefinitionManager)
        {
            _projectRepository = projectRepository;
            _projectsManager = projectsManager; 
            _permissionDefinitionManager = permissionDefinitionManager;
        }
        /// <summary>
        /// 创建一个项目
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.ProjectCreate)]
        public async Task<ProjectDto> CreateAsync(CreateProjectDto input)
        {
            var project = await _projectsManager.CreateAsync(
                                     input.Name,input.IpMaxUserCount,
                                     input.Remark
                                 );

            await _projectRepository.InsertAsync(project);


            return ObjectMapper.Map<Project, ProjectDto>(project);
        }

        /// <summary>
        /// 删除一个项目
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.ProjectDelete)]
        public async Task DeleteAsync(Guid id)
        {
            await _projectRepository.DeleteAsync(id);
        }

        /// <summary>
        /// 获取单个项目信息
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.ProjectGet)]
        public async Task<ProjectDto> GetAsync(Guid id)
        {
            var project = await _projectRepository.GetAsync(id);
            return ObjectMapper.Map<Project, ProjectDto>(project);
        }

        /// <summary>
        /// 获取项目列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.ProjectGetList)]
        public async Task<PagedResultDto<ProjectDto>> GetListAsync(GetProjectListDto input)
        {
            if (input.Sorting.IsNullOrWhiteSpace())
            {
                input.Sorting = nameof(Project.Name);
            }

            var projects = await _projectRepository.GetListAsync(
                input.SkipCount,
                input.MaxResultCount,
                input.Sorting,
                input.Filter
            );

             

            return new PagedResultDto<ProjectDto>(
                projects.Count,
                ObjectMapper.Map<List<Project>, List<ProjectDto>>(projects.Result)
            );
        }

        /// <summary>
        /// 更新一个项目
        /// </summary>
        /// <param name="id"></param>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.ProjectUpdate)]
        public async Task UpdateAsync(Guid id, UpdateProjectDto input)
        {
            var project = await _projectRepository.GetAsync(id);

            if (project.Name != input.Name)
            {
                await _projectsManager.ChangeNameAsync(project, input.Name);
            }
            project.IpMaxUserCount = input.IpMaxUserCount;
            project.Remark = input.Remark;

            await _projectRepository.UpdateAsync(project);
        }

        
    }
}
