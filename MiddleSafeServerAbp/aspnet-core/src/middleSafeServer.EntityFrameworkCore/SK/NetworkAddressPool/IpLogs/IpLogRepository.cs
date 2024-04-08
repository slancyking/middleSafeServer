using middleSafeServer.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories.EntityFrameworkCore;
using Volo.Abp.EntityFrameworkCore;

namespace middleSafeServer.SK.NetworkAddressPool.IpLogs
{
    public class IpLogRepository : EfCoreRepository<middleSafeServerDbContext, IpLog, Guid>, IIpLogRepository
    {
        public IpLogRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }
    }
}
