using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Authorization;
using middleSafeServer.Permissions;
using middleSafeServer.SK.CardMsgs.Dto;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.CardMsgs
{
    /// <summary>
    /// 卡密消息应用层
    /// </summary>
    [Authorize]
    public class CardMsgAppService : middleSafeServerAppService, ICardMsgAppService
    {
        private IRepository<CardMsg> _cardMsgRepository;

        /// <summary>
        /// 构造
        /// </summary>
        /// <param name="cardMsgRepository"></param>
        public CardMsgAppService(IRepository<CardMsg> cardMsgRepository)
        {
            _cardMsgRepository = cardMsgRepository;
        }

        /// <summary>
        /// 删除消息
        /// </summary>
        /// <param name="MsgIds"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.CardMsgDelete)]
        public async Task DeleteByIds(Guid[] MsgIds)
        {
            if (MsgIds == null || MsgIds.Length == 0)
                return;
            await _cardMsgRepository.DeleteAsync(i => i.Id.IsIn(MsgIds));
        }


        /// <summary>
        /// 获取消息列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.CardMsgGetList)]
        public async Task<PagedResultDto<CardMsgOutputDto>> GetMsgList(CardMsgInputDto input)
        {
            var msgQuery = await _cardMsgRepository.GetQueryableAsync(); 
            var MsgList =  msgQuery.Where(i => i.IsRead == false).WhereIf(!input.MsgFilter.IsNullOrWhiteSpace(), i => i.Info.Contains(input.MsgFilter));

            var m_count = MsgList.Count();
            MsgList = MsgList.PageBy(input);

            return new PagedResultDto<CardMsgOutputDto>(m_count, ObjectMapper.Map<IQueryable<CardMsg>, List<CardMsgOutputDto>>(MsgList));
        }


        /// <summary>
        /// 设置已读
        /// </summary>
        /// <param name="MsgIds"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.CardMsgSetRead)]
        public async Task SetReadByIds(Guid[] MsgIds)
        {
            var msgQuery = await _cardMsgRepository.GetQueryableAsync();
            var MsgList = msgQuery.Where(i => i.Id.IsIn(MsgIds));

            foreach (var item in MsgList)
            {
                item.IsRead = true;
                _cardMsgRepository.UpdateAsync(item);
            }
        }
    }
}
