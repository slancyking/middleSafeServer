using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using middleSafeServer.BackgroundJobs.Mail;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.WebSettings;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.BackgroundJobs;
using Volo.Abp.BackgroundWorkers;
using Volo.Abp.DependencyInjection;
using Volo.Abp.Domain.Repositories;
using Volo.Abp.Threading;
using Volo.Abp.Timing;
using Volo.Abp.Uow;

namespace middleSafeServer.BackgroundWorker
{
    public class CollectDroppedUsersWorker : AsyncPeriodicBackgroundWorkerBase, ISingletonDependency
    {
        private readonly IClock _clock;
        private readonly ICardRepository _cardRepository;
        private readonly IWebSettingRepository _webSettingRepository;
        private readonly IBackgroundJobManager _backgroundJobManager;

        public CollectDroppedUsersWorker(AbpAsyncTimer timer, IServiceScopeFactory serviceScopeFactory, IClock clock, ICardRepository cardRepository, IWebSettingRepository webSettingRepository, IBackgroundJobManager backgroundJobManager) : base(timer, serviceScopeFactory)
        {
            _clock = clock;
            _cardRepository = cardRepository;
            _webSettingRepository = webSettingRepository;
            Timer.Period = 1 * 60 * 1000;  //1分钟清理一次
            _backgroundJobManager = backgroundJobManager; 
        }

        [UnitOfWork]
        protected override async Task DoWorkAsync(PeriodicBackgroundWorkerContext workerContext)
        { 

            Logger.LogInformation("触发后台工作者.清理数据[工作单元]!");

            Dictionary<string, List<Card>> groupDropList = new Dictionary<string, List<Card>>();

            var wSet = await _webSettingRepository.FirstOrDefaultAsync();
            if (wSet != null || wSet.IsMailReportDrop == false) return;

            var _Now = DateTime.Now;
            var _5Minutes = DateTime.Now.Subtract(TimeSpan.FromMinutes(5));

            var DroppedCard = await _cardRepository.GetListAsync(c=>c.LoginToken != null && c.LoginToken != ""
                && c.LoginOvertime > _5Minutes
                && c.LoginOvertime <= _Now);

            foreach (var card in DroppedCard) {
                if (string.IsNullOrWhiteSpace(card.Mail)) 
                    continue;
                if(!groupDropList.ContainsKey(card.Mail))
                    groupDropList.Add(card.Mail, new List<Card>());
                 
                card.LoginToken = "";
                if (card.EnableMail)
                    groupDropList[card.Mail].Add(card);
                 
            }
            await _cardRepository.UpdateManyAsync(DroppedCard);

           

            foreach (var perMail in groupDropList)
            {
                if (perMail.Value.Count == 0) continue;

                StringBuilder mailContent = new StringBuilder();
                mailContent.Append("<DIV>-------------------------</DIV><br/>\r\n");
                foreach (var _dCard in perMail.Value)
                {
                    mailContent.Append("<DIV>" + _dCard.Remark);
                    mailContent.Append(" | ");
                    mailContent.Append(_dCard.Password);
                    mailContent.Append("</DIV><br/>\r\n"); 
                }
                mailContent.Append("<DIV>-------------------------</DIV><br/>\r\n");

                var mailinfo = new SendMailJobPublishArgs()
                {
                    Content = mailContent.ToString(),
                    Recv = perMail.Key.Trim(),
                    Title = string.Format("有机器掉线,共:{0} 台", perMail.Value.Count)
                };

                await _backgroundJobManager.EnqueueAsync(mailinfo); 
            }


        }
    }
}
