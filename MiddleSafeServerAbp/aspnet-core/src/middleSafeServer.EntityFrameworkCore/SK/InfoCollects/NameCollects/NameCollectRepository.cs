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

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public class NameCollectRepository : EfCoreRepository<middleSafeServerDbContext, NameCollect, Guid>, INameCollectRepository
    {
        public NameCollectRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

        public async Task<NameCollect> FindName(string name,uint nameHash, Guid infoAgentId)
        {
            var dbSet = await GetDbSetAsync();
            return await dbSet.Where(n=>n.InfoAgentId.Equals(infoAgentId))  
                .FirstOrDefaultAsync(nameCollect => nameCollect.NameHash.Equals(nameHash)  && nameCollect.Name.Equals(name));
        }

        public async Task<EfPageList<NameCollect>> GetListAsync(int skipCount, int maxResultCount, string sorting, Guid infoAgentId, string filter = null)
        {
            EfPageList<NameCollect> result = new();
            if (string.IsNullOrWhiteSpace(sorting)) sorting = "CreationTime";
            var dbSet = await GetDbSetAsync();
            var query = dbSet.Where(i => i.InfoAgentId.Equals(infoAgentId))
                .WhereIf(!string.IsNullOrWhiteSpace( filter ),   i=>i.Name.Contains(filter));

            result.Count = await query.CountAsync();
            result.Result = await query.OrderBy(sorting)
                .Skip(skipCount)
                .Take(maxResultCount)
                .ToListAsync();
             
            return result;
        }

        public async Task<List<NameCollect>> GetNeedDownImageList(int tryCount, Guid infoAgentId)
        {
            List<NameCollect> nameCollects = new List<NameCollect>();
            var dbSet = await GetDbSetAsync();
            var query = dbSet.Where(i => i.InfoAgentId.Equals(infoAgentId) && i.FinishSaveHeadIcon.Equals(false) && i.ImageCollectId.Equals(null)
            && i.RetrySaveHeadIconCount < tryCount);

            nameCollects.AddRange(await query.ToListAsync());
            
            return nameCollects;

        }

         


    }
}
