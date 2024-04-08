using AutoMapper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Inputforms.Dto
{
    /// <summary>
    /// 获取最后表单Json OutputDto
    /// </summary>
    [AutoMap(typeof(SK.InputForms.InputForm))]
    public class GetFormOutputDto
    {
        /// <summary>
        /// 创建时间
        /// </summary>
        public DateTime CreationTime { get; set; }
         
        /// <summary>
        /// 表单名
        /// </summary>
        public string Name { get; set; }

        /// <summary>
        /// 表单值
        /// </summary>
        public string Value { get; set; }

        /// <summary>
        /// 用户id
        /// </summary>
        public Guid UserId { get; set; }
    }
}
