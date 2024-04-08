using Microsoft.AspNetCore.Mvc;
using middleSafeServer.Localization;
using Volo.Abp.AspNetCore.Mvc;

namespace middleSafeServer.Controllers;

public class HomeController : AbpController
{
    public ActionResult Index()
    {
        LocalizationResource = typeof(middleSafeServerResource);
        return Redirect("~/swagger");
    }
}
