using middleSafeServer.Localization;
using Volo.Abp.AspNetCore.Mvc;

namespace middleSafeServer.Controllers;

/* Inherit your controllers from this class.
 */
public abstract class middleSafeServerController : AbpControllerBase
{
    protected middleSafeServerController()
    {
        LocalizationResource = typeof(middleSafeServerResource);
    }
}
