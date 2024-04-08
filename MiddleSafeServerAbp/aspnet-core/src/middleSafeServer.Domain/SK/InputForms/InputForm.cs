using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;
using Volo.Abp.Users;

namespace middleSafeServer.SK.InputForms
{    
    /// <summary>
    /// 用户表单
    /// </summary>
    public class InputForm : Entity<Guid>, IHasCreationTime
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
