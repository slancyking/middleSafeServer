using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.PropCollects.Dto
{
    /// <summary>
    /// 项目分支详情 
    /// </summary>
    public class PropBranchOutputDto
    {
        /// <summary>
        /// 分支名
        /// </summary>
        public string ProjectSubName { get; set; }

        /// <summary>
        /// 开始时间
        /// </summary>
        public DateTime StartTime { get; set; }

        /// <summary>
        /// 开始时间文本
        /// </summary>
        public string StartTimeStr { get; set; }
        /// <summary>
        /// 最后时间
        /// </summary>
        public DateTime LastTime { get; set; }
        /// <summary>
        /// 结束时间文本
        /// </summary>
        public string LastTimeStr { get; set; }

        /// <summary>
        /// 天数
        /// </summary>
        public int DaysCount { get; set; }

        /// <summary>
        /// 物品列表
        /// </summary>
        public List<PropItemOutputDto> PropList = new();
    }
}
