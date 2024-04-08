using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.NetworkAddressPool.IpLogs
{
    public interface IIpLogRepository : IRepository<IpLog, Guid>
    {    

    }
}
