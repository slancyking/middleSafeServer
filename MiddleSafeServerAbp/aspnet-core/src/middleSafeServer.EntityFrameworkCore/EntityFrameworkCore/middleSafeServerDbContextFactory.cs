using System;
using System.IO;
using Microsoft.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore.Design;
using Microsoft.EntityFrameworkCore.Migrations;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using middleSafeServer.Routes;
using ShardingCore;

namespace middleSafeServer.EntityFrameworkCore;

/* This class is needed for EF Core console commands
 * (like Add-Migration and Update-Database commands) */
public class middleSafeServerDbContextFactory : IDesignTimeDbContextFactory<middleSafeServerDbContext>
{
    private static IServiceProvider _serviceProvider;
    static middleSafeServerDbContextFactory()
    {
        var c = BuildConfiguration();
        var services = new ServiceCollection();

        services.AddShardingDbContext<middleSafeServerDbContext>()
            .UseRouteConfig(op =>
            { 
                op.AddShardingTableRoute<NameCollectHashRangeVirtualTableRoute>();
                op.AddShardingTableRoute<ImageCollectHashRangeVirtualTableRoute>();
            })
            .UseConfig((sp, op) =>
            {
                op.ThrowIfQueryRouteNotMatch = false;
                op.UseShardingQuery((conStr, builder) =>
                {
                    builder.UseSqlServer(conStr);
                });
                op.UseShardingTransaction((connection, builder) =>
                {
                    builder.UseSqlServer(connection);
                });
                op.UseShardingMigrationConfigure(builder =>
                {
                    builder.ReplaceService<IMigrationsSqlGenerator, ShardingSqlServerMigrationsSqlGenerator>();
                });
                op.AddDefaultDataSource("ds0", c.GetConnectionString("Default")); 
            })
            .AddShardingCore();
        _serviceProvider = services.BuildServiceProvider();
    }


    public middleSafeServerDbContext CreateDbContext(string[] args)
    {
        middleSafeServerEfCoreEntityExtensionMappings.Configure();
         
        return _serviceProvider.GetService<middleSafeServerDbContext>();
    }

    private static IConfigurationRoot BuildConfiguration()
    {
        var builder = new ConfigurationBuilder()
            .SetBasePath(Path.Combine(Directory.GetCurrentDirectory(), "../middleSafeServer.DbMigrator/"))
            .AddJsonFile("appsettings.json", optional: false);

        return builder.Build();
    }
}
