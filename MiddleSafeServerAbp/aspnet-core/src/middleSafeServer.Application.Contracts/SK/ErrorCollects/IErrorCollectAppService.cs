
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.CommonDto;
using System;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.ErrorCollects
{
    public interface IErrorCollectAppService : IApplicationService
    {
        /// <summary>
        /// 创建单个
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns> 
        Task<CardClientOuputDto<CardCommonOutputDto>> ClientErrorCollectAsync(CardClientInputDto<CreateErrorCollectInputDto>  input);

        /// <summary>
        /// 获取列表
        /// </summary>
        /// <returns></returns> 
        Task<PagedResultDto<ErrorCollectDto>> GetListAsync(GetErrorCollectListDto input);

        /// <summary>
        /// 删除一个
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        Task DeleteAsync(Guid id);
         
        /// <summary>
        /// 删除相似的错误报告
        /// </summary>
        /// <param name="errorMessage"></param>
        /// <returns></returns>
        Task DeleteSameErrorMessage(Guid id);
         
        /// <summary>
        /// 获取单个信息
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        Task<ErrorCollectDto> GetAsync(Guid id);

        

       

        








    }
}
