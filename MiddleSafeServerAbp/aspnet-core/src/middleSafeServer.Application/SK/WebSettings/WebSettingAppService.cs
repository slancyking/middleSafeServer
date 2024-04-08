
using Microsoft.AspNetCore.Authorization;
using middleSafeServer.Permissions;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Domain.Repositories;
using System;

namespace middleSafeServer.SK.WebSettings
{
    /// <summary>
    /// 获取网站设置
    /// </summary>

    public class WebSettingAppService : middleSafeServerAppService, IWebSettingAppService
    {
        private readonly IRepository<WebSetting> _webSettingRepository;

        /// <summary>
        /// 构造
        /// </summary>
        /// <param name="webSettingRepository"></param>
        public WebSettingAppService(IRepository<WebSetting> webSettingRepository)
        {
            _webSettingRepository = webSettingRepository;
        }

        /// <summary>
        /// 获取默认配置
        /// </summary>
        /// <returns></returns>
        /// <exception cref="UserFriendlyException"></exception>
        [Authorize(middleSafeServerPermissions.WebSettingGet)]
        public async Task<GetWebSettingOutputDto> GetWebSettingDef()
        {
            var Result = await _webSettingRepository.FirstOrDefaultAsync();

            if (Result == null)
            {
                throw new UserFriendlyException("网站配置丢失");
            }

            return ObjectMapper.Map<WebSetting, GetWebSettingOutputDto>(Result);
        }

        /// <summary>
        /// 更新配置
        /// </summary>
        /// <param name="id"></param>
        /// <param name="input"></param>
        /// <returns></returns>
        /// <exception cref="UserFriendlyException"></exception>
        [Authorize(middleSafeServerPermissions.WebSettingUpdate)]
        public async Task UpdateWebSetting(Guid id,UpdateWebSettingInputDto input)
        {
            var _setting = await _webSettingRepository.FirstOrDefaultAsync(s=>s.Id == id);

            if (_setting == null)
            {
                throw new UserFriendlyException("网站配置丢失");
            }
            else
            {
                _setting = ObjectMapper.Map<UpdateWebSettingInputDto, WebSetting>(input); 

                await _webSettingRepository.UpdateAsync(_setting);
            }
        }
         
    }
}
