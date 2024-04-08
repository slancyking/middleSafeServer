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


namespace middleSafeServer.SK.Branchs
{
    public class EfCoreBranchRepository : EfCoreRepository<middleSafeServerDbContext, Branch, Guid>, IBranchRepository
    {
        public EfCoreBranchRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

        public async Task<Branch> FindByNameAsync(string name)
        {
            var dbSet = await GetDbSetAsync();
            return await dbSet.FirstOrDefaultAsync(branch => branch.Name == name);
        }

        public async Task<EfPageList<Branch>> GetListAsync(int skipCount, int maxResultCount, string sorting, Guid? projectId = null, string filter = null)
        {
            EfPageList<Branch> result = new();
             
            var dbSet = await GetDbSetAsync();
            var query = dbSet
                .WhereIf(
                  projectId != null,
                  branch => branch.ProjectId == projectId
                )
                .WhereIf(
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
