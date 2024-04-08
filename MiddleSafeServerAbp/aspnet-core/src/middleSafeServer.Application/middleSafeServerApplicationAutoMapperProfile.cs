using AutoMapper;
using middleSafeServer.SK.Branchs;
using middleSafeServer.SK.Cards;
using middleSafeServer.SK.ErrorCollects;
using middleSafeServer.SK.InfoAgents;
using middleSafeServer.SK.InfoCollects.ImageCollects;
using middleSafeServer.SK.InfoCollects.NameCollects;
using middleSafeServer.SK.MiddleReports;
using middleSafeServer.SK.Projects;
using middleSafeServer.SK.PropCollects;
using middleSafeServer.SK.PropCollects.Dto;
using middleSafeServer.SK.WebSettings;
using System;

namespace middleSafeServer;

public class middleSafeServerApplicationAutoMapperProfile : Profile
{
    public middleSafeServerApplicationAutoMapperProfile()
    {
        /* You can configure your AutoMapper mapping configuration here.
         * Alternatively, you can split your mapping configurations
         * into multiple profile classes for a better organization. */


        CreateMap<Project, ProjectDto>();
        CreateMap<Branch, BranchDto>();

        CreateMap<Card, CardDto>().ForMember(x => x.IsLogin, map => map.MapFrom(m => !string.IsNullOrWhiteSpace(m.LoginToken) && m.LoginOvertime > DateTime.Now));

        CreateMap<MiddleReportInputDto, MiddleReport>();
        CreateMap<MiddleReport, MiddleNomalQueryOutputDto>().ForMember(x => x.Info, map => map.Ignore());



        CreateMap<WebSetting, GetWebSettingOutputDto>();

        CreateMap<UpdateWebSettingInputDto, WebSetting>(); 
        CreateMap<InfoAgent, InfoAgentDto>();

        //CreateMap<Tuple<NameCollect, ImageCollect, InfoAgent>, NameCollectDto>().ForMember(x => x.InfoAgent, option => option.MapFrom(input => input.Item3.Name))
        //    .ForMember(x=>x.FinishSaveHeadIcon , option => option.MapFrom(input=>input.Item1.FinishSaveHeadIcon))
        //    .ForMember(x=>x.HeadIconUrl, option => option.MapFrom(input => input.Item1.HeadIconUrl))
        //    .ForMember(x => x.Id, option => option.MapFrom(input => input.Item1.Id))
        //    .ForMember(x => x.ImageCollect, option => option.MapFrom(input => input.Item2 == null ? "" : input.Item2.ImageBase64))
        //    .ForMember(x => x.Name, option => option.MapFrom(input => input.Item1.Name))
        //    .ForMember(x => x.RetrySaveHeadIconCount, option => option.MapFrom(input => input.Item1.RetrySaveHeadIconCount))
        //    .ForMember(x => x.Sex, option => option.MapFrom(input => input.Item1.Sex));
        CreateMap<NameCollect, NameCollectDto>();

        CreateMap<ErrorCollect, ErrorCollectDto>();

        CreateMap<CreatePropCollectionInput, PropCollect>();

    }
}
