using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Entities;
using Volo.Abp.Domain.Repositories;
using Volo.Abp.Domain.Repositories.EntityFrameworkCore;
using Volo.Abp.EntityFrameworkCore;

namespace middleSafeServer.EntityFrameworkCore.Repositories
{
    public abstract class middleSafeServerRepositoryBase<TEntity, TPrimaryKey> : EfCoreRepository<middleSafeServerDbContext, TEntity, TPrimaryKey>
        where TEntity : class, IEntity<TPrimaryKey>
    {
        protected middleSafeServerRepositoryBase(IDbContextProvider<middleSafeServerDbContext> dbContextProvider)
            : base(dbContextProvider)
        {
        }

        // Add your common methods for all repositories
    }

    /// <summary>
    /// Base class for custom repositories of the application.
    /// This is a shortcut of <see cref="middleSafeServerRepositoryBase{TEntity,TPrimaryKey}"/> for <see cref="int"/> primary key.
    /// </summary>
    /// <typeparam name="TEntity">Entity type</typeparam>
    public abstract class middleSafeServerRepositoryBase<TEntity> : middleSafeServerRepositoryBase<TEntity, Guid>, IRepository<TEntity>
        where TEntity : class, IEntity<Guid>
    {
        protected middleSafeServerRepositoryBase(IDbContextProvider<middleSafeServerDbContext> dbContextProvider)
            : base(dbContextProvider)
        {
        }

        // Do not add any method here, add to the class above (since this inherits it)!!!
    }
}
