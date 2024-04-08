using System;
using System.Collections.Generic;
using System.Text;

namespace middleSafeServer.SK
{
    public class SKConsts
    {

        public const int CardPingAddTime = 5;
        public const int RSAKeyLength = 512;

        public const int IpLogExpiredTime = 10; //单位 分钟


        public const int MaxCardPassword = 256;

        public const int MaxCardDays = 366 * 5;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.UserName property.
        public const int MaxUserNameLength = 256;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.EmailAddress property.
        public const int MaxEmailAddressLength = 256;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.Name property.
        public const int MaxNameLength = 64;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.Surname property.
        public const int MaxSurnameLength = 64;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.AuthenticationSource
        //     property.
        public const int MaxAuthenticationSourceLength = 64;

        //
        // 摘要:
        //     UserName of the admin. admin can not be deleted and UserName of the admin can
        //     not be changed.
        public const string AdminUserName = "admin";

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.Password property.
        public const int MaxPasswordLength = 128;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.Password without hashed.
        public const int MaxPlainPasswordLength = 32;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.EmailConfirmationCode
        //     property.
        public const int MaxEmailConfirmationCodeLength = 328;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.PasswordResetCode property.
        public const int MaxPasswordResetCodeLength = 328;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.PhoneNumber property.
        public const int MaxPhoneNumberLength = 32;

        //
        // 摘要:
        //     Maximum length of the Abp.Authorization.Users.AbpUserBase.SecurityStamp property.
        public const int MaxSecurityStampLength = 128;


    }
}
