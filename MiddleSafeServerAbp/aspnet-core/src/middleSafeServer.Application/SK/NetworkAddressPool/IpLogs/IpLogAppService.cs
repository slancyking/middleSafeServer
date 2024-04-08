using middleSafeServer.SK.Branchs;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.CommonDto;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.NetworkAddressPool.IpLogs
{
    public class IpLogAppService : middleSafeServerAppService, IIpLogAppService
    {
        private readonly ICardRepository _cardRepository;
        private readonly CardManager _cardManager;
        private readonly IIpLogRepository _ipLogRepository;
        private readonly IpLogManager _ipLogManager;
        private readonly IBranchRepository _branchRepository;

        public IpLogAppService(ICardRepository cardRepository, CardManager cardManager, IIpLogRepository ipLogRepository , IpLogManager ipLogManager) {  
            _cardRepository = cardRepository;
            _cardManager = cardManager;
            _ipLogRepository = ipLogRepository;
            _ipLogManager = ipLogManager;
        }


        public async Task<CardClientOuputDto<IpLogInputOutputDto>> TryUseIp(CardClientInputDto<IpLogInputDto> input)
        {
            if (string.IsNullOrWhiteSpace(input.Password))
                return null;
            SK.Cards.Card _card = await _cardRepository.FindAsync(c => c.Password == input.Password.Trim());
            if (_card == null)
                return new CardClientOuputDto<IpLogInputOutputDto>(new IpLogInputOutputDto() { Info = "卡密异常", Result = -100, }, null);

            var param = input.getParam(_card.RsaPrivateKey);
            if (param == null)
                return new CardClientOuputDto<IpLogInputOutputDto>(new IpLogInputOutputDto() { Result = -98, Info = "解密异常" }, _card.RsaPrivateKey);

            if (param.bCheckTimeout())
                return new CardClientOuputDto<IpLogInputOutputDto>(new IpLogInputOutputDto() { Result = -101, Info = "请求超时" }, _card.RsaPrivateKey);

            CardLoginStatus loginStatus = _cardManager.CheckCardLogin(_card, param.Token);
            if (loginStatus != CardLoginStatus.loginSuccess)
                return new CardClientOuputDto<IpLogInputOutputDto>(new IpLogInputOutputDto() { Info = "登陆状态异常", Result = -90 }, _card.RsaPrivateKey);

            var branch = await _branchRepository.FindAsync(i => i.Id.Equals(_card.BranchId));
            if (_card == null)
                return new CardClientOuputDto<IpLogInputOutputDto>(new IpLogInputOutputDto() { Info = "分支异常", Result = -95 }, _card.RsaPrivateKey);

            var result = await _ipLogManager.TryUseIpAsync(param.IpAddress, branch.ProjectId, _card.Id, param.LogMark, param.Nation, param.Province, param.City, param.District);

            return new CardClientOuputDto<IpLogInputOutputDto>(new IpLogInputOutputDto() { Info = result.Item3, Result = result.Item2 }, _card.RsaPrivateKey);
        }
    }
}
