using System.Threading.Tasks;
using Volo.Abp.DependencyInjection;

namespace middleSafeServer.Data;

/* This is used if database provider does't define
 * ImiddleSafeServerDbSchemaMigrator implementation.
 */
public class NullmiddleSafeServerDbSchemaMigrator : ImiddleSafeServerDbSchemaMigrator, ITransientDependency
{
    public Task MigrateAsync()
    {
        return Task.CompletedTask;
    }
}
