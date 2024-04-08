using Volo.Abp.DependencyInjection;
using Volo.Abp.Ui.Branding;

namespace middleSafeServer;

[Dependency(ReplaceServices = true)]
public class middleSafeServerBrandingProvider : DefaultBrandingProvider
{
    public override string AppName => "middleSafeServer";
}
