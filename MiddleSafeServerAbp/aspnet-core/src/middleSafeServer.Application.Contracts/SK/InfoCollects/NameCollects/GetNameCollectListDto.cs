using System;
using System.Collections.Generic;
using System.Text;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class GetNameCollectListDto : PagedAndSortedResultRequestDto
    {
        /// <summary>
        /// 关键字
        /// </summary>
        public string Filter { get; set; }

        public Guid? InfoAgentId { get; set; }


    }
}
