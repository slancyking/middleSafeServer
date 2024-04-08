using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.IRepository
{
    /// <summary>
    /// 查询物品统计请求通用结构
    /// </summary>
    public class QueryPropCollectInputCommon
    { 

        /// <summary>
        /// 分支id
        /// </summary>
        public Guid BranchId { get; set; }

        /// <summary>
        /// 查询起始时间
        /// </summary>
        public DateTime? QueryStartTime { get; set; }

        /// <summary>
        /// 查询结束时间
        /// </summary>
        public DateTime? QueryEndTime { get; set; }

        /// <summary>
        /// 项目id包含
        /// </summary>
        public Guid[] ProjectIdContain { get; set; }

        /// <summary>
        /// 项目id过滤
        /// </summary>
        public Guid[] ProjectIdFilter { get; set; }

        /// <summary>
        /// 分支id包含
        /// </summary>
        public Guid[] BranchIdContain { get; set; }

        /// <summary>
        /// 分支id过滤
        /// </summary>
        public Guid[] BranchIdFilter { get; set; }

        /// <summary>
        /// 物品包含  如果填写此字段,则只统计包含此名字的物品
        /// </summary>
        public string[] PropContain { get; set; }

        /// <summary>
        /// 物品过滤 如果填写此字段,则过滤掉改物品的统计
        /// </summary>
        public string[] PropFilter { get; set; }

        /// <summary>
        /// 卡号包含 如果填写此字段,则只统计包含此卡号的物品
        /// </summary>
        public string[] CardIdContains { get; set; }

        /// <summary>
        /// 卡号过滤 如果填写此字段,则过考虑掉此卡号的物品
        /// </summary>
        public string[] CardIdFilter { get; set; }
         

    }
}
