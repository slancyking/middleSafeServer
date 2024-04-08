using middleSafeServer.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories.EntityFrameworkCore;
using Volo.Abp.EntityFrameworkCore;

namespace middleSafeServer.SK.InfoCollects.NameCollectCounts
{
    public class NameCollectCountRepository : EfCoreRepository<middleSafeServerDbContext, NameCollectCount, Guid>, INameCollectCountRepository
    {
        public NameCollectCountRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }
    }
}
