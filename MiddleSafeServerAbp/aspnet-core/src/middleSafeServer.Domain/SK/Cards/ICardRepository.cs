
using middleSafeServer.SK.Cards;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.Cards
{
    public interface ICardRepository : IRepository<Card, Guid>
    {  
        public Task<EfPageList<Card>> FindCards(int skipCount, int maxResultCount, string sorting, string filter, Guid? BranchId, string mail, string phone, Guid? CreateorId);
         
    }
}
