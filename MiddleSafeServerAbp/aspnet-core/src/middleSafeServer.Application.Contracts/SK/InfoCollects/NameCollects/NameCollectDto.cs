using System;
using System.Collections.Generic;
using System.Text;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class NameCollectDto : EntityDto<Guid>
    {
        public string InfoAgent { get; set; }

        public string Name { get; set; }
        public int Sex { get; set; } //性别 0未知 1男 2女 
         
        public bool FinishSaveHeadIcon { get; set; } //已经完成头像保存 
        public string HeadIconUrl { get; set; } //头像网址 
        public int RetrySaveHeadIconCount { get; set; } //重试保存头像数据次数

        public string ImageCollect { get; set; }
    }
}
