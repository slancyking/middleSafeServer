using System;
using Microsoft.Extensions.DependencyInjection;
using Volo.Abp.AuditLogging.EntityFrameworkCore;
using Volo.Abp.BackgroundJobs.EntityFrameworkCore;
using Volo.Abp.EntityFrameworkCore; 
using Volo.Abp.FeatureManagement.EntityFrameworkCore;
using Volo.Abp.Identity.EntityFrameworkCore;
using Volo.Abp.IdentityServer.EntityFrameworkCore;
using Volo.Abp.Modularity;
using Volo.Abp.PermissionManagement.EntityFrameworkCore;
using Volo.Abp.SettingManagement.EntityFrameworkCore;
using Volo.Abp.TenantManagement.EntityFrameworkCore;


using ShardingCore;
using ShardingCore.Bootstrappers;
using ShardingCore.Core.DbContextCreator;
using ShardingCore.Core.RuntimeContexts;
using ShardingCore.TableExists;
using ShardingCore.TableExists.Abstractions;
using Microsoft.Extensions.Logging;
using Microsoft.EntityFrameworkCore;
using middleSafeServer.Routes;
using Microsoft.EntityFrameworkCore.Migrations;
using Volo.Abp.EntityFrameworkCore.MySQL;
using Volo.Abp;
using middleSafeServer.SK.InfoCollects.NameCollects;
using Microsoft.Extensions.Configuration;

namespace middleSafeServer.EntityFrameworkCore;

[DependsOn(
    typeof(middleSafeServerDomainModule),
    typeof(AbpIdentityEntityFrameworkCoreModule),
    typeof(AbpIdentityServerEntityFrameworkCoreModule),
    typeof(AbpPermissionManagementEntityFrameworkCoreModule),
    typeof(AbpSettingManagementEntityFrameworkCoreModule),
    typeof(AbpEntityFrameworkCoreMySQLModule),
    typeof(AbpBackgroundJobsEntityFrameworkCoreModule),
    typeof(AbpAuditLoggingEntityFrameworkCoreModule),
    typeof(AbpTenantManagementEntityFrameworkCoreModule),
    typeof(AbpFeatureManagementEntityFrameworkCoreModule)
    )]
public class middleSafeServerEntityFrameworkCoreModule : AbpModule
{  


    public static readonly ILoggerFactory efLogger = LoggerFactory.Create(builder =>
    {
        builder.AddFilter((category, level) => category == DbLoggerCategory.Database.Command.Name && level == LogLevel.Information).AddConsole();
    });

    public override void PreConfigureServices(ServiceConfigurationContext context)
    {
        middleSafeServerEfCoreEntityExtensionMappings.Configure();
    }


    public override async void OnPostApplicationInitialization(ApplicationInitializationContext context)
    { 
        base.OnPostApplicationInitialization(context);
        using (var scope = context.ServiceProvider.CreateScope())
        {
            var defaultDbContext = scope.ServiceProvider.GetService<middleSafeServerDbContext>(); 
            //var nameCollect = new NameCollect(Guid.NewGuid(), Guid.NewGuid(), "收集名字1", 1, null, "baidu.com/pic1.img", "{}");
            //var nameCollect2 = new NameCollect(Guid.NewGuid(), Guid.NewGuid(), "收集名字2", 1, null, "baidu.com/pic2.img", "{}");

            //await defaultDbContext.AddAsync(nameCollect);
            //await defaultDbContext.AddAsync(nameCollect2);

            //await defaultDbContext.SaveChangesAsync();
        }

    }


    public override void ConfigureServices(ServiceConfigurationContext context)
    {
        //context.Services.AddShardingDbContext<middleSafeServerDbContext>();



        context.Services.AddAbpDbContext<middleSafeServerDbContext>(options =>
        {
            /* Remove "includeAllEntities: true" to create
             * default repositories only for aggregate roots */
            options.AddDefaultRepositories(includeAllEntities: true);
        });

        Configure<AbpDbContextOptions>(options =>
        {
            /* The main point to change your DBMS.
             * See also middleSafeServerMigrationsDbContextFactory for EF Core tooling. */
            options.UseSqlServer();
            options.Configure<middleSafeServerDbContext>(innerContext =>
            {
                innerContext.DbContextOptions.UseDefaultSharding<middleSafeServerDbContext>(innerContext.ServiceProvider);
            });
        });
        context.Services.AddShardingConfigure<middleSafeServerDbContext>()
        .UseRouteConfig(op =>
        {
            op.AddShardingTableRoute<NameCollectHashRangeVirtualTableRoute>();
            op.AddShardingTableRoute<ImageCollectHashRangeVirtualTableRoute>();
            
        })
        .UseConfig((sp, op) =>
        {
            op.ThrowIfQueryRouteNotMatch = false;
            var configuration=sp.GetRequiredService<IConfiguration>();
            op.IgnoreCreateTableError = false;
            op.AddDefaultDataSource("ds0", configuration.GetConnectionString("Default"));
            op.UseShardingQuery((conStr, builder) =>
            {
                builder.UseSqlServer(conStr).UseLoggerFactory(efLogger);
            });
            op.UseShardingTransaction((connection, builder) =>
            {
                builder.UseSqlServer(connection).UseLoggerFactory(efLogger);
            });
            op.UseShardingMigrationConfigure(o =>
            {
                o.ReplaceService<IMigrationsSqlGenerator, ShardingSqlServerMigrationsSqlGenerator>();
            });
            

        }).AddShardingCore();

    }
}
