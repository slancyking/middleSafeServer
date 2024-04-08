using System;
using System.Collections.Generic;
using System.Text;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class GetRandomNameCollectOutputDto  
    {

        /// <summary>
        /// 执行结果
        /// </summary>
        public int Result { get; set; }

        /// <summary>
        /// 执行信息
        /// </summary>
        public string Info { get; set; }

        public NameCollectDto Data { get; set; }

    }
}
