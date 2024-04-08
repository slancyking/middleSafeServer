using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    public interface INameCollectRepository : IRepository<NameCollect, Guid>
    {   

        Task<NameCollect> FindName(string name, uint nameHash,
            Guid infoAgentId
            );

        Task<List<NameCollect>> GetNeedDownImageList(int tryCount, Guid infoAgentId);


        Task<EfPageList<NameCollect>> GetListAsync(
            int skipCount,
            int maxResultCount, 
            string sorting,
            Guid infoAgentId,
            string filter = null
        );  
    }
}
