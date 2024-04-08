using JetBrains.Annotations;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities.Auditing;

namespace middleSafeServer.SK.InfoAgents
{
    /// <summary>
    /// 消息渠道
    /// </summary>
    public class InfoAgent : FullAuditedAggregateRoot<Guid>, IHasCreationTime
    {
        public string Name { get; set; }
        public string Description { get; set; }
        public bool IsOpen { get; set; }


        /// <summary>
        /// 构造 用于反序列化
        /// </summary>
        public InfoAgent()
        {
            /* This constructor is for deserialization / ORM purpose */
        }

        internal InfoAgent(
        Guid id,
        [NotNull] string name,
        [NotNull] bool isOpen,
        [CanBeNull] string description = null  ) : base(id)
        {
            SetName(name);
            Description = description; 
            IsOpen = isOpen;
            CreationTime = DateTime.UtcNow;
        }

        internal InfoAgent ChangeName([NotNull] string name)
        {
            SetName(name);
            return this;
        }

        private void SetName([NotNull] string name)
        {
            Name = Check.NotNullOrWhiteSpace(
                name,
                nameof(name),
                maxLength: SKConsts.MaxNameLength
            );
        }

    }
}
