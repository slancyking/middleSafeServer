using Microsoft.EntityFrameworkCore;
using middleSafeServer.SK;
using middleSafeServer.SK.Branchs;
using middleSafeServer.SK.CardMsgs;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.InfoAgents;
using middleSafeServer.SK.InfoCollects.NameCollects;
using middleSafeServer.SK.InputForms;
using middleSafeServer.SK.MiddleReports;
using middleSafeServer.SK.Projects;
using middleSafeServer.SK.PropCollects;
using middleSafeServer.SK.WebSettings;
using Volo.Abp.AuditLogging.EntityFrameworkCore;
using Volo.Abp.BackgroundJobs.EntityFrameworkCore;
using Volo.Abp.Data;
using Volo.Abp.DependencyInjection;
using Volo.Abp.EntityFrameworkCore;
using Volo.Abp.EntityFrameworkCore.Modeling;
using Volo.Abp.FeatureManagement.EntityFrameworkCore;
using Volo.Abp.Identity;
using Volo.Abp.Identity.EntityFrameworkCore;
using Volo.Abp.IdentityServer.EntityFrameworkCore;
using Volo.Abp.PermissionManagement.EntityFrameworkCore;
using Volo.Abp.SettingManagement.EntityFrameworkCore;
using Volo.Abp.TenantManagement;
using Volo.Abp.TenantManagement.EntityFrameworkCore;

using ShardingCore.Core.VirtualRoutes.TableRoutes.RouteTails.Abstractions;
using ShardingCore.Sharding.Abstractions;
using ShardingCore.Sharding.ShardingDbContextExecutors;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using middleSafeServer.SK.NetworkAddressPool.IpLogs;
using middleSafeServer.SK.InfoCollects.NameCollectCounts;
using middleSafeServer.SK.ErrorCollects;

namespace middleSafeServer.EntityFrameworkCore;

[ReplaceDbContext(typeof(IIdentityDbContext))]
[ReplaceDbContext(typeof(ITenantManagementDbContext))]
[ConnectionStringName("Default")]
public class middleSafeServerDbContext :
    AbstractShardingAbpDbContext<middleSafeServerDbContext>,
    IIdentityDbContext,
    ITenantManagementDbContext,
    IShardingTableDbContext
{
    /* Add DbSet properties for your Aggregate Roots / Entities here. */

    #region Entities from the modules

    /* Notice: We only implemented IIdentityDbContext and ITenantManagementDbContext
     * and replaced them for this DbContext. This allows you to perform JOIN
     * queries for the entities of these modules over the repositories easily. You
     * typically don't need that for other modules. But, if you need, you can
     * implement the DbContext interface of the needed module and use ReplaceDbContext
     * attribute just like IIdentityDbContext and ITenantManagementDbContext.
     *
     * More info: Replacing a DbContext of a module ensures that the related module
     * uses this DbContext on runtime. Otherwise, it will use its own DbContext class.
     */

    //Identity
    public DbSet<IdentityUser> Users { get; set; }
    public DbSet<IdentityRole> Roles { get; set; }
    public DbSet<IdentityClaimType> ClaimTypes { get; set; }
    public DbSet<OrganizationUnit> OrganizationUnits { get; set; }
    public DbSet<IdentitySecurityLog> SecurityLogs { get; set; }
    public DbSet<IdentityLinkUser> LinkUsers { get; set; }

    // Tenant Management
    public DbSet<Tenant> Tenants { get; set; }
    public DbSet<TenantConnectionString> TenantConnectionStrings { get; set; }

    #endregion


    public DbSet<PropCollect> PropCollects { get; set; }
    public DbSet<InputForm> InputForms { get; set; }
    public DbSet<Card> Cards { get; set; } 
    public DbSet<CardMsg> CardMsgs { get; set; }
    public DbSet<Project> Projects { get; set; }
    public DbSet<Branch> Branchs { get; set; }
    public DbSet<MiddleReport> MiddleReports { get; set; }
    public DbSet<WebSetting> WebSettings { get; set; }

    public DbSet<InfoAgent> InfoAgents { get; set; }
    public DbSet<NameCollect> NameCollects { get; set; }
    public DbSet<NameCollectCount> NameCollectCounts { get; set; }
    
    public DbSet<ImageCollect> ImageCollects { get; set; }
    public DbSet<IpLog> IpLogs { get; set; }
    public DbSet<ErrorCollect> ErrorCollects { get; set; }

    public middleSafeServerDbContext(DbContextOptions<middleSafeServerDbContext> options)
        : base(options)
    {

    }

    protected override void OnModelCreating(ModelBuilder builder)
    {
        base.OnModelCreating(builder);

        /* Include modules to your migration db context */

        builder.ConfigurePermissionManagement();
        builder.ConfigureSettingManagement();
        builder.ConfigureBackgroundJobs();
        builder.ConfigureAuditLogging();
        builder.ConfigureIdentity();
        builder.ConfigureIdentityServer();
        builder.ConfigureFeatureManagement();
        builder.ConfigureTenantManagement();

        /* Configure your own tables/entities inside here */

        builder.Entity<PropCollect>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "PropCollects", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
        });
        builder.Entity<InputForm>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "InputForms", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
        });
        builder.Entity<Card>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "Cards", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
        });
         
        builder.Entity<CardMsg>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "CardMsgs", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
        });
        builder.Entity<Project>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "Projects", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
            b.Property(x => x.Name)
                .IsRequired()
                .HasMaxLength(SKConsts.MaxNameLength);
            b.HasIndex(x => x.Name);

        });
        builder.Entity<Branch>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "Branchs", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
            b.Property(x => x.Name)
                .IsRequired()
                .HasMaxLength(SKConsts.MaxNameLength);
            b.HasOne<Project>().WithMany().HasForeignKey(x => x.ProjectId).IsRequired();
        });
        builder.Entity<MiddleReport>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "MiddleReports", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
            b.HasOne<Card>().WithMany().HasForeignKey(x => x.CardId).IsRequired();
            
        });
        builder.Entity<WebSetting>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "WebSettings", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
        });


        builder.Entity<InfoAgent>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "InfoAgents", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
        });
        builder.Entity<NameCollect>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "NameCollects", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props  
        });
        builder.Entity<NameCollectCount>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "NameCollectCounts", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
            b.HasOne<InfoAgent>().WithMany().HasForeignKey(x => x.InfoAgentId).IsRequired();
        });

        
        builder.Entity<ImageCollect>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "ImageCollects", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props  
        });
        builder.Entity<IpLog>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "IpLogs", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
            b.HasOne<Card>().WithMany().HasForeignKey(x=>x.CardId).IsRequired();
            b.HasOne<Project>().WithMany().HasForeignKey(x => x.ProjectId).IsRequired(); 
        });
        builder.Entity<ErrorCollect>(b =>
        {
            b.ToTable(middleSafeServerConsts.DbTablePrefix + "ErrorCollects", middleSafeServerConsts.DbSchema);
            b.ConfigureByConvention(); //auto configure for the base class props 
            b.HasOne<Card>().WithMany().HasForeignKey(x => x.CardId).IsRequired();
            b.HasOne<Branch>().WithMany().HasForeignKey(x => x.BranchId).IsRequired();
        });


    }
    public IRouteTail RouteTail { get; set; }
}
