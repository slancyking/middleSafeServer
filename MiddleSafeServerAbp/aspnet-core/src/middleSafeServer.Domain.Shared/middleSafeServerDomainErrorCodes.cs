namespace middleSafeServer;

public static class middleSafeServerDomainErrorCodes
{
    /* You can add your business exception error codes here, as constants */

    public const string ProjectAlreadyExists = "middleSafeServer:00001";
    public const string BranchAlreadyExists = "middleSafeServer:00002";
    public const string ProjectAlreadyDelete = "middleSafeServer:00003"; 
    public const string BranchAlreadyDelete = "middleSafeServer:00004";

    public const string cardDaysOutOfRange = "middleSafeServer:00005";

    public const string InfoAgentAlreadyExists = "middleSafeServer:00006";

    public const string InfoAgentAlreadyDelete = "middleSafeServer:00007";
    public const string NameCollectAlreadyExists = "middleSafeServer:00008";

    public const string NameCollectCountAlreadyExists = "middleSafeServer:00009";
}
