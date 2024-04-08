
using Microsoft.AspNetCore.Authorization;
using middleSafeServer.Permissions;
using middleSafeServer.SK.Projects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Authorization.Permissions;
using Volo.Abp.Domain.Repositories;
using Volo.Abp.Users; 

namespace middleSafeServer.SK.Branchs
{
    /// <summary>
    /// 项目分支管理
    /// </summary>
    [Authorize]
    public class BranchAppService : middleSafeServerAppService, IBranchAppService
    {
        private readonly IBranchRepository _branchRepository; 

        private readonly BranchManager _branchManager;

        /// <summary>
        /// 构造
        /// </summary>
        /// <param name="branchRepository"></param>
        /// <param name="branchManager"></param> 
        public BranchAppService(IBranchRepository branchRepository,  
            BranchManager branchManager
            ) {
            _branchRepository = branchRepository; 
            _branchManager = branchManager;
        }


        /// <summary>
        /// 创建一个分支
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.BranchCreate)]
        public async Task<BranchDto> CreateAsync(CreateBranchDto input)
        {
            var branch = await _branchManager.CreateAsync(
                                    input.Name,
                                    input.ProjectId,
                                    input.IsOpen,
                                    input.Remark
                                ); 
            var result = await _branchRepository.InsertAsync(branch); 
            return ObjectMapper.Map<Branch, BranchDto>(result);
        }

        /// <summary>
        /// 删除一个分支
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.BranchDelete)]
        public async Task DeleteAsync(Guid id)
        {
            await _branchRepository.DeleteAsync(id);
        }

        /// <summary>
        /// 获取一个分支
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.BranchGet)]
        public async Task<BranchDto> GetAsync(Guid id)
        {
            var branch = await _branchRepository.GetAsync(id);
            return ObjectMapper.Map<Branch, BranchDto>(branch);
        }

        /// <summary>
        /// 获取项目分支列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.BranchGetList)]
        public async Task<PagedResultDto<BranchDto>> GetListAsync(GetBranchListDto input)
        {
            if (input.Sorting.IsNullOrWhiteSpace())
            {
                input.Sorting = nameof(Project.Name);
            }

            var branchs = await _branchRepository.GetListAsync(
                input.SkipCount,
                input.MaxResultCount,
                input.Sorting,
                input._projectId,
                input.Filter
            );
              
            return new PagedResultDto<BranchDto>(
                branchs.Count,
                ObjectMapper.Map<List<Branch>, List<BranchDto>>(branchs.Result)
            );
        }

        /// <summary>
        /// 更新项目分支
        /// </summary>
        /// <param name="id"></param>
        /// <param name="input"></param>
        /// <returns></returns>  
        [Authorize(middleSafeServerPermissions.BranchUpdate)]
        public async Task UpdateAsync(Guid id, UpdateBranchDto input)
        {
            var branch = await _branchRepository.GetAsync(id);

            if (branch == null)
                return;


            if (branch.Name != input.Name)
            {
                await _branchManager.ChangeNameAsync(branch, input.Name);
            }

            if (branch.ProjectId != input.ProjectId)
                await _branchManager.ChangeProjectAsync(branch, input.ProjectId);
             
            branch.Remark = input.Remark;

            await _branchRepository.UpdateAsync(branch);
        }

         
    }
}
