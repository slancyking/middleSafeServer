using System.Threading.Tasks;

namespace middleSafeServer.Data;

public interface ImiddleSafeServerDbSchemaMigrator
{
    Task MigrateAsync();
}
