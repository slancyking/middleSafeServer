using System;
using System.Collections.Generic;
using System.Text;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.Projects
{
    /// <summary>
    /// 获取项目列表输入实体
    /// </summary>
    public class GetProjectListDto : PagedAndSortedResultRequestDto
    {
        /// <summary>
        /// 项目名过滤
        /// </summary>
        public string Filter { get; set; }
    }
}
