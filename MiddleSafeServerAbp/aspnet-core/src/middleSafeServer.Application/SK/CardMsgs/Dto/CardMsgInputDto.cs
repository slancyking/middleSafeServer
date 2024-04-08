
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.CardMsgs.Dto
{
    public class CardMsgInputDto : IPagedResultRequest
    {
        /// <summary>
        /// 消息文本过滤
        /// </summary>
        public string MsgFilter { get; set; }
        /// <summary>
        /// 跳过数目
        /// </summary>
        public int SkipCount { get; set; }
        /// <summary>
        /// 最大分页数目
        /// </summary>
        public int MaxResultCount { get; set; }


        /// <summary>
        /// 支持分页的InputDto
        /// </summary>
        public CardMsgInputDto()
        {
            MaxResultCount = AppConsts.DefaultPageSize;
        }

    }
}
