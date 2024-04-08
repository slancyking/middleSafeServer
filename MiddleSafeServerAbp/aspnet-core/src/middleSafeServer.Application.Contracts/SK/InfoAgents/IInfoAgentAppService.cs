
using System;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.InfoAgents
{
    public interface IInfoAgentAppService : IApplicationService
    {
        /// <summary>
        /// 创建单个
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns> 
        Task<InfoAgentDto> CreateAsync(CreateInfoAgentDto input);

        /// <summary>
        /// 更新项目
        /// </summary>
        /// <returns></returns> 
        Task UpdateAsync(Guid id, UpdateInfoAgentDto input);

        /// <summary>
        /// 获取项目列表
        /// </summary>
        /// <returns></returns> 
        Task<PagedResultDto<InfoAgentDto>> GetListAsync(GetInfoAgentListDto input);

        /// <summary>
        /// 删除一个项目
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        Task DeleteAsync(Guid id);
         
        /// <summary>
        /// 获取单个信息
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        Task<InfoAgentDto> GetAsync(Guid id);

        

       

        








    }
}
