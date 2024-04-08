using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.ErrorCollects
{
    public interface IErrorCollectRepository : IRepository<ErrorCollect, Guid>
    {

        Task DeleteSameErrorById(Guid id);


        Task<EfPageList<ErrorCollect>> GetListAsync(
            int skipCount,
            int maxResultCount,
            string sorting,
            string errorTitle = null,
            Guid? branchId = null,
            string errMessage = null
        );
    }
}
