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


namespace middleSafeServer.SK.Projects
{
    public class EfCoreProjectRepository : EfCoreRepository<middleSafeServerDbContext, Project, Guid>, IProjectRepository
    {
        public EfCoreProjectRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

        public async Task<Project> FindByNameAsync(string name)
        {
            var dbSet = await GetDbSetAsync();
            return await dbSet.FirstOrDefaultAsync(project => project.Name == name);
        }

        public async Task<EfPageList<Project>> GetListAsync(int skipCount, int maxResultCount, string sorting, string filter = null)
        {

            EfPageList<Project> result = new();

            var dbSet = await GetDbSetAsync();
            var query = dbSet
                .WhereIf(
                    !filter.IsNullOrWhiteSpace(),
                    project => project.Name.Contains(filter)
                 );

            result.Count = query.Count();
            result.Result = await query
                .OrderBy(sorting)
                .Skip(skipCount)
                .Take(maxResultCount)
                .ToListAsync();
             
            return result;

        }
    }
}
