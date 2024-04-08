using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;

namespace middleSafeServer.SK.InfoCollects.NameCollectCounts
{
    public class NameCollectCount : AggregateRoot<Guid>, IHasCreationTime
    {
        public DateTime CreationTime { get; set; }
        public Guid InfoAgentId { get; set; }
        public uint Count { get; set; }

        public NameCollectCount() { 
        
        }


        public NameCollectCount(Guid id, Guid InfoAgentId) : base(id)
        {
            this.InfoAgentId = InfoAgentId;
            this.CreationTime = DateTime.Now;
            this.Count = 0;
        }

    }
}
