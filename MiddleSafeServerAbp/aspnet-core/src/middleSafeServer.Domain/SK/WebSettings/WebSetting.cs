
using System;
using System.Collections.Generic;
using System.Text;
using Volo.Abp.Domain.Entities;
using Volo.Abp.Validation;

namespace middleSafeServer.SK.WebSettings
{
    public class WebSetting : Entity<Guid>
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

         


        public List<string> GetMailListForServiceResource()
        {
            List<string> Result = GetStringList(this.MailListForServiceResource);
            if (Result != null)
            {
                for (int i = Result.Count - 1; i >= 0; i--)
                {
                    if (!ValidationHelper.IsValidEmailAddress(Result[i]) || Result[i].IsNullOrWhiteSpace())
                    {
                        Result.RemoveAt(i);
                    }
                }
            }
            return Result;
        }

         
        public List<string> GetPhoneNumForServiceResource()
        {
            List<string> Result = GetStringList(this.PhoneNumForServiceResource);
            if (Result != null)
            {
                for (int i = Result.Count - 1; i >= 0; i--)
                {
                    if (Result[i].IsNullOrWhiteSpace())
                    {
                        Result.RemoveAt(i);
                    }
                }
            }

            return Result;
        }

        private List<string> GetStringList(string pra)
        {
            if (pra.IsNullOrEmpty()) { return null; }
            if (!pra.Contains(",")) { return new List<string>() { pra }; }
            return new List<string>(pra.Split(","));
        }

    }
}
