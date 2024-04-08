using Volo.Abp.Modularity;

namespace middleSafeServer;

[DependsOn(
    typeof(middleSafeServerApplicationModule),
    typeof(middleSafeServerDomainTestModule)
    )]
public class middleSafeServerApplicationTestModule : AbpModule
{

}
