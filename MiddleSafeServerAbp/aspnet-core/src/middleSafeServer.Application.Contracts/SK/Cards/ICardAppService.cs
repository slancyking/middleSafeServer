
using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.Cards
{
    public interface ICardAppService : IApplicationService
    {
        /// <summary>
        /// 批量创建
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task CreateAsync(CreateCardDto input);

        /// <summary>
        /// 导入卡密
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<ImportCardOutputDto> ImportCardAsync(List<ImportCardInputDto> input);


        /// <summary>
        /// 获取单个卡密
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        Task<CardDto> GetAsync(Guid id);



        /// <summary>
        /// 更新卡
        /// </summary>
        /// <param name="id"></param>
        /// <param name="input"></param>
        /// <returns></returns>
        Task UpdateAsync(Guid id,UpdateCardDto input);

        /// <summary>
        /// 删除卡
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        Task DeleteAsync(Guid id);

        /// <summary>
        /// 清除登陆状态
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        Task ClearLoginStatus(Guid id);
        /// <summary>
        /// 获取卡列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<PagedResultDto<CardDto>> GetListAsync(GetCardListDto input);


        /// <summary>
        /// 自用卡 登陆
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<CardLoginOutpuDto> LoginAsync(CardLoginInputDto input);

        /// <summary>
        /// 自用卡 退出
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<CardClientOuputDto<CardCommonOutputDto>> LogoutAsync(CardClientInputDto<CardLogoutDto> input);

        /// <summary>
        /// 暂停
        /// </summary>
        /// <returns></returns>
        Task<CardClientOuputDto<CardCommonOutputDto>> PauseAsync(CardClientInputDto<CardPauseDto> input); 

        /// <summary>
        /// 心跳
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns> 
        Task<CardClientOuputDto<CardCommonOutputDto>> PingAsync(CardClientInputDto<CardPingDto> input);

        /// <summary>
        /// 设置标题
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task<CardClientOuputDto<CardCommonOutputDto>> SetTitle(CardClientInputDto<CardSetTitleDto> input);


    }
}
