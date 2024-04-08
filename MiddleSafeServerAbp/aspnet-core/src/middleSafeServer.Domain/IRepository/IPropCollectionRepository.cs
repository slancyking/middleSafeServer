
using middleSafeServer.SK.PropCollects;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.IRepository
{
    public interface IPropCollectionRepository : IRepository<SK.PropCollects.PropCollect, Guid>
    {
        /// <summary>
        /// 通过各种过滤条件,返回一个PropCollect查询语句
        /// </summary>
        /// <param name="pra"></param>
        /// <returns></returns>
        Task<IQueryable<PropCollect>> GetPropCollectList(
            QueryPropCollectInputCommon pra
            );




    }
}
