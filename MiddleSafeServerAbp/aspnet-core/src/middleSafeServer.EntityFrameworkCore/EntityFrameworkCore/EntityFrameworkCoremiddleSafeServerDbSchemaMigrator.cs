using System;
using System.Threading.Tasks;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.DependencyInjection;
using middleSafeServer.Data;
using Volo.Abp.DependencyInjection;

namespace middleSafeServer.EntityFrameworkCore;

public class EntityFrameworkCoremiddleSafeServerDbSchemaMigrator
    : ImiddleSafeServerDbSchemaMigrator, ITransientDependency
{
    private readonly IServiceProvider _serviceProvider;

    public EntityFrameworkCoremiddleSafeServerDbSchemaMigrator(
        IServiceProvider serviceProvider)
    {
        _serviceProvider = serviceProvider;
    }

    public async Task MigrateAsync()
    {
        /* We intentionally resolving the middleSafeServerDbContext
         * from IServiceProvider (instead of directly injecting it)
         * to properly get the connection string of the current tenant in the
         * current scope.
         */

        await _serviceProvider
            .GetRequiredService<middleSafeServerDbContext>()
            .Database
            .MigrateAsync();
    }
}
