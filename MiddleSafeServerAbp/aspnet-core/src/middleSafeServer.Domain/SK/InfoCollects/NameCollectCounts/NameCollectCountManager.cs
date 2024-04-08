using JetBrains.Annotations;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.DistributedLocking;
using Volo.Abp.Domain.Services;

namespace middleSafeServer.SK.InfoCollects.NameCollectCounts
{
    public class NameCollectCountManager : DomainService
    {
        private readonly INameCollectCountRepository _nameCollectCountRepository;
        private readonly IAbpDistributedLock _abpDistributedLock; 

        public NameCollectCountManager(INameCollectCountRepository nameCollectCountRepository, IAbpDistributedLock abpDistributedLock) { 
        
            _nameCollectCountRepository = nameCollectCountRepository;
            _abpDistributedLock = abpDistributedLock;
        }


        public async Task<NameCollectCount> CreateAsync(
            [NotNull] Guid InfoAgentId
            )
        {
            var infoAgent = await _nameCollectCountRepository.FindAsync(i => i.InfoAgentId.Equals(InfoAgentId));
            if (infoAgent != null)
            {
                throw new NameCollectCountAlreadyExistsException(InfoAgentId.ToString());
            }
             
            return new NameCollectCount(GuidGenerator.Create(), InfoAgentId);
        }

        public async Task<uint> GetNameCollectIndex([NotNull] Guid InfoAgentId,int addCount = 1) {
             
            await using (var handle = await _abpDistributedLock.TryAcquireAsync("lockForGetNameCollectIndex:" + InfoAgentId.ToString(), new TimeSpan(0, 0, 10)))
            { //根据渠道Guid做互斥,最多等待10秒
                if (handle != null)
                {
                    uint tmpIndex = 0;
                    var infoAgent = await _nameCollectCountRepository.FindAsync(i => i.InfoAgentId.Equals(InfoAgentId));
                    if (infoAgent != null)
                    {
                        tmpIndex = infoAgent.Count + 1;
                        infoAgent.Count += (uint)addCount;
                        await _nameCollectCountRepository.UpdateAsync(infoAgent);
                    }
                    else { 
                        NameCollectCount newNameCount = new NameCollectCount(GuidGenerator.Create(), InfoAgentId);
                        tmpIndex = newNameCount.Count + 1;
                        newNameCount.Count += (uint)addCount;
                        await _nameCollectCountRepository.InsertAsync(newNameCount);
                    }
                    return tmpIndex;
                }
                else
                {
                    return 0;
                }
            }
             
        }



    }
}
