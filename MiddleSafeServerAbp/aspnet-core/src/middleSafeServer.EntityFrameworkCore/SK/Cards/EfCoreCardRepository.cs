using Microsoft.EntityFrameworkCore;
using middleSafeServer.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories.EntityFrameworkCore;
using Volo.Abp.EntityFrameworkCore;
using System.Linq.Dynamic.Core;

namespace middleSafeServer.SK.Cards
{
    public class EfCoreCardRepository : EfCoreRepository<middleSafeServerDbContext, Card, Guid>, ICardRepository
    {
        public EfCoreCardRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

         
        public async Task<EfPageList<Card>> FindCards(int skipCount, int maxResultCount, string sorting, string filter , Guid? BranchId, string mail, string phone, Guid? CreateorId)
        {
            EfPageList<Card> result = new();
            if (string.IsNullOrWhiteSpace(sorting)) sorting = "CreationTime";
            var dbSet = await GetDbSetAsync();
            var query = dbSet
                        .WhereIf( !filter.IsNullOrWhiteSpace(), branch => branch.Password.Contains(filter))
                        .WhereIf(BranchId != null, card => card.BranchId == BranchId)
                        .WhereIf(CreateorId != null, card => card.CreatorId == CreateorId)
                        .WhereIf(!string.IsNullOrWhiteSpace(mail), card => card.Mail.Contains(mail))
                        .WhereIf(!string.IsNullOrWhiteSpace(phone), card => card.Phone.Contains(phone));

            result.Count = await query.CountAsync();
            result.Result = await query.OrderBy(sorting)
                .Skip(skipCount)
                .Take(maxResultCount)
                .ToListAsync();


            return result;

        }
    }
}
