using middleSafeServer.IRepository;
using middleSafeServer.SK.PropCollects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.EntityFrameworkCore;

namespace middleSafeServer.EntityFrameworkCore.Repositories
{
    public class PropCollectionRepository : middleSafeServerRepositoryBase<PropCollect>, IPropCollectionRepository
    {
        public PropCollectionRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

        public async Task<IQueryable<PropCollect>> GetPropCollectList(QueryPropCollectInputCommon pra)
        {
            var Query = await GetQueryableAsync();


            //查询起始时间
            if (pra.QueryStartTime > DateTime.MinValue) { Query = Query.Where(p => p.CreationTime >= pra.QueryStartTime); }
            //查询结束时间
            if (pra.QueryEndTime > DateTime.MinValue) { Query = Query.Where(p => p.CreationTime <= pra.QueryEndTime); }

            //指定物品名处理
            if (pra.PropContain != null && pra.PropContain.Length > 0)
            {
                Query = Query.Where(p => p.PropName.IsIn(pra.PropContain));
            }

            //物品名过滤处理
            if (pra.PropFilter != null && pra.PropFilter.Length > 0)
            {
                Query = Query.Where(p => !p.PropName.IsIn(pra.PropFilter));
            }

            ////指定卡号处理
            //if (pra.CardIdContains != null && pra.CardIdContains.Length > 0)
            //{
            //    Query = Query.Where(p => p.Card.Password.IsIn(pra.CardIdContains));
            //}

            ////卡号过滤处理
            //if (pra.CardIdFilter != null && pra.CardIdFilter.Length > 0)
            //{
            //    Query = Query.Where(p => !p.Card.Password.IsIn(pra.CardIdFilter));
            //}

             

            ////分支id包含
            //if (pra.BranchIdContain != null && pra.BranchIdContain.Length > 0)
            //{
            //    Query = Query.Where(p => p.BranchId.IsIn(pra.BranchIdContain));
            //}

            ////分支id过滤
            //if (pra.BranchIdFilter != null && pra.BranchIdFilter.Length > 0)
            //{
            //    Query = Query.Where(p => !p.BranchId.IsIn(pra.BranchIdFilter));
            //}


            ////项目id包含
            //if (pra.ProjectIdContain != null && pra.ProjectIdContain.Length > 0)
            //{
            //    Query = Query.Where(p => p.Branch.ProjectId.IsIn(pra.ProjectIdContain));
            //}

            ////项目id过滤
            //if (pra.ProjectIdFilter != null && pra.ProjectIdFilter.Length > 0)
            //{
            //    Query = Query.Where(p => !p.Branch.ProjectId.IsIn(pra.ProjectIdFilter));
            //}

            return Query;
        }
    }
}
