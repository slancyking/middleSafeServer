using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.PropCollects.Dto
{
    /// <summary>
    /// 查询每日统计输出结构
    /// </summary>
    public class QueryEveryDayOutput
    {

        /// <summary>
        /// 显示时间
        /// </summary>
        public DateTime ShowTime { get; set; }

        /// <summary>
        /// 项目主名称
        /// </summary> 
        public string ProjectName { get; set; }

        /// <summary>
        /// 项目分支名称
        /// </summary> 
        public string BranchName { get; set; }


        /// <summary>
        /// 物品名称
        /// </summary>
        public string PropName { get; set; }

        /// <summary>
        /// 物品数目
        /// </summary>
        public int PropNum { get; set; }

    }
}
