using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using JetBrains.Annotations;
using middleSafeServer.SK.Projects;
using Volo.Abp;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;
using Volo.Abp.Domain.Entities.Auditing;
using Volo.Abp.Timing;
using Volo.Abp.Users;
namespace middleSafeServer.SK.Branchs
{
    /// <summary>
    /// 项目分支
    /// </summary>
    public class Branch  : FullAuditedAggregateRoot<Guid>{
         

        /// <summary>
        /// 分支名
        /// </summary>
        public string Name { get; set; }
         
        /// <summary>
        /// 所属项目id
        /// </summary>
        public Guid ProjectId { get; set; }
          
        /// <summary>
        /// 分支是否启用
        /// </summary>
        public bool IsOpen  { get; set; }
          
        /// <summary>
        /// 分支备注
        /// </summary>
        public string Remark { get; set; }

        /// <summary>
        /// 构造 用于反序列化
        /// </summary>
        public Branch()
        {
            /* This constructor is for deserialization / ORM purpose */
        }

        internal Branch(
            Guid id,
            [NotNull] string name, 
            [NotNull] Guid projectId,
            [NotNull] bool isOpen,
            [CanBeNull] string remark = null
            )
            : base(id)
        {
            SetName(name);
            Remark = remark;  
            ProjectId = projectId;
            IsOpen = isOpen; 
        }

        internal Branch ChangeName([NotNull] string name)
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
