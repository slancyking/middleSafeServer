using JetBrains.Annotations;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using middleSafeServer.util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class NameCollect : AggregateRoot<Guid>, IHasCreationTime
    {
        /// <summary>
        /// 创建时间
        /// </summary>
        public DateTime CreationTime { get; set; }

        public Guid InfoAgentId { get; set; }

        public string Name { get; set; }
        public int Sex { get; set; } //性别 0未知 1男 2女
        public uint NameHash { get; set; }


        public bool FinishSaveHeadIcon { get; set; } //已经完成头像保存 
        public string HeadIconUrl { get; set; } //头像网址 
        public int RetrySaveHeadIconCount { get; set; } //重试保存头像数据次数

        public Guid? ImageCollectId { get; set; }
        public uint CollectIndex { get; set; } //收集索引

        public string ExtendJson { get; set; }

        /// <summary>
        /// 构造 用于反序列化
        /// </summary>
        public NameCollect()
        {
            /* This constructor is for deserialization / ORM purpose */
        }

        public NameCollect(
            Guid id,
            Guid infoAgentId,
            string name, 
            int sex, 
            Guid? imageCollectId, 
            string headIconUrl, 
            string extendJson
            ) : base(id)
        {
            CreationTime = DateTime.Now;
            InfoAgentId = infoAgentId; 
            Sex = sex;
            RetrySaveHeadIconCount = 0;
            ImageCollectId = imageCollectId;
            SetName(name); 
            if (imageCollectId != null) FinishSaveHeadIcon = false;
            else FinishSaveHeadIcon = false;

            HeadIconUrl = headIconUrl;
            ExtendJson = extendJson;

        }

        public NameCollect ChangeName( string name)
        {
            SetName(name);
            return this;
        }

        private void SetName( string name)
        {
            Name = Check.NotNullOrWhiteSpace(
                name,
                nameof(name),
                maxLength: SKConsts.MaxNameLength
            );
            NameHash = CommonCrypt.stringToHashNumber(Name);
        }
    }
}
