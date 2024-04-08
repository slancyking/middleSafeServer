using Microsoft.EntityFrameworkCore;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using middleSafeServer.SK.InfoCollects.NameCollects;
using Volo.Abp.Identity;
using Volo.Abp.ObjectExtending;
using Volo.Abp.Threading;

namespace middleSafeServer.EntityFrameworkCore;

public static class middleSafeServerEfCoreEntityExtensionMappings
{
    private static readonly OneTimeRunner OneTimeRunner = new OneTimeRunner();

    public static void Configure()
    {
        middleSafeServerGlobalFeatureConfigurator.Configure();
        middleSafeServerModuleExtensionConfigurator.Configure();

        OneTimeRunner.Run(() =>
        {
            /* You can configure extra properties for the
             * entities defined in the modules used by your application.
             *
             * This class can be used to map these extra properties to table fields in the database.
             *
             * USE THIS CLASS ONLY TO CONFIGURE EF CORE RELATED MAPPING.
             * USE middleSafeServerModuleExtensionConfigurator CLASS (in the Domain.Shared project)
             * FOR A HIGH LEVEL API TO DEFINE EXTRA PROPERTIES TO ENTITIES OF THE USED MODULES
             *
             * Example: Map a property to a table field:

                 ObjectExtensionManager.Instance
                     .MapEfCoreProperty<IdentityUser, string>(
                         "MyProperty",
                         (entityBuilder, propertyBuilder) =>
                         {
                             propertyBuilder.HasMaxLength(128);
                         }
                     );

             * See the documentation for more:
             * https://docs.abp.io/en/abp/latest/Customizing-Application-Modules-Extending-Entities
             */

            ObjectExtensionManager.Instance
                    .MapEfCoreProperty<NameCollect, string>(
                        "MyProperty",
                        (entityBuilder, propertyBuilder) =>
                        {
                            propertyBuilder.HasMaxLength(128);
                        }
                    )
                    .MapEfCoreProperty<NameCollect, string>(
                        "MyProperty1",
                        (entityBuilder, propertyBuilder) =>
                        {
                            propertyBuilder.HasMaxLength(128);
                        }
                    );
            ObjectExtensionManager.Instance
                    .MapEfCoreProperty<ImageCollect, string>(
                        "MyProperty",
                        (entityBuilder, propertyBuilder) =>
                        {
                            propertyBuilder.HasMaxLength(128);
                        }
                    )
                    .MapEfCoreProperty<ImageCollect, string>(
                        "MyProperty1",
                        (entityBuilder, propertyBuilder) =>
                        {
                            propertyBuilder.HasMaxLength(128);
                        }
                    );
        });
    }
}
