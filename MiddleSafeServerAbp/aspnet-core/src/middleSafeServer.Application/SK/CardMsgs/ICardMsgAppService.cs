 
using middleSafeServer.SK.CardMsgs.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.CardMsgs
{
    public interface ICardMsgAppService : IApplicationService
    {
        Task DeleteByIds(Guid[] MsgIds);


        Task SetReadByIds(Guid[] MsgIds);


        Task<PagedResultDto<CardMsgOutputDto>> GetMsgList(CardMsgInputDto input);
    }
}
