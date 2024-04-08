using Microsoft.Extensions.Configuration;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.util
{
    public static class ConfigHelper
    {
        private static IConfigurationRoot _appConfiguration = AppConfigurations.Get(System.Environment.CurrentDirectory);

        public static string GetAppSetting(string section, string key)
        {

            return _appConfiguration.GetSection(section)[key];
        }

        public static string GetConnectionString(string key)
        {
            return _appConfiguration.GetConnectionString(key);
        }

    }
}
