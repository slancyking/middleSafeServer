using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.MiddleReports;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.BackgroundWorkers;
using Volo.Abp.DependencyInjection;
using Volo.Abp.Domain.Repositories;
using Volo.Abp.Threading;
using Volo.Abp.Timing;
using Volo.Abp.Uow;

namespace middleSafeServer.BackgroundWorker
{
    public class ClearMiddleReportWorker : AsyncPeriodicBackgroundWorkerBase, ISingletonDependency
    {
        private readonly IRepository<MiddleReport> _middleReportRepository;
        private readonly ICardRepository _cardRepository;

        private readonly IClock _clock;
 
        public ClearMiddleReportWorker(AbpAsyncTimer timer, IServiceScopeFactory serviceScopeFactory, IRepository<MiddleReport> middleReportRepository, ICardRepository cardRepository, IClock clock) : base(timer, serviceScopeFactory)
        {
            _clock = clock;
            _middleReportRepository = middleReportRepository;
            _cardRepository = cardRepository;
            Timer.Period = /*60 **/ 60 * 1000; //一个小时清理一次 
        }

        /// <summary>
        /// 清理数据[工作单元] 
        /// </summary>
        [UnitOfWork]
        protected override async Task DoWorkAsync(PeriodicBackgroundWorkerContext workerContext)
        { 
            Logger.LogInformation("触发后台工作者.清理数据[工作单元]!");
            var _1hour = _clock.Now.Subtract(TimeSpan.FromHours(1));


            var queryable = await _middleReportRepository.GetQueryableAsync();
            var query = from mid in queryable
                        join card in await _cardRepository.GetQueryableAsync() on mid.CardId equals card.Id
                        where mid.CreationTime < _1hour || mid.Token != card.LoginToken
                        select mid;
             
            var DroppedCard = query.ToList();
             
            if (DroppedCard == null || DroppedCard.Count == 0)
                return;

            Logger.LogInformation("清理掉过期中间报告数据 总数:%d", DroppedCard.Count);
            foreach (var card in DroppedCard)
            {
                Logger.LogInformation("清理掉过期中间报告数据,卡密ID:%s,Flag:%s,IP:%s\r\n", card.CardId, card.Flag, card.IP);
                _middleReportRepository.DeleteAsync(card);
            }
            
        }
    }
}
