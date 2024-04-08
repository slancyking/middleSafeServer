using Microsoft.Extensions.Logging;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using middleSafeServer.SK.InfoCollects.NameCollects;
using middleSafeServer.util;
using SixLabors.ImageSharp.Formats;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.BackgroundJobs;
using Volo.Abp.DependencyInjection;
using Volo.Abp.Emailing;
using Volo.Abp.Uow;

namespace middleSafeServer.BackgroundJobs.ImageCollectDown
{
    public class ImageCollectDownPublishJob : BackgroundJob<ImageCollectDownPublicArgs>, ISingletonDependency
    {
 
        private readonly IImageCollectRepository _imageCollectRepository;
        private readonly ImageCollectManager _imageCollectManager;
        private readonly IBackgroundJobManager _backgroundJobManager;
        private readonly INameCollectRepository _nameCollectRepository;

        public ImageCollectDownPublishJob( 
                        IImageCollectRepository imageCollectRepository,
                        ImageCollectManager imageCollectManager, IBackgroundJobManager backgroundJobManager, INameCollectRepository nameCollectRepository)
        {
            _imageCollectRepository = imageCollectRepository;
            _imageCollectManager = imageCollectManager;
            _backgroundJobManager = backgroundJobManager;
            _nameCollectRepository = nameCollectRepository;
        }

        [UnitOfWork]
        public async Task saveImageToData(bool suc, ImageCollectSavePublicArgs args)
        {
            try
            {
                var nameInfo = await _nameCollectRepository.FindAsync(i => i.Id.Equals(args.NameId) && i.InfoAgentId.Equals(args.InfoAgentId));

                nameInfo.RetrySaveHeadIconCount++;
                if (suc)
                {
                    var headImage = await _imageCollectRepository.FindImage(args.Image64Size, args.ImageMd5, args.ImageHash, args.ImageWidth, args.ImageHeight, args.ImageName, args.InfoAgentId);

                    if (headImage == null)
                    {
                        headImage = await _imageCollectManager.CreateAsync(args.InfoAgentId, args.ImageB64, args.ImageWidth, args.ImageHeight, args.Image64Size, args.ImageMd5, args.ImageHash, args.ImageName);
                        headImage = await _imageCollectRepository.InsertAsync(headImage);
                    }

                    if (headImage != null)
                    {
                        nameInfo.ImageCollectId = headImage.Id;
                        nameInfo.FinishSaveHeadIcon = true;
                    }
                }
                await _nameCollectRepository.UpdateAsync(nameInfo);
            }
            catch {
                Logger.LogError("修改NameCollect实体失败!");
            }
        }

        public override void Execute(ImageCollectDownPublicArgs args)
        {
            //var nameInfo = args.nameInfo; 

            if (args.HeadIconUrl == null) {
                return;
            }

            WebRequest request = WebRequest.Create(args.HeadIconUrl);
            WebResponse response = null; ;
            Stream reader = null;
            SixLabors.ImageSharp.Image tmpImage = null;

            ImageCollectSavePublicArgs imageCollectSavePublicArgs = new ImageCollectSavePublicArgs();
            bool suc = false;
            imageCollectSavePublicArgs.NameId = args.Id;
            imageCollectSavePublicArgs.InfoAgentId = args.InfoAgentId;
            try
            {

                response = request.GetResponse();
                reader = response.GetResponseStream();
                IImageFormat format;

                List<byte> bytes = new List<byte>();
                int temp = reader.ReadByte();
                while (temp != -1)
                {
                    bytes.Add((byte)temp);
                    temp = reader.ReadByte();
                }  
                byte[] imageByteArray = bytes.ToArray(); 
                tmpImage = SixLabors.ImageSharp.Image.Load(imageByteArray, out format);
                string b64Image = Convert.ToBase64String(imageByteArray);
                uint Image64Size = (uint)(tmpImage.Width * tmpImage.Height);
                string ImageMd5 = CommonCrypt.makeMd5(b64Image);
                uint ImageHash = CommonCrypt.stringToHashNumber(ImageMd5);

                suc = true;
                imageCollectSavePublicArgs.Image64Size = Image64Size;
                imageCollectSavePublicArgs.ImageMd5 = ImageMd5;
                imageCollectSavePublicArgs.ImageHash = ImageHash;
                imageCollectSavePublicArgs.ImageWidth = tmpImage.Width;
                imageCollectSavePublicArgs.ImageHeight = tmpImage.Height;
                imageCollectSavePublicArgs.ImageName = format.Name;
                imageCollectSavePublicArgs.ImageB64 = b64Image;
                 
            }
            catch (Exception e)
            {
                Logger.Log(Microsoft.Extensions.Logging.LogLevel.Error, "下载图片失败! ,错误代码:{0}", e.Message);
            }
            finally
            {
                if (reader != null)
                {
                    reader.Close();
                    reader.Dispose();
                }
                if (response != null)
                {
                    response.Close();
                    response.Dispose();
                }
                if (tmpImage != null)
                    tmpImage.Dispose();

                saveImageToData(suc,imageCollectSavePublicArgs).Wait();

            }
        }
    }
}
