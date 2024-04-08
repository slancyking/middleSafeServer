
using middleSafeServer.SK.ExtendCards.Dto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Application.Services;

namespace middleSafeServer.SK.ExtendCards
{
    public interface IExtendCardAppService : IApplicationService
    {
        /// <summary>
        /// 批量创建
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        Task Create(CreateExtendCardInputDto input);


        /// <summary>
        /// 获取单个卡密
        /// </summary>
        /// <param name="CardId"></param>
        /// <returns></returns>
        Task<ExtendCardOutputDto> GetCard(Guid CardId);



        /// <summary>
        /// 更新卡
        /// </summary>
        /// <returns></returns>
        Task UpdateCard(ExtendCardInputDto input);


        /// <summary>
        /// 获取卡列表
        /// </summary>
        /// <returns></returns>
        Task<PagedResultDto<ExtendCardOutputDto>> GetCardList(GetExtendCardListInput input);



    }
}
