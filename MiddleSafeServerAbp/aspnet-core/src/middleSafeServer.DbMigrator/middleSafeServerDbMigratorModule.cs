using middleSafeServer.EntityFrameworkCore;
using Volo.Abp.Autofac;
using Volo.Abp.BackgroundJobs;
using Volo.Abp.Modularity;

namespace middleSafeServer.DbMigrator;

[DependsOn(
    typeof(AbpAutofacModule),
    typeof(middleSafeServerEntityFrameworkCoreModule),
    typeof(middleSafeServerApplicationContractsModule)
    )]
public class middleSafeServerDbMigratorModule : AbpModule
{
    public override void ConfigureServices(ServiceConfigurationContext context)
    {
        Configure<AbpBackgroundJobOptions>(options => options.IsJobExecutionEnabled = false);
    }
}
