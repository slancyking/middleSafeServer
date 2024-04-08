
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

namespace middleSafeServer.SK.InfoAgents
{
    /// <summary>
    /// 项目分支管理
    /// </summary>
    [Authorize]
    public class InfoAgentAppService : middleSafeServerAppService, IInfoAgentAppService
    {
        private readonly IInfoAgentRepository _infoAgentRepository;

        private readonly InfoAgentManager _infoAgentManager;

   
        public InfoAgentAppService(IInfoAgentRepository infoAgentRepository,
            InfoAgentManager infoAgentManager
            ) { 
            _infoAgentRepository = infoAgentRepository;
            _infoAgentManager = infoAgentManager;
        }


        /// <summary>
        /// 创建一个信息收集渠道
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.InfoAgentCreate)]
        public async Task<InfoAgentDto> CreateAsync(CreateInfoAgentDto input)
        {
            var infoAgent = await _infoAgentManager.CreateAsync(
                                    input.Name, 
                                    input.IsOpen,
                                    input.Description
                                ); 
            var result = await _infoAgentRepository.InsertAsync(infoAgent); 
            return ObjectMapper.Map<InfoAgent, InfoAgentDto>(result);
        }

        /// <summary>
        /// 删除一个信息收集渠道
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.InfoAgentDelete)]
        public async Task DeleteAsync(Guid id)
        {
            await _infoAgentRepository.DeleteAsync(id);
        }

        /// <summary>
        /// 获取一个信息收集渠道
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.InfoAgentGet)]
        public async Task<InfoAgentDto> GetAsync(Guid id)
        {
            var infoAgent = await _infoAgentRepository.GetAsync(id);
            return ObjectMapper.Map<InfoAgent, InfoAgentDto>(infoAgent);
        }

        /// <summary>
        /// 获取信息收集渠道列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.InfoAgentGetList)]
        public async Task<PagedResultDto<InfoAgentDto>> GetListAsync(GetInfoAgentListDto input)
        {
            if (input.Sorting.IsNullOrWhiteSpace())
            {
                input.Sorting = nameof(InfoAgent.Name);
            }

            var infoAgents = await _infoAgentRepository.GetListAsync(
                input.SkipCount,
                input.MaxResultCount,
                input.Sorting,
                input.Filter
            );
              
            return new PagedResultDto<InfoAgentDto>(
                infoAgents.Count,
                ObjectMapper.Map<List<InfoAgent>, List<InfoAgentDto>>(infoAgents.Result)
            );
        }

        /// <summary>
        /// 更新信息收集渠道
        /// </summary>
        /// <param name="id"></param>
        /// <param name="input"></param>
        /// <returns></returns>  
        [Authorize(middleSafeServerPermissions.InfoAgentUpdate)]
        public async Task UpdateAsync(Guid id, UpdateInfoAgentDto input)
        {
            var infoAgent = await _infoAgentRepository.GetAsync(id);

            if (infoAgent == null)
                return;


            if (infoAgent.Name != input.Name)
            {
                await _infoAgentManager.ChangeNameAsync(infoAgent, input.Name);
            }


            infoAgent.Description = input.Description;

            await _infoAgentRepository.UpdateAsync(infoAgent);
        }

         
    }
}
