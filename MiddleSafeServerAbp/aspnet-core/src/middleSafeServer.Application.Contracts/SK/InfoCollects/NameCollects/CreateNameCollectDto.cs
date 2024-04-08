using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class CreateNameCollectDto
    {
        /// <summary>
        /// 项目分支名
        /// </summary>
        [Required]
        [StringLength(SKConsts.MaxNameLength)]
        public string Name { get; set; }

        /// <summary>
        /// 项目id
        /// </summary>
        [Required]
        public Guid InfoAgentId { get; set; }

        [Required]
        public int Sex { get; set; } //性别 0未知 1男 2女 
        [Required]
        public string HeadIconUrl { get; set; } //头像网址  
        [Required]
        public string ImageCollect { get; set; }
        [Required]
        public string ExtendJson { get; set; }
    }
}
