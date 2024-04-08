using middleSafeServer.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories.EntityFrameworkCore;
using Volo.Abp.EntityFrameworkCore;

namespace middleSafeServer.SK.WebSettings
{
    public class EfCoreWebSettingRepository : EfCoreRepository<middleSafeServerDbContext, WebSetting, Guid>, IWebSettingRepository
    {
        public EfCoreWebSettingRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }
    }
}
