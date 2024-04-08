using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class UpdateNameCollectDto
    {
        /// <summary>
        /// 所属项目id
        /// </summary>
        [Required]
        public Guid InfoAgentId { get; set; }


        [Required]
        [StringLength(SKConsts.MaxNameLength)]
        public string Name { get; set; }
        [Required]
        public int Sex { get; set; }
        [Required]
        public string ImageCollect { get; set; }
        [Required] 
        public string ExtendJson { get; set; }
    }
}
