using JetBrains.Annotations;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;

namespace middleSafeServer.SK.InfoCollects.ImageCollects
{
    public class ImageCollect : AggregateRoot<Guid>, IHasCreationTime
    {
        public DateTime CreationTime { get; set; }
        public Guid InfoAgentId    { get; set; }
        public string ImageBase64 { get; set; }
        public uint Image64Size { get; set; } //图片的base64 长度 
        public string ImageMd5 { get; set; } //头像数据的md5, 快速比较头像是否一致
        public uint ImageHash { get; set; } //将图片md5再做hash 分组 ,检索的时候增加速度
        public int ImageWidth { get; set; }
        public int ImageHeight { get; set; }
        public string ImageType { get; set; }


        /// <summary>
        /// 构造 用于反序列化
        /// </summary>
        public ImageCollect()
        {
            /* This constructor is for deserialization / ORM purpose */
        }

        public ImageCollect(
            Guid id,
            [NotNull] Guid infoAgentId,
            [NotNull] string imageBase64,
            [NotNull] uint image64Size,
            [NotNull] string imageMd5,
            [NotNull] uint imageHash,
            [NotNull] int imageWidth,
            [NotNull] int imageHeight,
            [NotNull] string imageType
            )
            : base(id)
        {
            InfoAgentId = infoAgentId;
            ImageBase64 = imageBase64;
            Image64Size = image64Size;
            ImageMd5 = imageMd5;
            ImageHash = imageHash;
            ImageType = imageType;
            ImageWidth = imageWidth;
            ImageHeight = imageHeight;
            this.CreationTime = DateTime.Now;
        }
    }
}
