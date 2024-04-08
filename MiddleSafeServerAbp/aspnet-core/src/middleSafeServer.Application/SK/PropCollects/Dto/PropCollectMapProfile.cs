using AutoMapper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.PropCollects.Dto
{
    public class PropCollectMapProfile : Profile
    {
        public PropCollectMapProfile() {
            CreateMap<PropCollect, QueryDetailOutput>();
            //CreateMap<PropCollect, QueryDetailOutput>().ForMember(x => x.ProjectName, map => map.MapFrom(m => m.Branch.LinkProject.Name)) //项目名映射
            //.ForMember(x => x.BranchName, map => map.MapFrom(m => m.Branch.Name)) //分支名映射
            //.ForMember(x => x.CardPassword, map => map.MapFrom(m => m == null ? "" : m.Card.Password)); //内部卡密映射 

        }
    }
}
