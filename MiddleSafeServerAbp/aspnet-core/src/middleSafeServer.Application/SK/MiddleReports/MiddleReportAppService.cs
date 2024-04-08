using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Http;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.CommonDto;
using middleSafeServer.util;
using System;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.MiddleReports
{
    /// <summary>
    /// 中间报告服务
    /// </summary>

    public class MiddleReportAppService : middleSafeServerAppService, IMiddleReportAppService
    {

        private readonly IRepository<MiddleReport> _middleReportRepository;
        private readonly ICardRepository _cardRepository; 
        private readonly CardManager _cardManager;
        private IHttpContextAccessor _accessor;

        /// <summary>
        /// 构造
        /// </summary>
        /// <param name="middleReportRepository"></param>
        /// <param name="cardRepository"></param>
        /// <param name="accessor"></param>
        /// <param name="cardManager"></param> 
        public MiddleReportAppService(IRepository<MiddleReport> middleReportRepository
            , ICardRepository cardRepository 
            , IHttpContextAccessor accessor
            , CardManager cardManager) {
            _middleReportRepository = middleReportRepository;
            _cardRepository = cardRepository; 
            _accessor = accessor;
            _cardManager = cardManager;
        }

        /// <summary>
        /// 正常查询 基于端口和随机秘钥
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        [AllowAnonymous]
        public async Task<CardClientOuputDto<MiddleNomalQueryOutputDto>> NormalQueryAsync(CardClientInputDto<MiddleNomalQueryInputDto> input)
        {
            if (!string.IsNullOrWhiteSpace(input.Password))
            {
                SK.Cards.Card _card = await _cardRepository.FindAsync(c => c.Password == input.Password.Trim());
                if (_card == null) 
                    return new CardClientOuputDto<MiddleNomalQueryOutputDto>(new MiddleNomalQueryOutputDto() { Info = "卡密异常" }, null);

                var param = input.getParam(_card.RsaPrivateKey);
                if (param == null) 
                    return new CardClientOuputDto<MiddleNomalQueryOutputDto>(new MiddleNomalQueryOutputDto() { Info = "参数异常" }, _card.RsaPrivateKey);

                if (param.bCheckTimeout())
                    return new CardClientOuputDto<MiddleNomalQueryOutputDto>(new MiddleNomalQueryOutputDto() { Info = "请求超时" }, _card.RsaPrivateKey);

                CardLoginStatus loginStatus = _cardManager.CheckCardLogin(_card, param.Token);
                if (loginStatus != CardLoginStatus.loginSuccess)
                    return new CardClientOuputDto<MiddleNomalQueryOutputDto>(new MiddleNomalQueryOutputDto() { Info = "登陆状态异常" }, _card.RsaPrivateKey);

                var report = await _middleReportRepository.FirstOrDefaultAsync(a => a.CardId == _card.Id && a.Flag == param.Flag);
                if (report == null)
                    return new CardClientOuputDto<MiddleNomalQueryOutputDto>(new MiddleNomalQueryOutputDto() { Info = "操作成功" }, _card.RsaPrivateKey);
                MiddleNomalQueryOutputDto result = ObjectMapper.Map<MiddleReport, MiddleNomalQueryOutputDto>(report);
                result.Info = "操作成功";
                return new CardClientOuputDto<MiddleNomalQueryOutputDto>(result, _card.RsaPrivateKey);
            }
            return new CardClientOuputDto<MiddleNomalQueryOutputDto>(new MiddleNomalQueryOutputDto() { Info = "卡密异常" }, null);
        }

        /// <summary>
        /// 正常报告
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        [AllowAnonymous]
        public async Task<CardClientOuputDto<MiddleReportOutputDto>> NormalReportAsync(CardClientInputDto<MiddleReportInputDto> input)
        {
            if (!string.IsNullOrWhiteSpace(input.Password))  
            {
                SK.Cards.Card _card = await _cardRepository.FindAsync(c => c.Password == input.Password.Trim());
                if (_card == null)
                    return new CardClientOuputDto<MiddleReportOutputDto>(new MiddleReportOutputDto() { Result = -100, Info = "卡密无效" }, null);

                var param = input.getParam(_card.RsaPrivateKey);
                if (param == null)
                    return new CardClientOuputDto<MiddleReportOutputDto>(new MiddleReportOutputDto() { Result = -98, Info = "解密异常" }, null);

                if (param.bCheckTimeout())
                    return new CardClientOuputDto<MiddleReportOutputDto>(new MiddleReportOutputDto() { Result = -101, Info = "请求超时" }, null);

                CardLoginStatus loginStatus = _cardManager.CheckCardLogin(_card, param.Token);
                if (loginStatus != CardLoginStatus.loginSuccess)
                    return new CardClientOuputDto<MiddleReportOutputDto>(
                    new MiddleReportOutputDto(){ Result = (int)loginStatus, Info = CardLoginStatusString.GetStatusString(loginStatus) }, 
                    null);


                var flagQuery = await _middleReportRepository.FindAsync(report => report.CardId == _card.Id && report.Flag == param.Flag);
                if (flagQuery == null)
                {
                    var report = ObjectMapper.Map<MiddleReportInputDto, MiddleReport>(param);
                    report.CardId = _card.Id;
                    report.IP = HttpContextExtension.GetUserIp(this._accessor.HttpContext);
                    await _middleReportRepository.InsertAsync(report);
                }
                else {
                    flagQuery.IP = HttpContextExtension.GetUserIp(this._accessor.HttpContext);
                    flagQuery.CreationTime = DateTime.Now;
                    flagQuery.KeyIndex = param.KeyIndex;
                    flagQuery.RandomKey = param.RandomKey;
                    flagQuery.RandomPort = param.RandomPort;
                    flagQuery.PostUnix = param.PostUnix;
                    await _middleReportRepository.UpdateAsync(flagQuery);
                }

                return new CardClientOuputDto<MiddleReportOutputDto>(new MiddleReportOutputDto() { Result = 0, Info = "操作成功" }, _card.RsaPrivateKey);
            }
            return new CardClientOuputDto<MiddleReportOutputDto>(new MiddleReportOutputDto() { Result = -100, Info = "卡密无效" }, null);
        }
    }
}
