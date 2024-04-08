
using middleSafeServer.SK.Inputforms.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.Inputforms
{
    /// <summary>
    /// 请求表单记录
    /// </summary>
    public interface IFormAppService : IApplicationService
    {
        /// <summary>
        /// 获取最后表单内容
        /// </summary>
        /// <returns></returns>
        Task<GetFormOutputDto> GetLastFormInfo(GetFormInputDto input);

        /// <summary>
        /// 获取表单内容列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<List<GetFormOutputDto>> GetFormInfoList(GetFormsInputDto input);
    }
}
