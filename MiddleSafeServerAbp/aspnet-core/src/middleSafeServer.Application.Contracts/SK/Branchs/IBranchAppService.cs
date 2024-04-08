
using System;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.Branchs
{
    public interface IBranchAppService : IApplicationService
    {
        /// <summary>
        /// 创建单个
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns> 
        Task<BranchDto> CreateAsync(CreateBranchDto input);

        /// <summary>
        /// 更新项目
        /// </summary>
        /// <returns></returns> 
        Task UpdateAsync(Guid id, UpdateBranchDto input);

        /// <summary>
        /// 获取项目列表
        /// </summary>
        /// <returns></returns> 
        Task<PagedResultDto<BranchDto>> GetListAsync(GetBranchListDto input);

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
        Task<BranchDto> GetAsync(Guid id);

        

       

        








    }
}
