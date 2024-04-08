using middleSafeServer.Localization;
using Volo.Abp.Authorization.Permissions;
using Volo.Abp.Localization;
 

namespace middleSafeServer.Permissions;

public class middleSafeServerPermissionDefinitionProvider : PermissionDefinitionProvider
{



    public override void Define(IPermissionDefinitionContext context)
    {
        


        var Group_PropCollect = context.AddGroup(middleSafeServerPermissions.Group_PropCollect);
        Group_PropCollect.AddPermission(middleSafeServerPermissions.PropCollectQuery, L("Permission:PropCollectQuery"));

        var Group_Card = context.AddGroup(middleSafeServerPermissions.Group_Card);
        Group_Card.AddPermission(middleSafeServerPermissions.CardCreate, L("Permission:CreateCard"));
        Group_Card.AddPermission(middleSafeServerPermissions.CardUpdate, L("Permission:EditCard"));
        Group_Card.AddPermission(middleSafeServerPermissions.CardGetSingle, L("Permission:GetSingleCard"));
        Group_Card.AddPermission(middleSafeServerPermissions.CardGetList, L("Permission:GetListCard"));
        Group_Card.AddPermission(middleSafeServerPermissions.CardDelete, L("Permission:CardDelete"));

        Group_Card.AddPermission(middleSafeServerPermissions.CardImport, L("Permission:CardImport"));
        Group_Card.AddPermission(middleSafeServerPermissions.CardFull, L("Permission:CardFull"));

  
        var Group_CardMsg = context.AddGroup(middleSafeServerPermissions.Group_CardMsg);
        Group_CardMsg.AddPermission(middleSafeServerPermissions.CardMsgDelete, L("Permission:DeleteCardMsg"));
        Group_CardMsg.AddPermission(middleSafeServerPermissions.CardMsgSetRead, L("Permission:SetReadCardMsg"));
        Group_CardMsg.AddPermission(middleSafeServerPermissions.CardMsgGetList, L("Permission:GetListCardMsg"));

        var Group_WebSetting = context.AddGroup(middleSafeServerPermissions.Group_WebSetting);
        Group_WebSetting.AddPermission(middleSafeServerPermissions.WebSettingGet, L("Permission:WebSettingGet"));
        Group_WebSetting.AddPermission(middleSafeServerPermissions.WebSettingUpdate, L("Permission:WebSettingUpdate"));


        var Group_Project = context.AddGroup(middleSafeServerPermissions.Group_Project);
        Group_Project.AddPermission(middleSafeServerPermissions.ProjectCreate, L("Permission:ProjectCreate"));
        Group_Project.AddPermission(middleSafeServerPermissions.ProjectUpdate, L("Permission:ProjectUpdate"));
        Group_Project.AddPermission(middleSafeServerPermissions.ProjectGetList, L("Permission:ProjectGetList"));
        Group_Project.AddPermission(middleSafeServerPermissions.ProjectDelete, L("Permission:ProjectDelete"));
        Group_Project.AddPermission(middleSafeServerPermissions.ProjectGet, L("Permission:ProjectGet"));

        var Group_Branch = context.AddGroup(middleSafeServerPermissions.Group_Branch);
        Group_Branch.AddPermission(middleSafeServerPermissions.BranchCreate, L("Permission:BranchCreate"));
        Group_Branch.AddPermission(middleSafeServerPermissions.BranchUpdate, L("Permission:BranchUpdate"));
        Group_Branch.AddPermission(middleSafeServerPermissions.BranchGetList, L("Permission:BranchGetList"));
        Group_Branch.AddPermission(middleSafeServerPermissions.BranchDelete, L("Permission:BranchDelete"));
        Group_Branch.AddPermission(middleSafeServerPermissions.BranchGet, L("Permission:BranchGet"));
        var authorManagement = Group_Branch.AddPermission("BranchChileManager");

        var Group_InfoAgent = context.AddGroup(middleSafeServerPermissions.Group_InfoAgent);
        Group_InfoAgent.AddPermission(middleSafeServerPermissions.InfoAgentCreate, L("Permission:InfoAgentCreate"));
        Group_InfoAgent.AddPermission(middleSafeServerPermissions.InfoAgentUpdate, L("Permission:InfoAgentUpdate"));
        Group_InfoAgent.AddPermission(middleSafeServerPermissions.InfoAgentGetList, L("Permission:InfoAgentGetList"));
        Group_InfoAgent.AddPermission(middleSafeServerPermissions.InfoAgentDelete, L("Permission:InfoAgentDelete"));
        Group_InfoAgent.AddPermission(middleSafeServerPermissions.InfoAgentGet, L("Permission:InfoAgentGet"));


        var Group_ErrorCollect = context.AddGroup(middleSafeServerPermissions.Group_ErrorCollect); 
        Group_ErrorCollect.AddPermission(middleSafeServerPermissions.ErrorCollectUpdate, L("Permission:ErrorCollectUpdate"));
        Group_ErrorCollect.AddPermission(middleSafeServerPermissions.ErrorCollectGetList, L("Permission:ErrorCollectGetList"));
        Group_ErrorCollect.AddPermission(middleSafeServerPermissions.ErrorCollectDelete, L("Permission:ErrorCollectDelete"));
        Group_ErrorCollect.AddPermission(middleSafeServerPermissions.ErrorCollectDeleteSame, L("Permission:ErrorCollectDelete"));
        Group_ErrorCollect.AddPermission(middleSafeServerPermissions.ErrorCollectGet, L("Permission:ErrorCollectGet"));


        var GroupNameCollect = context.AddGroup(middleSafeServerPermissions.Group_NameCollect);
        GroupNameCollect.AddPermission(middleSafeServerPermissions.NameCollectCreate, L("Permission:NameCollectCreate"));
        GroupNameCollect.AddPermission(middleSafeServerPermissions.NameCollectGetList, L("Permission:NameCollectGetList"));
        GroupNameCollect.AddPermission(middleSafeServerPermissions.NameCollectDelete, L("Permission:NameCollectDelete"));
        GroupNameCollect.AddPermission(middleSafeServerPermissions.NameCollectUpdate, L("Permission:NameCollectUpdate"));
        GroupNameCollect.AddPermission(middleSafeServerPermissions.NameCollectGet, L("Permission:NameCollectGet"));

    }

    private static LocalizableString L(string name)
    {
        return LocalizableString.Create<middleSafeServerResource>(name);
    }
}
