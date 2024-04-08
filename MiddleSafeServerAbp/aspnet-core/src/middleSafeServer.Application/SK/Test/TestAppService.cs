using Microsoft.Extensions.Localization;
using middleSafeServer.BackgroundJobs.Mail;
using middleSafeServer.Localization;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.BackgroundJobs;
using Volo.Abp.Emailing;
using Volo.Abp.SettingManagement;
using Volo.Abp.Settings;

namespace middleSafeServer.SK.Test
{
    public class TestAppService : middleSafeServerAppService, ITestAppService
    {
        private readonly IStringLocalizer<middleSafeServerResource> _localizer;
        private readonly ISettingEncryptionService _settingEncryptionService;
        private readonly ISettingDefinitionManager _settingDefinitionManager;
        private readonly IBackgroundJobManager _backgroundJobManager;
        private readonly SettingManager _settingManager;
        public TestAppService(ISettingEncryptionService settingEncryptionService, ISettingDefinitionManager settingDefinitionManager
            , IBackgroundJobManager backgroundJobManager, SettingManager settingManager,
            IStringLocalizer<middleSafeServerResource> localizer)
        {
            _settingEncryptionService = settingEncryptionService;
            _settingDefinitionManager = settingDefinitionManager;
            _backgroundJobManager = backgroundJobManager;
            _settingManager = settingManager;
            _localizer = localizer;
        }

        public async Task<string> LocalizerTest()
        {
            return _localizer["Name"];
        }

        public async Task<string> MailEntrypt(string content)
        {
            var setting = _settingDefinitionManager.Get(EmailSettingNames.Smtp.Password);
            var psd = _settingEncryptionService.Encrypt(setting, content);
            await Task.Delay(1);
            return psd;
        }

        public async Task MailTets() {



            //encrypts the password on set and decrypts on get
            var fromAdd = _settingManager.GetAllGlobalAsync(); 


            var mailinfo = new SendMailJobPublishArgs()
            {
                Content = "测试内容",
                Recv = "119985151@qq.com",
                Title = "卡密服务器-测试邮件!"
            };

            await _backgroundJobManager.EnqueueAsync(mailinfo);

        }


    }
}
