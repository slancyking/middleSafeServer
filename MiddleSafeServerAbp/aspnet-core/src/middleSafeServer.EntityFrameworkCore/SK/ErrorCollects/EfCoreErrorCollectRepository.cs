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

namespace middleSafeServer.SK.ErrorCollects
{
    public class EfCoreErrorCollectRepository : EfCoreRepository<middleSafeServerDbContext, ErrorCollect, Guid>, IErrorCollectRepository
    {
        public EfCoreErrorCollectRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

        public async Task DeleteSameErrorById(Guid id)
        { 
            var errorCollect = await FindAsync(id);

            if (errorCollect == null) return;

            await DeleteAsync(i => i.ErrorTitle.Equals(errorCollect.ErrorTitle) && i.ErrorMessage.Equals(errorCollect.ErrorMessage), true);
        }

        public async Task<EfPageList<ErrorCollect>> GetListAsync(int skipCount, int maxResultCount, string sorting, string errorTitle = null, Guid? branchId = null, string errMessage = null)
        {
            EfPageList<ErrorCollect> result = new();

            var dbSet = await GetDbSetAsync();
            var query = dbSet
                .WhereIf(
                  branchId != null,
                  err => err.BranchId == branchId
                )
                .WhereIf(
                    !errorTitle.IsNullOrWhiteSpace(),
                    err => err.ErrorTitle.Equals(errorTitle)
                 ).WhereIf(
                    !errMessage.IsNullOrWhiteSpace(),
                    err => err.ErrorMessage.Equals(errMessage)
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
