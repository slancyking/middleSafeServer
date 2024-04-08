using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using middleSafeServer.BackgroundJobs.ImageCollectDown;
using middleSafeServer.SK.InfoAgents;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using middleSafeServer.SK.InfoCollects.NameCollects;
using middleSafeServer.util;
using SixLabors.ImageSharp.Formats;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.BackgroundJobs;
using Volo.Abp.BackgroundWorkers;
using Volo.Abp.DependencyInjection;
using Volo.Abp.Threading;
using Volo.Abp.Timing;
using Volo.Abp.Uow;

namespace middleSafeServer.BackgroundWorker
{
    public class DownLoadImageForCollectWorker : AsyncPeriodicBackgroundWorkerBase, ISingletonDependency
    {
    
        private readonly IClock _clock;

        private readonly IImageCollectRepository _imageCollectRepository;
        private readonly INameCollectRepository _nameCollectRepository;
        private readonly IInfoAgentRepository _infoAgentRepository;
        private readonly IBackgroundJobManager _backgroundJobManager;
        private readonly ImageCollectManager _imageCollectManager;
        public DownLoadImageForCollectWorker(AbpAsyncTimer timer, IServiceScopeFactory serviceScopeFactory,  IClock clock,
            INameCollectRepository nameCollectRepository,
            IInfoAgentRepository infoAgentRepository,
            IBackgroundJobManager backgroundJobManager,
            IImageCollectRepository imageCollectRepository, 
            ImageCollectManager imageCollectManager) : base(timer, serviceScopeFactory)
        {
            _clock = clock;
            Timer.Period = /*30 * */60 * 1000; //处理间隔
            _nameCollectRepository = nameCollectRepository;
            _infoAgentRepository = infoAgentRepository;
            _backgroundJobManager = backgroundJobManager;
            _imageCollectRepository = imageCollectRepository;
            _imageCollectManager = imageCollectManager;
        }

        

        [UnitOfWork]
        protected override async Task DoWorkAsync(PeriodicBackgroundWorkerContext workerContext)
        {
            Logger.LogInformation("触发后台工作者.处理图片收集[工作单元]!");
            var infoAgentsCount = await _infoAgentRepository.GetCountAsync();
            int singlePage = 10;
            int skipCount = 0;

            do
            {
                var infoAgents = await _infoAgentRepository.GetListAsync(skipCount, singlePage,nameof(InfoAgent.CreationTime));

                //挨个渠道执行
                foreach (var i in infoAgents.Result)
                {
                    //处理掉失败次数大于5的 名称收录, 
                    await _nameCollectRepository.DeleteAsync(n => n.RetrySaveHeadIconCount >= 5 && n.ImageCollectId.Equals(null) && n.InfoAgentId.Equals(i.Id));

                    var query = await _nameCollectRepository.GetQueryableAsync();

                    var result = await _nameCollectRepository.GetNeedDownImageList(5, i.Id);
                     

                    foreach (var nameInfo in result) {
                        ImageCollectDownPublicArgs imageCollectDownPublicArgs = new ImageCollectDownPublicArgs();
                        imageCollectDownPublicArgs.HeadIconUrl = nameInfo.HeadIconUrl;
                        imageCollectDownPublicArgs.Id = nameInfo.Id;
                        imageCollectDownPublicArgs.InfoAgentId = nameInfo.InfoAgentId;
                        await _backgroundJobManager.EnqueueAsync(imageCollectDownPublicArgs);
                    }  
                }

                skipCount += singlePage;
            } while (infoAgentsCount >= skipCount);
            


            




        }
    }
}
