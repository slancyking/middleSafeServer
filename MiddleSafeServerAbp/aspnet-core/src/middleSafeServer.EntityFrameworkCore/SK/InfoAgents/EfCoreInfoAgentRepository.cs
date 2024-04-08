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


namespace middleSafeServer.SK.InfoAgents
{
    public class EfCoreInfoAgentRepository : EfCoreRepository<middleSafeServerDbContext, InfoAgent, Guid>, IInfoAgentRepository 
    {
        public EfCoreInfoAgentRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

        public async Task<InfoAgent> FindByNameAsync(string name)
        {
            var dbSet = await GetDbSetAsync();
            return await dbSet.FirstOrDefaultAsync(branch => branch.Name == name);
        }

        public async Task<EfPageList<InfoAgent>> GetListAsync(int skipCount, int maxResultCount, string sorting, string filter = null)
        {
            EfPageList<InfoAgent> result = new();
             
            var dbSet = await GetDbSetAsync();
            var query = dbSet .WhereIf(
                    !filter.IsNullOrWhiteSpace(),
                    branch => branch.Name.Contains(filter)
                 );

            result.Count = await query.CountAsync();
            result.Result = await query.OrderBy(sorting)
                .Skip(skipCount)
                .Take(maxResultCount)
                .ToListAsync();
            return result;
        }
    }
}
