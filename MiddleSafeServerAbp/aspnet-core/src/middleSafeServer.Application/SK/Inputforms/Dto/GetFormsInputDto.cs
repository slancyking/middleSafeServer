using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.Inputforms.Dto
{
    /// <summary>
    /// 获取表单内容列表 InputDto
    /// </summary>
    public class GetFormsInputDto
    { 

        /// <summary>
        /// 表单名
        /// </summary> 
        public string Name { get; set; }

        /// <summary>
        /// 最大数目
        /// </summary>
        [Range(1, AppConsts.MaxFormResult)]
        public int MaxResult { get; set; }
    }
}
