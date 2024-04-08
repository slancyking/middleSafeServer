using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.InfoAgents
{
    public interface IInfoAgentRepository : IRepository<InfoAgent, Guid>
    {
        Task<InfoAgent> FindByNameAsync(string name);

        Task<EfPageList<InfoAgent>> GetListAsync(
            int skipCount,
            int maxResultCount,
            string sorting,
            string filter = null
        );




    }
}
