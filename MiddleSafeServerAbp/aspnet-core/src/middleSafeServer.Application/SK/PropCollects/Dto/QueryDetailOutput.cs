using AutoMapper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.PropCollects.Dto
{
    /// <summary>
    /// 查询物品列表OutputDto
    /// </summary>
    [AutoMap(typeof(PropCollect))]
    public class QueryDetailOutput
    {
        /// <summary>
        /// 创建时间
        /// </summary>
        public DateTime CreationTime { get; set; }

        /// <summary>
        /// 记录ip地址
        /// </summary> 
        public string IP { get; set; }

        /// <summary>
        /// 项目主名称
        /// </summary> 
        public string ProjectName { get; set; }

        /// <summary>
        /// 项目分支名称
        /// </summary> 
        public string BranchName { get; set; }

        /// <summary>
        /// 所属卡号
        /// </summary> 
        public string CardPassword { get; set; }
           
        /// <summary>
        /// 物品名称
        /// </summary> 
        public string PropName { get; set; }

        /// <summary>
        /// 物品id
        /// </summary> 
        public string PropId { get; set; }

        /// <summary>
        /// 物品数目
        /// </summary>
        public int PropNum { get; set; }

        /// <summary>
        /// 提交的时间戳
        /// </summary>
        public int PostUnix { get; set; }

        /// <summary>
        /// 备注
        /// </summary> 
        public string Remark { get; set; }

    }
}
