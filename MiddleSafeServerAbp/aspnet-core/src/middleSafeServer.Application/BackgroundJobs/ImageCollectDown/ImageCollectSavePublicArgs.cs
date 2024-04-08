using middleSafeServer.SK.InfoCollects.NameCollects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.BackgroundJobs.ImageCollectDown
{
    [Serializable]
    public class ImageCollectSavePublicArgs
    {
        public bool success { get; set; }
        public string ImageB64 { get; set; }
        public uint Image64Size { get; set; }
        public string ImageMd5 { get; set; }
        public uint ImageHash { get; set; }
        public int ImageWidth { get; set; }
        public int ImageHeight { get; set; }
        public string ImageName { get; set; }
        public Guid NameId { get; set; }
        public Guid InfoAgentId { get; set; }
    }
}
