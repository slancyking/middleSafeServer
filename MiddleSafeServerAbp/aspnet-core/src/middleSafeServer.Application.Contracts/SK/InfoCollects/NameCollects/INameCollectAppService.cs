using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public interface INameCollectAppService : IApplicationService
    {

        /// <summary>
        /// 创建单个
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns> 
        Task<NameCollectDto> CreateAsync(CreateNameCollectDto input);

        /// <summary>
        /// 创建多个
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<CardClientOuputDto<CreateManyNameCollectOutputDto>> CreateManyAsync(CardClientInputDto<CreateManyNameCollectDto> input);


       
        Task<CardClientOuputDto<GetRandomNameCollectOutputDto>> RandomNameCollect(CardClientInputDto<GetRandomNameCollectInputDto> input);


        /// <summary>
        /// 更新项目
        /// </summary>
        /// <returns></returns> 
        Task UpdateAsync(Guid id, UpdateNameCollectDto input);

        /// <summary>
        /// 获取项目列表
        /// </summary>
        /// <returns></returns> 
        Task<PagedResultDto<NameCollectDto>> GetListAsync(GetNameCollectListDto input);

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
        Task<NameCollectDto> GetAsync(Guid id);

    }
}
