using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.PropCollects.Dto
{
    /// <summary>
    /// 物品详情
    /// </summary>
    public class PropItemOutputDto
    {
        /// <summary>
        /// 物品名称
        /// </summary>
        public string PropName { get; set; }


        /// <summary>
        /// 显示时间
        /// </summary>
        public List<string> ShowTime = new();

        /// <summary>
        /// 物品数目
        /// </summary>
        public List<int> PropNum = new();


    }
}
