using middleSafeServer.SK.InfoCollects.NameCollects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.BackgroundJobs.ImageCollectDown
{
    [Serializable]
    public class ImageCollectDownPublicArgs
    {
        public Guid Id { get; set; }
        public Guid InfoAgentId { get; set; }
        public string HeadIconUrl { get; set; } //头像网址 
        public int RetrySaveHeadIconCount { get; set; } //重试保存头像数据次数
    }
}
