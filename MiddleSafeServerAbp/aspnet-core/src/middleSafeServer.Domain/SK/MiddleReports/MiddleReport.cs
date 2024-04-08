using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;

namespace middleSafeServer.SK.MiddleReports
{
    /// <summary>
    /// 中间报告服务
    /// </summary>
    public class MiddleReport : Entity<Guid>, IHasCreationTime
    {
        //////////////////

        /// <summary>
        /// 创建时间
        /// </summary>
        public DateTime CreationTime { get; set; }

        /// <summary>
        /// 记录ip地址
        /// </summary>
        [MaxLength(middleSafeServerConsts.MaxLength_ForIp)]
        public string IP { get; set; }

        /// <summary>
        /// 服务端的标志位,可以是进程id.之类的
        /// </summary>
        public string Flag { get; set; }

        /// <summary>
        /// 秘钥索引
        /// </summary>
        public int KeyIndex { get; set; }


        /// <summary>
        /// 随机端口
        /// </summary>
        public int RandomPort { get; set; }

        /// <summary>
        /// 随机秘钥
        /// </summary>
        public string RandomKey { get; set; }

        /// <summary>
        /// 提交的时间戳
        /// </summary>
        public int PostUnix { get; set; }

        /// <summary>
        /// 登陆凭证  用于后期清除数据时 校验登陆当前状态用
        /// </summary>
        public string Token { get; set; }

        /// <summary>
        /// 所属卡号
        /// </summary> 
        public Guid CardId { get; set; }
         
        /// <summary>
        /// 构造 初始化插入时间
        /// </summary>
        public MiddleReport()
        {
            this.CreationTime = DateTime.Now;
        }



    }
}
