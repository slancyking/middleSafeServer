using System;
using System.Collections.Generic;
using System.Text;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 导入卡密输出
    /// </summary>
    public class ImportCardOutputDto
    {
        /// <summary>
        /// 失败列表
        /// </summary>
        public List<string> FailseList { get; set; }
    }
}
