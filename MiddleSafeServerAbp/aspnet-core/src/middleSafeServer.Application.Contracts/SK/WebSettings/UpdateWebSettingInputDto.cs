using System;

namespace middleSafeServer.SK.WebSettings
{

    /// <summary>
    /// 服务器设置输入实体
    /// </summary> 
    public class UpdateWebSettingInputDto
    {
         
        /// <summary>
        /// 是否开启邮件汇报--掉线
        /// </summary>
        public bool IsMailReportDrop { get; set; }

        /// <summary>
        /// 是否开启邮件汇报--服务器资源
        /// </summary>
        public bool IsMailReportServiceResource { get; set; }
         
        /// <summary>
        /// 服务器资源邮箱列表  分隔符 ","
        /// </summary>
        public string MailListForServiceResource { get; set; }

        /// <summary>
        /// 是否开启短信汇报--掉线
        /// </summary>
        public bool IsSmsReportDrop { get; set; }

        /// <summary>
        /// 是否开启短信汇报--服务器资源
        /// </summary>
        public bool IsSmsReportServiceResource { get; set; }
          
        /// <summary>
        /// 服务器资源 汇报手机号码  分隔符 ","
        /// </summary>
        public string PhoneNumForServiceResource { get; set; }
    }
}
