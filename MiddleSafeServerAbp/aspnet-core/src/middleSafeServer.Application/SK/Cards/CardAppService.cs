

using Microsoft.AspNetCore.Authorization;
using middleSafeServer.Permissions;
using middleSafeServer.SK.CommonDto;
using middleSafeServer.util;
using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using Volo.Abp.Authorization;
using Volo.Abp.DistributedLocking;

namespace middleSafeServer.SK.Cards
{
    /// <summary>
    /// 卡密管理服务
    /// </summary>
    [Authorize]
    public class CardAppService : middleSafeServerAppService, ICardAppService
    {
        //private IHttpContextAccessor _accessor;
        private readonly ICardRepository _cardRepository; 
        private readonly CardManager _cardManager;
        private readonly IAuthorizationService _authorizationService;
        private readonly IAbpDistributedLock _abpDistributedLock;
        /// <summary>
        /// 构造
        /// </summary>
        /// <param name="cardRepository"></param> 
        /// <param name="cardManager"></param>
        /// <param name="authorizationService"></param>
        public CardAppService(ICardRepository cardRepository, CardManager cardManager, IAuthorizationService authorizationService, IAbpDistributedLock abpDistributedLock) {
            //_accessor = accessor;
            _cardRepository = cardRepository; 
            _cardManager = cardManager;
            _authorizationService = authorizationService;
            _abpDistributedLock = abpDistributedLock;
        }


        /// <summary>
        /// 批量创建
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns> 
        [Authorize(middleSafeServerPermissions.CardCreate)]
        public async Task CreateAsync(CreateCardDto input)
        {
            List<Card> cards = await _cardManager.CreateAsync(input.ChargingMode,input.ExpiredTime, input.BranchId, input.Days, input.Count, input.Mail, input.Phone, input.Remark,input.EnableMail, input.EnablePhoneMsg);
            if (cards != null && cards.Count > 0)
                await _cardRepository.InsertManyAsync(cards);
        }


        /// <summary>
        /// 导入卡密
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns> 
        [Authorize(middleSafeServerPermissions.CardImport)] 
        public async Task<ImportCardOutputDto> ImportCardAsync(List<ImportCardInputDto> input)
        {
            List<Card> imCard = new List<Card>();
            ImportCardOutputDto result = new ImportCardOutputDto();
            result.FailseList = new List<string>();
            foreach (var card in input) {
                var vCard = await _cardManager.ImportAsync(card.BranchId, card.Password, card.ExpiredTime, card.Phone, card.Mail, card.Remark);
                if (vCard != null)
                    imCard.Add(vCard);
                else
                    result.FailseList.Add(card.Password);
            }
            if (imCard.Count > 0)
                await _cardRepository.InsertManyAsync(imCard);

            return result;
        }

        


        /// <summary>
        /// 获取单个卡密信息
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.CardGetSingle)]
        public async Task<CardDto> GetAsync(Guid id)
        {
            var PersonCard = await _cardRepository.GetAsync(id);
            var result = await _authorizationService.AuthorizeAsync(middleSafeServerPermissions.CardFull);
            if (result.Succeeded == false && PersonCard.CreatorId != CurrentUser.Id) //没有完整权限并且创建者不是自身
            {
                //throw exception
                throw new AbpAuthorizationException("..."); 
            } 
            return ObjectMapper.Map<Card, CardDto>(PersonCard);
        }

        /// <summary>
        /// 获取卡密列表
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.CardGetList)]
        public async Task<PagedResultDto<CardDto>> GetListAsync(GetCardListDto input)
        {
            var result = await _authorizationService.AuthorizeAsync(middleSafeServerPermissions.CardFull);
            if (result.Succeeded == false ) //没有完整权限只能获取自身卡密
            {
                input.CreatorId = CurrentUser.Id;
            }
             
            var cardList = await _cardRepository.FindCards(input.SkipCount,input.MaxResultCount,input.Sorting,input.Filter,input.BranchId,input.Mail,input.Phone,input.CreatorId);
              
            return new PagedResultDto<CardDto>(cardList.Count, ObjectMapper.Map<List<Card>, List<CardDto>>(cardList.Result));
        }


        /// <summary>
        /// 更新卡
        /// </summary>
        /// <param name="id"></param>
        /// <param name="input"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.CardUpdate)]
        public async Task UpdateAsync(Guid id, UpdateCardDto input)
        {
            var card = await _cardRepository.GetAsync(id);
            if (card == null) return;

            var result = await _authorizationService.AuthorizeAsync(middleSafeServerPermissions.CardFull);
            if (result.Succeeded == false && card.CreatorId != CurrentUser.Id) //没有完整权限并且创建者不是自身
            {
                throw new AbpAuthorizationException("...");
            }

            if (card.Mail != input.Mail)
                _cardManager.ChangeMail(card, input.Mail);
            if (card.Phone != input.Phone)
                _cardManager.ChangePhone(card, input.Phone);
            if (card.Password != input.Password)
                _cardManager.ChangePassword(card, input.Password);

            card.ExpiredTime = input.ExpiredTime;
            card.EnableMail = input.EnableMail;
            card.EnablePhoneMsg = input.EnablePhoneMsg;
            card.ChargingMode = input.ChargingMode;

            card.Days = input.Days;
            card.Status = input.Status;
            await _cardRepository.UpdateAsync(card);
        }

        /// <summary>
        /// 删除一个卡密
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.CardDelete)]
        public async Task DeleteAsync(Guid id)
        {
            var result = await _authorizationService.AuthorizeAsync(middleSafeServerPermissions.CardFull);
            if (result.Succeeded == false) //没有完整权限并且创建者不是自身
            {
                await _cardRepository.DeleteAsync(c => c.Id == id && c.CreatorId == CurrentUser.Id);
            }
            else {
                await _cardRepository.DeleteAsync(c => c.Id == id);
            } 
            
        }

        /// <summary>
        /// 清除登陆状态
        /// </summary>
        /// <param name="id"></param>
        /// <returns></returns>
        [Authorize(middleSafeServerPermissions.CardUpdate)]
        public async Task ClearLoginStatus(Guid id) {
            var card = await _cardRepository.GetAsync(id);
            if (card == null) return;

            var result = await _authorizationService.AuthorizeAsync(middleSafeServerPermissions.CardFull);
            if (result.Succeeded == false && card.CreatorId != CurrentUser.Id) //没有完整权限并且创建者不是自身
            {
                throw new AbpAuthorizationException("...");
            }
            card.Logout();

            await _cardRepository.UpdateAsync(card);
        }



        /// <summary>
        /// 自用卡 登陆
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns> 
        [AllowAnonymous]
        public async Task<CardLoginOutpuDto> LoginAsync(CardLoginInputDto input)
        {
            CardLoginOutpuDto _result = new CardLoginOutpuDto();
            if (input.CardPassword.IsNullOrWhiteSpace() || input.BranchId.ToString().IsNullOrWhiteSpace())
            {
                _result.Result = -99;
                _result.Info = "参数异常";
                return _result;
            }

            var card = await _cardRepository.FindAsync(a => a.Password == input.CardPassword && input.BranchId.Equals(input.BranchId)); 
            if (card == null)
            {
                _result.Result = -100;
                _result.Info = "卡密无效";
                return _result;
            }

            await using (var handle = await _abpDistributedLock.TryAcquireAsync("lockForCard:" + input.CardPassword, new TimeSpan(0, 0, 5)))
            { 
                if (handle != null)
                { 
                    CardLoginStatus loginStatus = _cardManager.Login(card);
                    _result.Result = (int)loginStatus;
                    _result.Info = CardLoginStatusString.GetStatusString(loginStatus);
                    if (loginStatus != CardLoginStatus.loginSuccess)
                        return _result;

                    await _cardRepository.UpdateAsync(card);
                    _result.Token = HexEncrypt.GetstringDESenctypt(HexEncrypt.UUIDEncrypt(card.LoginToken), input.CardPassword.Trim());
                    _result.TokenEx = HexEncrypt.GetstringDESenctypt(card.RsaPublicKey, card.LoginToken);
                    _result.Expired = TimeHelp.ConvertDataTimeToLong(card.ExpiredTime);
                    _result.SurplusSecond = card.SurplusSecond;
                    return _result;
                }
                else {
                    _result.Result = -101;
                    _result.Info = "操作超时";
                    return _result;
                }
            }
            
             
            
        }


        /// <summary>
        /// 自用卡 退出
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [AllowAnonymous]
        public async Task<CardClientOuputDto<CardCommonOutputDto>> LogoutAsync(CardClientInputDto<CardLogoutDto> input)
        {
            CardCommonOutputDto _result = new CardCommonOutputDto();
            if (input.Password.IsNullOrWhiteSpace())
            {
                _result.Info = "参数异常";
                _result.Result = -99;
                return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
            }

            var card = await _cardRepository.FindAsync(a => a.Password == input.Password.Trim());
            if (card == null)
            {
                _result.Info = "卡密无效";
                _result.Result = -100;
                return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
            }

            await using (var handle = await _abpDistributedLock.TryAcquireAsync("lockForCard:" + input.Password, new TimeSpan(0, 0, 5)))
            {  
                if (handle != null)
                { 
                    var param = input.getParam(card.RsaPrivateKey);
                    _cardManager.CardLogout(card, param.Token.Trim());
                    await _cardRepository.UpdateAsync(card);
                    _result.Info = "操作成功";
                    _result.Result = 0;
                    return new CardClientOuputDto<CardCommonOutputDto>(_result, card.RsaPrivateKey);
                }
                else {
                    _result.Info = "操作超时";
                    _result.Result = -101;
                    return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                }
            }
            
        }

        /// <summary>
        /// 客户端心跳
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        [AllowAnonymous]
        public async Task<CardClientOuputDto<CardCommonOutputDto>> PingAsync(CardClientInputDto<CardPingDto> input)
        { 

            CardCommonOutputDto _result = new CardCommonOutputDto();
            if (input.Password.IsNullOrWhiteSpace())
            {
                _result.Info = "参数异常";
                _result.Result = -99;
                return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
            }

            var card = await _cardRepository.FindAsync(a => a.Password == input.Password.Trim());
            if (card == null)
            {
                _result.Info = "卡密无效";
                _result.Result = -100;
                return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
            }
            await using (var handle = await _abpDistributedLock.TryAcquireAsync("lockForCard:" + input.Password, new TimeSpan(0, 0, 5)))
            {
                if (handle != null)
                {
                    var param = input.getParam(card.RsaPrivateKey);
                    if (param == null)
                    {
                        _result.Info = "参数异常";
                        _result.Result = -98;
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                    }

                    if (param.bCheckTimeout())
                    {
                        _result.Info = "请求超时";
                        _result.Result = -80;
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                    }

                    //登陆状态检查
                    CardLoginStatus loginStatus = _cardManager.CheckCardLogin(card, param.Token);
                    _result.Result = (int)loginStatus;
                    _result.Info = CardLoginStatusString.GetStatusString(loginStatus);
                    if (loginStatus != CardLoginStatus.loginSuccess)
                    {
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, card.RsaPrivateKey);
                    }

                    _cardManager.Ping(card);

                    await _cardRepository.UpdateAsync(card);

                    long unixNow = TimeHelp.ConvertDataTimeToLong(DateTime.Now);
                    _result.Info = unixNow.ToString();
                    return new CardClientOuputDto<CardCommonOutputDto>(_result, card.RsaPrivateKey);

                }
                else
                {
                    _result.Info = "操作超时";
                    _result.Result = -101;
                    return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                }
            }
        }


        [AllowAnonymous]
        public async Task<CardClientOuputDto<CardCommonOutputDto>> SetTitle(CardClientInputDto<CardSetTitleDto> input) {
            CardCommonOutputDto _result = new CardCommonOutputDto();
            if (input.Password.IsNullOrWhiteSpace())
            {
                _result.Info = "参数异常";
                _result.Result = -99;
                return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
            }

            var card = await _cardRepository.FindAsync(a => a.Password == input.Password.Trim());
            if (card == null)
            {
                _result.Info = "卡密无效";
                _result.Result = -100;
                return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
            }
            await using (var handle = await _abpDistributedLock.TryAcquireAsync("lockForCard:" + input.Password, new TimeSpan(0, 0, 5)))
            {
                if (handle != null)
                {
                    var param = input.getParam(card.RsaPrivateKey);
                    if (param == null)
                    {
                        _result.Info = "参数异常";
                        _result.Result = -98;
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                    }

                    if (param.bCheckTimeout())
                    {
                        _result.Info = "请求超时";
                        _result.Result = -80;
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                    }

                    //登陆状态检查
                    CardLoginStatus loginStatus = _cardManager.CheckCardLogin(card, param.Token);
                    _result.Result = (int)loginStatus;
                    _result.Info = CardLoginStatusString.GetStatusString(loginStatus);
                    if (loginStatus != CardLoginStatus.loginSuccess)
                    {
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, card.RsaPrivateKey);
                    }

                    _cardManager.ChangeTitle(card,param.Title);

                    await _cardRepository.UpdateAsync(card);
                    _result.Result = 0;
                    _result.Info = "操作成功";
                    return new CardClientOuputDto<CardCommonOutputDto>(_result, card.RsaPrivateKey);

                }
                else
                {
                    _result.Info = "操作超时";
                    _result.Result = -101;
                    return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                }
            }
        }

        /// <summary>
        /// 暂停计费
        /// </summary>
        /// <param name="input"></param>
        /// <returns></returns>
        /// <exception cref="NotImplementedException"></exception>
        [AllowAnonymous]
        public async Task<CardClientOuputDto<CardCommonOutputDto>> PauseAsync(CardClientInputDto<CardPauseDto> input)
        {
            CardCommonOutputDto _result = new CardCommonOutputDto();
            if (input.Password.IsNullOrWhiteSpace())
            {
                _result.Info = "参数异常";
                _result.Result = -99;
                return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
            }

            var card = await _cardRepository.FindAsync(a => a.Password == input.Password.Trim());
            if (card == null)
            {
                _result.Info = "卡密无效";
                _result.Result = -100;
                return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
            }
            await using (var handle = await _abpDistributedLock.TryAcquireAsync("lockForCard:" + input.Password, new TimeSpan(0, 0, 5)))
            {
                if (handle != null)
                {
                    var param = input.getParam(card.RsaPrivateKey);
                    if (param == null)
                    {
                        _result.Info = "参数异常";
                        _result.Result = -98;
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                    }

                    if (param.bCheckTimeout())
                    {
                        _result.Info = "请求超时";
                        _result.Result = -80;
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                    }

                    //登陆状态检查
                    CardLoginStatus loginStatus = _cardManager.CheckCardLogin(card, param.Token);
                    _result.Result = (int)loginStatus;
                    _result.Info = CardLoginStatusString.GetStatusString(loginStatus);
                    if (loginStatus != CardLoginStatus.loginSuccess)
                    {
                        return new CardClientOuputDto<CardCommonOutputDto>(_result, card.RsaPrivateKey);
                    }

                    if (false == _cardManager.pause(card, param.Token))
                    {
                        _result.Result = -79;
                        _result.Info = "暂停失败";
                    }
                    else
                    {
                        _result.Result = 0;
                        _result.Info = "暂停成功并退出登陆";
                        await _cardRepository.UpdateAsync(card);
                    }

                    return new CardClientOuputDto<CardCommonOutputDto>(_result, card.RsaPrivateKey);

                }
                else
                {
                    _result.Info = "操作超时";
                    _result.Result = -101;
                    return new CardClientOuputDto<CardCommonOutputDto>(_result, null);
                }
            }
        }


    }
}
