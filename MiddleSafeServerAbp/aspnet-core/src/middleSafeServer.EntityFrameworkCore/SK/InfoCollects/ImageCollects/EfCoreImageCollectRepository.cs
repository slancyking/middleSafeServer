using Microsoft.EntityFrameworkCore;
using middleSafeServer.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories.EntityFrameworkCore;
using Volo.Abp.EntityFrameworkCore;
using System.Linq.Dynamic.Core;


namespace middleSafeServer.SK.InfoCollects.ImageCollects
{
    public class EfCoreImageCollectRepository : EfCoreRepository<middleSafeServerDbContext, ImageCollect, Guid>, IImageCollectRepository
    {
        public EfCoreImageCollectRepository(IDbContextProvider<middleSafeServerDbContext> dbContextProvider) : base(dbContextProvider)
        {
        }

        public async Task<ImageCollect> FindImage(uint Image64Size, string ImageMd5, uint ImageHash, int ImageWidth, int ImageHeight, string ImageType, Guid InfoAgentId)
        {
            var dbSet = await GetDbSetAsync();
            return await dbSet.FirstOrDefaultAsync(imageCollect => imageCollect.InfoAgentId == InfoAgentId && imageCollect.ImageHash == ImageHash 
            && imageCollect.ImageHeight == ImageHeight 
            && imageCollect.ImageWidth == ImageWidth  
            && imageCollect.Image64Size == Image64Size
            && imageCollect.ImageType == ImageType
            && imageCollect.ImageMd5 == ImageMd5  

            );
        }

        public async Task<EfPageList<ImageCollect>> GetListAsync(int skipCount, int maxResultCount, string sorting, Guid infoAgentId)
        { 
            EfPageList<ImageCollect> result = new();
            if (string.IsNullOrWhiteSpace(sorting)) sorting = "CreationTime";
            var dbSet = await GetDbSetAsync();
            var query = dbSet.Where( i => i.InfoAgentId.Equals(infoAgentId));

            result.Count = await query.CountAsync();
            result.Result = await query.OrderBy(sorting)
                .Skip(skipCount)
                .Take(maxResultCount)
                .ToListAsync();


            return result;

        }
    }
}
