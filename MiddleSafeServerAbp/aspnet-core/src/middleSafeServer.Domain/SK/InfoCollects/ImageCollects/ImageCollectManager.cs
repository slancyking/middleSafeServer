using JetBrains.Annotations;
using middleSafeServer.SK.InfoAgents;
using middleSafeServer.SK.Projects;
using middleSafeServer.util;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp;
using Volo.Abp.Domain.Services;

namespace middleSafeServer.SK.InfoCollects.ImageCollects
{
    public class ImageCollectManager : DomainService
    {
        private readonly IImageCollectRepository _imageCollectRepository;
        private readonly IInfoAgentRepository _infoAgentRepository;

        public ImageCollectManager(IImageCollectRepository imageCollectRepository, IInfoAgentRepository infoAgentRepository) {
            _imageCollectRepository = imageCollectRepository;
            _infoAgentRepository = infoAgentRepository;
        }
         
        public async Task<ImageCollect> CreateAsync(
            [NotNull] Guid InfoAgentId,
            [NotNull] string ImageBase64,
            [NotNull] int ImageWidth,
            [NotNull] int ImageHeight,
            [NotNull] uint Image64Size ,
            [NotNull] string ImageMd5,
            [NotNull] uint ImageHash,
            [NotNull] string ImageType)
        {
             
            var infoAgent = await _infoAgentRepository.FindAsync(InfoAgentId);
            if (infoAgent == null)
            {
                throw new InfoAgentAlreadyDeleteException(infoAgent.ToString());
            }


            Check.NotNullOrWhiteSpace(InfoAgentId.ToString(), nameof(InfoAgentId));
            Check.NotNullOrWhiteSpace(ImageBase64, nameof(ImageBase64));
              
            return new ImageCollect(
                    GuidGenerator.Create(), InfoAgentId, ImageBase64, Image64Size, ImageMd5,
                    ImageHash,
                    ImageWidth,
                    ImageHeight,
                    ImageType
                ); 
        }
         
    }
}
