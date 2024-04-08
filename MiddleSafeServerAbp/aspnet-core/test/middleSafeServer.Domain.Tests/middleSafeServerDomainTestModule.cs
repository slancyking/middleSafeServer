using middleSafeServer.EntityFrameworkCore;
using Volo.Abp.Modularity;

namespace middleSafeServer;

[DependsOn(
    typeof(middleSafeServerEntityFrameworkCoreTestModule)
    )]
public class middleSafeServerDomainTestModule : AbpModule
{

}
