using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;

namespace middleSafeServer.SK.PropCollects
{
    public class PropCollect : Entity<Guid>, IHasCreationTime
    {
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
        /// 所属卡号
        /// </summary> 
        public Guid CardId { get; set; }  

        /// <summary>
        /// 物品名称
        /// </summary>
        [MaxLength(middleSafeServerConsts.MaxLength_ForPropName)]
        public string PropName { get; set; }

        /// <summary>
        /// 物品id
        /// </summary>
        [MaxLength(middleSafeServerConsts.MaxLength_ForPropId)]
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
        [MaxLength(middleSafeServerConsts.MaxLength_ForRemark)]
        public string Remark { get; set; }

        /// <summary>
        /// 构造 初始化插入时间
        /// </summary>
        public PropCollect()
        {
            this.CreationTime = DateTime.Now;
        }

        public void setId(Guid id) {
            this.Id = id;
        }

    }
}
