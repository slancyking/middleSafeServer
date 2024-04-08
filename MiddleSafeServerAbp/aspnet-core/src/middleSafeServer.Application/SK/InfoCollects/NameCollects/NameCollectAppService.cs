using System;
using System.Collections.Generic;
using System.Linq;
using System.Linq.Dynamic.Core;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Application.Dtos;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.Formats;
using middleSafeServer.util;
using middleSafeServer.SK.InfoAgents;
using AutoMapper;
using middleSafeServer.SK.InfoCollects.NameCollectCounts;
using Volo.Abp;
using middleSafeServer.SK.CommonDto;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.Branchs;
using Microsoft.AspNetCore.Authorization;
using middleSafeServer.Permissions;
using Volo.Abp.DistributedLocking;

namespace middleSafeServer.SK.InfoCollects.NameCollects
{
    [Authorize]
    public class NameCollectAppService : middleSafeServerAppService, INameCollectAppService
    {

        private readonly INameCollectRepository _nameCollectsRepository;
        private readonly NameCollectManager _nameCollectManager;

        private readonly IImageCollectRepository _imageCollectRepository;
        private readonly ImageCollectManager _imageCollectManager;

        private readonly IInfoAgentRepository _infoAgentRepository;

        private readonly NameCollectCountManager _nameCollectCountManager;
        private readonly INameCollectCountRepository _nameCollectCountRepository;


        private readonly ICardRepository _cardRepository;
        private readonly CardManager _cardManager;
        private readonly IBranchRepository _branchRepository;

        private readonly IAbpDistributedLock _abpDistributedLock;

        private const string imageFlag = "base64,";

        public  NameCollectAppService(INameCollectRepository nameCollectsRepository,
                NameCollectManager nameCollectManager,
                IImageCollectRepository imageCollectRepository,
                ImageCollectManager imageCollectManager,
                IInfoAgentRepository infoAgentRepository,
                NameCollectCountManager nameCollectCountManager,
                ICardRepository cardRepository,
                CardManager cardManager,
                IBranchRepository branchRepository,
                INameCollectCountRepository nameCollectCountRepository,
                IAbpDistributedLock abpDistributedLock
                )
        {
            _nameCollectsRepository = nameCollectsRepository;
            _nameCollectManager = nameCollectManager;
            _imageCollectRepository = imageCollectRepository;
            _imageCollectManager = imageCollectManager;
            _infoAgentRepository = infoAgentRepository;
            _nameCollectCountManager = nameCollectCountManager;
            _nameCollectCountRepository = nameCollectCountRepository;
            _cardRepository = cardRepository;
            _cardManager = cardManager;
            _branchRepository = branchRepository;
            _abpDistributedLock = abpDistributedLock;
        }

        [Authorize(middleSafeServerPermissions.NameCollectUpdate)]
        public async Task<NameCollectDto> CreateAsync(CreateNameCollectDto input)
        {
            Guid? ImageCollectId = null;
            var NeedSaveImg = false;
            ImageCollect headImage = null;
            if (!string.IsNullOrWhiteSpace(input.ImageCollect)) {
                byte[] imgBytes = Convert.FromBase64String(input.ImageCollect);
                IImageFormat format;
                using var tmpImage = Image.Load(imgBytes,out format);

                uint Image64Size = (uint)input.ImageCollect.Length;
                string ImageMd5 = CommonCrypt.makeMd5(input.ImageCollect);
                uint ImageHash = CommonCrypt.stringToHashNumber(ImageMd5);

                headImage = await _imageCollectRepository.FindImage(Image64Size, ImageMd5, ImageHash, tmpImage.Width, tmpImage.Height, format.FileExtensions.ToString(), input.InfoAgentId);
                
                if (headImage == null) {
                    NeedSaveImg = true;
                    headImage = await _imageCollectManager.CreateAsync(input.InfoAgentId, input.ImageCollect, tmpImage.Width, tmpImage.Height, Image64Size, ImageMd5, ImageHash, format.FileExtensions.ToString()); 
                }
                ImageCollectId = headImage.Id; 
            }
             
            var nameCollect = await _nameCollectManager.CreateAsync(
                                   input.InfoAgentId,
                                   input.Name,
                                   input.Sex,
                                   ImageCollectId,
                                   input.HeadIconUrl,
                                   input.ExtendJson
                               );


            if (nameCollect != null) {
                uint tmpIndex = await _nameCollectCountManager.GetNameCollectIndex(input.InfoAgentId);

                if (tmpIndex == 0) {
                    throw new UserFriendlyException(
                        "数据索引定义异常!"
                    );
                } 

                nameCollect.CollectIndex = tmpIndex;

                if (NeedSaveImg) //如果需要保存头像,放在此处,避免在创建 nameCollect实体的时候遇到重名异常
                    await _imageCollectRepository.InsertAsync(headImage);
                var result = await _nameCollectsRepository.InsertAsync(nameCollect);
                return ObjectMapper.Map<NameCollect, NameCollectDto>(result);
            }
            
            return ObjectMapper.Map<NameCollect, NameCollectDto>(null);
        }
        [AllowAnonymous]
        public async Task<CardClientOuputDto<CreateManyNameCollectOutputDto>> CreateManyAsync(CardClientInputDto<CreateManyNameCollectDto>  input)
        {

            if (string.IsNullOrWhiteSpace(input.Password)) { return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Info = "卡密异常", Result = -100, }, null); }

            if (string.IsNullOrWhiteSpace(input.Password))
                return null;
            SK.Cards.Card _card = await _cardRepository.FindAsync(c => c.Password == input.Password.Trim());
            if (_card == null)
                return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Info = "卡密异常", Result = -100, }, null);

            var param = input.getParam(_card.RsaPrivateKey);
            if (param == null)
                return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Result = -98, Info = "解密异常" }, _card.RsaPrivateKey);

            if (param.bCheckTimeout())
                return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Result = -101, Info = "请求超时" }, _card.RsaPrivateKey);

            CardLoginStatus loginStatus = _cardManager.CheckCardLogin(_card, param.Token);
            if (loginStatus != CardLoginStatus.loginSuccess)
                return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Info = "登陆状态异常", Result = -90 }, _card.RsaPrivateKey);

            var branch = await _branchRepository.FindAsync(i => i.Id.Equals(_card.BranchId));
            if (_card == null)
                return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Info = "分支异常", Result = -95 }, _card.RsaPrivateKey);


            List<ImageCollect> imageList = new List<ImageCollect>();
            List<NameCollect> nameList = new List<NameCollect>();

 
            foreach (var item in param.NameCollects)
            { 
                ImageCollect headImage = null;
                bool needSaveImg = false;
                if (!string.IsNullOrWhiteSpace(item.ImageCollect))
                {
                    try
                    {
                        byte[] imgBytes = Convert.FromBase64String(item.ImageCollect);
                        IImageFormat format;
                        using var tmpImage = Image.Load(imgBytes, out format);

                        uint Image64Size = (uint)(tmpImage.Width * tmpImage.Height);
                        string ImageMd5 = CommonCrypt.makeMd5(item.ImageCollect);
                        uint ImageHash = CommonCrypt.stringToHashNumber(ImageMd5);

                        headImage = await _imageCollectRepository.FindImage(Image64Size, ImageMd5, ImageHash, tmpImage.Width, tmpImage.Height, format.Name, item.InfoAgentId);

                        if (headImage == null)
                        {
                            headImage = await _imageCollectManager.CreateAsync(item.InfoAgentId, item.ImageCollect, tmpImage.Width, tmpImage.Height, Image64Size, ImageMd5, ImageHash, format.FileExtensions.ToString());
                            needSaveImg = true;
                        }
                    }
                    catch {
                        return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Info = "图片格式异常!", Result = -92 }, _card.RsaPrivateKey);
                    }

                    
                }

                var nameCollect = await _nameCollectManager.CreateAsync(
                                       item.InfoAgentId,
                                       item.Name,
                                       item.Sex,
                                       headImage == null ? null : headImage.Id,
                                       item.HeadIconUrl,
                                       item.ExtendJson
                                   );

                if (nameCollect != null) {
                    if (needSaveImg) {
                        imageList.Add(headImage);
                        nameCollect.FinishSaveHeadIcon = true;
                    }
                    nameList.Add(nameCollect);
                } 
                //var result = await _nameCollectsRepository.InsertAsync(nameCollect);
            }


            if (nameList.Count() > 0) {
                uint tmpIndex = await _nameCollectCountManager.GetNameCollectIndex(nameList[0].InfoAgentId, nameList.Count()); 
                if (tmpIndex == 0)
                {
                    return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Info = "数据索引异常", Result = -93 }, _card.RsaPrivateKey);
                }

                for (int i = 0; i < nameList.Count(); i++)
                    nameList[i].CollectIndex = (uint)(tmpIndex + i);

                if (imageList.Count() > 0)
                    await _imageCollectRepository.InsertManyAsync(imageList);

                await _nameCollectsRepository.InsertManyAsync(nameList);
            }
             
            return new CardClientOuputDto<CreateManyNameCollectOutputDto>(new CreateManyNameCollectOutputDto() { Info = "操作成功", Result = 0 }, _card.RsaPrivateKey);



        }
        [AllowAnonymous]
        public async Task<CardClientOuputDto<GetRandomNameCollectOutputDto>> RandomNameCollect(CardClientInputDto<GetRandomNameCollectInputDto> input) {
            if (string.IsNullOrWhiteSpace(input.Password)) { return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto() { Info = "卡密异常", Result = -100, }, null, true); }

            if (string.IsNullOrWhiteSpace(input.Password))
                return null;
            SK.Cards.Card _card = await _cardRepository.FindAsync(c => c.Password == input.Password.Trim());
            if (_card == null)
                return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto() { Info = "卡密异常", Result = -100, }, null, true);

            var param = input.getParam(_card.RsaPrivateKey);
            if (param == null)
                return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto() { Result = -98, Info = "解密异常" }, null, true);

            if (param.bCheckTimeout())
                return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto() { Result = -101, Info = "请求超时" }, null, true);

            CardLoginStatus loginStatus = _cardManager.CheckCardLogin(_card, param.Token);
            if (loginStatus != CardLoginStatus.loginSuccess)
                return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto() { Info = "登陆状态异常", Result = -90 }, null, true);

            //var branch = await _branchRepository.FindAsync(i => i.Id.Equals(_card.BranchId));
            //if (_card == null)
            //    return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto() { Info = "分支异常", Result = -95 }, _card.RsaPrivateKey);


            var nameCount = await _nameCollectCountRepository.FindAsync(n => n.InfoAgentId.Equals(param.InfoAgentId));

            if(nameCount == null)
                return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto() { Info = "无效的信息渠道", Result = -88 }, null, true);
            var r = new Random(Guid.NewGuid().GetHashCode());
            uint rndIdx = (uint)r.Next(1, (int)nameCount.Count);
            var result = await _nameCollectsRepository.FindAsync(n=>n.CollectIndex.Equals(rndIdx) && n.InfoAgentId.Equals(param.InfoAgentId));
            if(result == null)
                return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto() { Info = "随机数据无效", Result = -87 }, null, true);

            ImageCollect imageCollect = null;
            if (result.ImageCollectId != null)
                imageCollect = await _imageCollectRepository.GetAsync(i => i.Id == (Guid)result.ImageCollectId && i.InfoAgentId == param.InfoAgentId);

            var infoAgent = await _infoAgentRepository.GetAsync(result.InfoAgentId);

            NameCollectDto nameCollectDto = ObjectMapper.Map<NameCollect, NameCollectDto>(result);
            nameCollectDto.InfoAgent = infoAgent.Name;
            nameCollectDto.ImageCollect = imageCollect.ImageBase64;

            return new CardClientOuputDto<GetRandomNameCollectOutputDto>(new GetRandomNameCollectOutputDto(){ Info = "操作成功", Result = 0 , Data = nameCollectDto },null,true);

        }

        [Authorize(middleSafeServerPermissions.NameCollectDelete)]
        public async Task DeleteAsync(Guid id)
        {
            await _nameCollectsRepository.DeleteAsync(id);
        }
        [Authorize(middleSafeServerPermissions.NameCollectGet)]
        public async Task<NameCollectDto> GetAsync(Guid id)
        { 
            var nameCollect = await _nameCollectsRepository.GetAsync(id);

            var infoAgent = await _infoAgentRepository.GetAsync(nameCollect.InfoAgentId);
            ImageCollect imageCollect = null;
            if (nameCollect.ImageCollectId != null) {
                imageCollect = await _imageCollectRepository.GetAsync((Guid)nameCollect.ImageCollectId);
            }

            NameCollectDto nameCollectDto = ObjectMapper.Map<NameCollect, NameCollectDto>(nameCollect);
            nameCollectDto.InfoAgent = infoAgent.Name;
            nameCollectDto.ImageCollect = imageCollect.ImageBase64;

            return nameCollectDto;
        }
        [Authorize(middleSafeServerPermissions.NameCollectGetList)]
        public async Task<PagedResultDto<NameCollectDto>> GetListAsync(GetNameCollectListDto input)
        {
            if (input.Sorting == null) {
                input.Sorting = nameof(NameCollect.CreationTime);
            }


            var queryable = await _nameCollectsRepository.GetQueryableAsync();
            queryable = queryable.WhereIf(!string.IsNullOrWhiteSpace(input.Filter), q => q.Name.Contains(input.Filter));
            queryable = queryable.WhereIf(input.InfoAgentId != null, q => q.InfoAgentId.Equals(input.InfoAgentId));
           // queryable = queryable.OrderBy(input.Sorting);
            var s1 = await _infoAgentRepository.GetQueryableAsync();
            var s2 = await _imageCollectRepository.GetQueryableAsync();
            var query = from nameCollect in queryable
                        join infoAgent in s1 on nameCollect.InfoAgentId equals infoAgent.Id
                        join imageCollect in s2 on nameCollect.ImageCollectId equals imageCollect.Id
                        select new { nameCollect, infoAgent, imageCollect };
            query = query
                .OrderBy(NormalizeSorting(input.Sorting)) //这 要引用 using System.Linq.Dynamic.Core;
                .Skip(input.SkipCount)
                .Take(input.MaxResultCount);
            try
            {
                var queryResult = await AsyncExecuter.ToListAsync(query);

                var nameCollectDtos = queryResult.Select(x =>
                {
                    var nameCollectDto = ObjectMapper.Map<NameCollect, NameCollectDto>(x.nameCollect);
                    nameCollectDto.InfoAgent = x.infoAgent.Name;
                    nameCollectDto.ImageCollect = x.imageCollect.ImageBase64;
                    return nameCollectDto;
                }).ToList();
                var totalCount = queryable.Count();

                return new PagedResultDto<NameCollectDto>(
                    totalCount,
                    nameCollectDtos
                ); 
            }
            catch (Exception ex)
            {
                return null;
            }
           

        }
        [Authorize(middleSafeServerPermissions.NameCollectUpdate)]
        public async Task UpdateAsync(Guid id, UpdateNameCollectDto input)
        {
            var nameCollect = await _nameCollectsRepository.GetAsync(id);
            if (nameCollect == null) return;

            if (input.InfoAgentId != nameCollect.InfoAgentId)
                await _nameCollectManager.ChangeInfoAgentAsync(nameCollect, input.InfoAgentId);

            if (input.Name != nameCollect.Name)
                await _nameCollectManager.ChangeNameAsync(nameCollect,input.Name);

            if (input.Sex != nameCollect.Sex) nameCollect.Sex = input.Sex;
            if (input.ExtendJson != nameCollect.ExtendJson) nameCollect.ExtendJson = input.ExtendJson;

            if (!string.IsNullOrWhiteSpace(input.ImageCollect)) {  //需要保存头像
                ImageCollect headImage = null;
                if (!string.IsNullOrWhiteSpace(input.ImageCollect))
                {
                    byte[] imgBytes = Convert.FromBase64String(input.ImageCollect);
                    IImageFormat format;
                    using var tmpImage = Image.Load(imgBytes, out format);

                    uint Image64Size = (uint)input.ImageCollect.Length;
                    string ImageMd5 = CommonCrypt.makeMd5(input.ImageCollect);
                    uint ImageHash = CommonCrypt.stringToHashNumber(ImageMd5);

                    headImage = await _imageCollectRepository.FindImage(Image64Size, ImageMd5, ImageHash, tmpImage.Width, tmpImage.Height, format.FileExtensions.ToString(), input.InfoAgentId);

                    if (headImage == null)
                    { 
                        headImage = await _imageCollectManager.CreateAsync(input.InfoAgentId, input.ImageCollect, tmpImage.Width, tmpImage.Height, Image64Size, ImageMd5, ImageHash, format.FileExtensions.ToString());
                        await _imageCollectRepository.InsertAsync(headImage);
                    }
                    nameCollect.ImageCollectId = headImage.Id;
                } 
            }
            await _nameCollectsRepository.UpdateAsync(nameCollect);

        }

        private static string NormalizeSorting(string sorting)
        {
            if (sorting.IsNullOrEmpty())
            {
                return $"nameCollect.{nameof(NameCollect.Name)}";
            }

            if (sorting.Contains("infoAgentName", StringComparison.OrdinalIgnoreCase))
            {
                return sorting.Replace(
                    "infoAgentName",
                    "infoAgent.Name",
                    StringComparison.OrdinalIgnoreCase
                );
            }

            return $"nameCollect.{sorting}";
        }

    }
}
