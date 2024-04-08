using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.BackgroundJobs;
using Volo.Abp.DependencyInjection;
using Volo.Abp.Emailing;

namespace middleSafeServer.BackgroundJobs.Mail
{
    public class SendMailPublishJob : BackgroundJob<SendMailJobPublishArgs>, ITransientDependency
    {
        private readonly IEmailSender _emailSender;

        public SendMailPublishJob(
                    IEmailSender emailSender
                    )
        { 
            _emailSender = emailSender;
        }


        public override void Execute(SendMailJobPublishArgs args)
        {
            MailMessage mailmessage = new MailMessage("18680176145@163.com", args.Recv, args.Title, args.Content);
            //from email，to email，主题，邮件内容
            mailmessage.Priority = MailPriority.Normal; //邮件优先级
            SmtpClient smtpClient = new SmtpClient("smtp.163.com", 25); //smtp地址以及端口号
            smtpClient.Credentials = new NetworkCredential("18680176145@163.com", "ZXBOVRTNHGGXYBFO");//smtp用户名密码
            smtpClient.EnableSsl = true; //启用ssl                                            
            smtpClient.Send(mailmessage); //发送邮件

            //_emailSender.SendAsync(
            //       args.Recv,
            //       args.Title,
            //       args.Content
            //       );
        }
    }
}
