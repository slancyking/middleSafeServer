using System;
using System.Collections.Generic;
using System.Text;

namespace middleSafeServer
{
    public class AppConsts
    {
        /// <summary>
        /// Default page size for paged requests.
        /// </summary>
        public const int DefaultPageSize = 30;

        /// <summary>
        /// Maximum allowed page size for paged requests.
        /// </summary>
        public const int MaxPageSize = 1000;


        public const int MaxFormResult = 20;

        /// <summary>
        /// 最大卡密天数
        /// </summary>
        public const int CreateCardMaxDay = 365 * 10;

        /// <summary>
        /// 最大卡密数量
        /// </summary>
        public const int CreateCardMaxCount = 1000;



        public const string QueryName_Detail = "产量详情";
        public const string QueryName_Everyday = "每日产量";




        /// <summary>
        /// 消息定义  掉线消息
        /// </summary>
        public const string MsgDefine_Dropped = "Msg.RecDroppedMsg";



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
