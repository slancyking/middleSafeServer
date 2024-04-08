using System;
using System.Collections.Generic;
using System.Text;
using middleSafeServer.Localization;
using Volo.Abp.Application.Services;

namespace middleSafeServer;

/* Inherit your application services from this class.
 */
public abstract class middleSafeServerAppService : ApplicationService
{
    protected middleSafeServerAppService()
    {
        LocalizationResource = typeof(middleSafeServerResource);
    }
}
