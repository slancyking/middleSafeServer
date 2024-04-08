using AutoMapper;
using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.PropCollects.Dto
{
    /// <summary>
    /// 新建物品信息收集输入实体
    /// </summary>
    [AutoMap(typeof(PropCollect))]
    public class CreatePropCollectionInput : CardClientRequstBase
    { 
         
        /// <summary>
        /// 登陆凭证
        /// </summary>
        public string Token { get; set; }

        /// <summary>
        /// 物品名称
        /// </summary>
        [Required]
        [MaxLength(middleSafeServerConsts.MaxLength_ForPropName)]
        public string PropName { get; set; }

        /// <summary>
        /// 物品id
        /// </summary>
        [Required]
        [MaxLength(middleSafeServerConsts.MaxLength_ForPropId)]
        public string PropId { get; set; }

        /// <summary>
        /// 物品数目
        /// </summary>
        [Required]
        public int PropNum { get; set; }
         

        /// <summary>
        /// 备注
        /// </summary>
        [MaxLength(middleSafeServerConsts.MaxLength_ForRemark)]
        public string Remark { get; set; }
    }
}
