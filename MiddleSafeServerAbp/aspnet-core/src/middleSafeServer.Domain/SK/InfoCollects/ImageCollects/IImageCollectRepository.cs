using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Domain.Repositories;

namespace middleSafeServer.SK.InfoCollects.ImageCollects
{
    public interface IImageCollectRepository : IRepository<ImageCollect, Guid>
    {   

        Task<ImageCollect> FindImage(uint Image64Size, 
            string ImageMd5,
            uint ImageHash,
            int ImageWidth,
            int ImageHeight,
            string ImageType,
            Guid InfoAgentId
            );


        Task<EfPageList<ImageCollect>> GetListAsync(
            int skipCount,
            int maxResultCount, 
            string sorting,
            Guid infoAgentId
        );
         



    }
}
