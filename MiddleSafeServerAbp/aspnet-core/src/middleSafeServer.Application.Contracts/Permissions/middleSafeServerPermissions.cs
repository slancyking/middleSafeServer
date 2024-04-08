namespace middleSafeServer.Permissions;

public static class middleSafeServerPermissions
{
    //Add your own permission names. Example:
    //public const string MyPermission1 = GroupName + ".MyPermission1";
    public const string Group_PropCollect = "PropCollectPermissions"; 
    public const string PropCollectQuery = Group_PropCollect + ".Query";


    public const string Group_Card = "CardPermissions"; 
    public const string CardCreate = Group_Card + ".Create";
    public const string CardUpdate = Group_Card + ".Update";
    public const string CardGetSingle = Group_Card + ".GetSingle";
    public const string CardGetList = Group_Card + ".GetList";
    public const string CardDelete = Group_Card + ".Delete";
    public const string CardImport = Group_Card + ".Import";

    public const string CardFull = Group_Card + ".CardFull";


    public const string Group_ExtendCard = "ExtendCardPermissions";
    public const string ExtendCardCreate = Group_ExtendCard + ".Create";
    public const string ExtendCardUpdate = Group_ExtendCard + ".Update";
    public const string ExtendCardGetSingle = Group_ExtendCard + ".GetSingle";
    public const string ExtendCardGetList = Group_ExtendCard + ".GetList";


    public const string Group_CardMsg = "CardMsgPermissions";
    public const string CardMsgDelete = Group_CardMsg + ".Delete";
    public const string CardMsgSetRead = Group_CardMsg + ".SetRead";
    public const string CardMsgGetList = Group_CardMsg + ".GetList";


    public const string Group_WebSetting = "WebSettingPermissions";
    public const string WebSettingGet = Group_WebSetting + ".Get";
    public const string WebSettingUpdate = Group_WebSetting + ".Update";


    //项目管理 
    public const string Group_Project = "ProjectPermissions";
    public const string ProjectCreate = Group_Project + ".Create";
    public const string ProjectUpdate = Group_Project + ".Update";
    public const string ProjectGet = Group_Project + ".Get";
    public const string ProjectGetList = Group_Project + ".GetList";
    public const string ProjectDelete = Group_Project + ".Delete";

    //项目分支管理 
    public const string Group_Branch = "BranchPermissions";
    public const string BranchCreate = Group_Branch + ".Create";
    public const string BranchUpdate = Group_Branch + ".Update";
    public const string BranchGet = Group_Branch + ".Get";
    public const string BranchGetList = Group_Branch + ".GetList";
    public const string BranchDelete = Group_Branch + ".Delete";

    //子分支管理
    public const string BranchChileManager = Group_Branch + ".Chile";

    //项目权限元组
    public const string projectGroup = "ProjectPermission";


    //信息收集渠道
    public const string Group_InfoAgent = "InfoAgentPermissions";
    public const string InfoAgentCreate = Group_InfoAgent + ".Create"; 
    public const string InfoAgentUpdate = Group_InfoAgent + ".Update";
    public const string InfoAgentGet = Group_InfoAgent + ".Get";
    public const string InfoAgentGetList = Group_InfoAgent + ".GetList";
    public const string InfoAgentDelete = Group_InfoAgent + ".Delete";

    //异常收集
    public const string Group_ErrorCollect = "ErrorCollectPermissions"; 
    public const string ErrorCollectUpdate = Group_ErrorCollect + ".Update";
    public const string ErrorCollectGet = Group_ErrorCollect + ".Get";
    public const string ErrorCollectGetList = Group_ErrorCollect + ".GetList";
    public const string ErrorCollectDelete = Group_ErrorCollect + ".Delete";
    public const string ErrorCollectDeleteSame = Group_ErrorCollect + ".DeleteSame";



    public const string Group_NameCollect = "NameCollectPermissions";
    public const string NameCollectCreateMany = Group_NameCollect + ".CreateMany";
    public const string NameCollectGetRandom = Group_NameCollect + ".GetRandom";
    public const string NameCollectCreate = Group_NameCollect + ".Create";
    public const string NameCollectDelete = Group_NameCollect + ".Delete";
    public const string NameCollectUpdate = Group_NameCollect + ".Update";
    public const string NameCollectGetList = Group_NameCollect + ".GetList";
    public const string NameCollectGet = Group_NameCollect + ".Get";





}
