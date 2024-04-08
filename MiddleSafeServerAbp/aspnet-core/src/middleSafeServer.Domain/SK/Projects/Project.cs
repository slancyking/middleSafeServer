using JetBrains.Annotations;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;
using Volo.Abp.Domain.Entities.Auditing;
using Volo.Abp.Users;

namespace middleSafeServer.SK.Projects
{
    /// <summary>
    /// 主项目实体
    /// </summary>
    public class Project : FullAuditedAggregateRoot<Guid>
    {    
        /// <summary>
        /// 项目名
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 每个ip最多几个用户使用
        /// </summary>
        public int IpMaxUserCount { get; set; }

        /// <summary>
        /// 项目备注
        /// </summary>
        public string Remark { get; set; }
          
        /// <summary>
        /// 构造 用于反序列化
        /// </summary>
        public Project()
        {
            /* This constructor is for deserialization / ORM purpose */
        }

        internal Project(
            Guid id,
            [NotNull] string name,
             [NotNull] int ipMaxUserCount,
            [CanBeNull] string remark = null)
            : base(id)
        {
            SetName(name);
            IpMaxUserCount = ipMaxUserCount;
            Remark = remark;
        }

        internal Project ChangeName([NotNull] string name)
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
