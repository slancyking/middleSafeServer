using Microsoft.Extensions.DependencyInjection;
using middleSafeServer.BackgroundWorker;
using Volo.Abp;
using Volo.Abp.Account;
using Volo.Abp.AutoMapper;
using Volo.Abp.BackgroundWorkers;
using Volo.Abp.Emailing;
using Volo.Abp.FeatureManagement;
using Volo.Abp.Identity;
using Volo.Abp.Modularity;
using Volo.Abp.PermissionManagement;
using Volo.Abp.SettingManagement;
using Volo.Abp.TenantManagement;

namespace middleSafeServer;

[DependsOn(
    typeof(middleSafeServerDomainModule),
    typeof(AbpAccountApplicationModule),
    typeof(middleSafeServerApplicationContractsModule),
    typeof(AbpIdentityApplicationModule),
    typeof(AbpPermissionManagementApplicationModule),
    typeof(AbpTenantManagementApplicationModule),
    typeof(AbpFeatureManagementApplicationModule),
    typeof(AbpSettingManagementApplicationModule),
    typeof(AbpBackgroundWorkersModule),
    typeof(AbpAutoMapperModule),
    typeof(AbpEmailingModule)
    )]
public class middleSafeServerApplicationModule : AbpModule
{ 

    public override void ConfigureServices(ServiceConfigurationContext context)
    {
        Configure<AbpAutoMapperOptions>(options =>
        {
            options.AddMaps<middleSafeServerApplicationModule>();
        });
        


    }

    public override void OnApplicationInitialization(ApplicationInitializationContext context)
    { 

        context.AddBackgroundWorkerAsync<ClearMiddleReportWorker>();
        context.AddBackgroundWorkerAsync<CollectDroppedUsersWorker>();
        context.AddBackgroundWorkerAsync<DownLoadImageForCollectWorker>();
        
        base.OnApplicationInitialization(context);
         
    }

    public override void OnPostApplicationInitialization(ApplicationInitializationContext context)
    {
        base.OnPostApplicationInitialization(context);
    }


}
