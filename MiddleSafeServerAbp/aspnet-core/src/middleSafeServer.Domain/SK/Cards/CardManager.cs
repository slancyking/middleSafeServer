using JetBrains.Annotations;
using middleSafeServer.SK.Branchs;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Domain.Services;

namespace middleSafeServer.SK.Cards
{
    public class CardManager : DomainService
    {
        private readonly ICardRepository _cardRepository;
        private readonly IBranchRepository _branchRepository;



        public CardManager(ICardRepository cardRepository, IBranchRepository branchRepository) {
            _cardRepository = cardRepository;
            _branchRepository = branchRepository;
        }

        public async Task<List<Card>> CreateAsync(
            CardChargingMode mode,
            DateTime expiredTime, 
            Guid branchId, 
            int days,
            int count, 
            string mail, 
            string phone, 
            string remark, 
            bool enableMail,
            bool enablePhoneMsg)
        {
            List<Card> result = new List<Card>(); 
            var branch = await _branchRepository.FindAsync(branchId);
            if (branch == null)
                throw new BranchAlreadyDeleteException(branchId.ToString());


            DateTime stTime = mode == CardChargingMode.realTime ? DateTime.Now : DateTime.MinValue;
            expiredTime = mode == CardChargingMode.realTime ? DateTime.Now.AddDays(days) : expiredTime;
            for (int i = 0; i < count; i++)
            {
                var card = new Card(mode, expiredTime, GuidGenerator.Create(), GuidGenerator.Create().ToString(), stTime, days, branchId, CardStatus.UNUSE, CardType.Inner, enableMail, enablePhoneMsg, phone, mail, remark);
                result.Add(card);
            }

            return result;
        }

        public async Task<Card> ImportAsync(Guid branchId, string password, DateTime expiredTime, string phone, string mail, string remark)
        { 
            var branch = await _branchRepository.FindAsync(branchId);
            if (branch == null)
                throw new BranchAlreadyDeleteException(branchId.ToString());

            var tmpCard = await _cardRepository.FindAsync(c => c.Password == password && c.Type == CardType.Outer);
            if (tmpCard != null)
                return null;

            return new Card(CardChargingMode.realTime, expiredTime, GuidGenerator.Create(), password, DateTime.Now, 0, branchId, CardStatus.INUSE, CardType.Outer, false, false, phone, mail, remark);
        }


        public void ChangeTitle(
            [NotNull] Card card,
            [NotNull] string title)
        {
            Check.NotNull(card, nameof(card));
            card.ChangeTitle(title);
        }

        public void ChangePassword(
            [NotNull] Card card,
            [NotNull] string newPassword)
        {
            Check.NotNull(card, nameof(card)); 
            card.ChangePassword(newPassword);
        }

        public void ChangeMail(
           [NotNull] Card card,
           [NotNull] string email)
        {
            Check.NotNull(card, nameof(card));
            card.ChangeMail(email);
        }

        public void ChangePhone(
           [NotNull] Card card,
           [NotNull] string phone)
        {
            Check.NotNull(card, nameof(card));
            card.ChangePhone(phone);
        }

        public void AddDays([NotNull] Card card,
           [NotNull] int days)
        {
            Check.NotNull(card, nameof(card));
            int newDay = days + card.Days;
            if (newDay > SKConsts.MaxCardDays)
                throw new CardDaysOutRangeException(newDay, SKConsts.MaxCardDays);

            card.AddDays(days);
        }

        public CardLoginStatus CheckCardLogin([NotNull] Card card, [NotNull] string token)
        {
            Check.NotNull(card, nameof(card)); 
            Check.NotNullOrWhiteSpace(token, nameof(token));
            return card.checkLogin(token); 
        }

        public CardLoginStatus Login([NotNull] Card card) {
            Check.NotNull(card, nameof(card)); 
            return card.Login();
        }

        public bool CardLogout([NotNull] Card card, [NotNull] string token) {
            Check.NotNull(card, nameof(card));
            Check.NotNullOrWhiteSpace(token, nameof(token));

            if (card.checkLogin(token) != CardLoginStatus.loginSuccess)
                return false;
             
            return card.Logout();
        }

        public bool pause([NotNull] Card card, [NotNull] string token) {
            Check.NotNull(card, nameof(card));
            Check.NotNullOrWhiteSpace(token, nameof(token));

            if (card.checkLogin(token) != CardLoginStatus.loginSuccess)
                return false;

            card.pause();
            return true;
        }


        public void Ping([NotNull] Card card) {
            Check.NotNull(card, nameof(card));
            var _5Minutes = Clock.Now.Add(TimeSpan.FromMinutes(5));
            if (card.LoginOvertime < _5Minutes)
                card.LoginOvertime = DateTime.Now.AddMinutes(5);
            DateTime _now = DateTime.Now;
            card.SurplusSecond -= (long)(_now - card.LastPingTime).TotalSeconds;
            card.LastPingTime = _now;
            
        }



    }
}
