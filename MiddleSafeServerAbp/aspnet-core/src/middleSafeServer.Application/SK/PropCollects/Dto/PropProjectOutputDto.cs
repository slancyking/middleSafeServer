using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.PropCollects.Dto
{
    /// <summary>
    /// 主项目
    /// </summary>
    public class PropProjectOutputDto
    {
        /// <summary>
        /// 主项目名
        /// </summary>
        public string ProjectName { get; set; }


        /// <summary>
        /// 项目分支信息
        /// </summary>
        public List<PropBranchOutputDto> SubList = new List<PropBranchOutputDto>();
    }
}
