using Volo.Abp.Settings;

namespace middleSafeServer.Settings;

public class middleSafeServerSettingDefinitionProvider : SettingDefinitionProvider
{
    public override void Define(ISettingDefinitionContext context)
    {
        //Define your own settings here. Example:
        //context.Add(new SettingDefinition(middleSafeServerSettings.MySetting1));
    }
}
