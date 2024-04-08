using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.Branchs
{
    public interface IBranchRepository : IRepository<Branch, Guid>
    {
        Task<Branch> FindByNameAsync(string name);

        Task<EfPageList<Branch>> GetListAsync(
            int skipCount,
            int maxResultCount,
            string sorting,
            Guid? projectId = null,
            string filter = null
        );
    }
}
