
using AutoMapper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.SK.CardMsgs.Dto
{
    /// <summary>
    /// 对象映射,app加载之前会先加载
    /// </summary>
    public class CardMsgProfile : Profile
    {
        public CardMsgProfile() {
            CreateMap<CardMsg, CardMsgOutputDto>();
            //CreateMap<CardMsg, CardMsgOutputDto>().ForMember(x => x.CardPassword, map => map.MapFrom(m => m.Card.Password))
            //.ForMember(x => x.CardRemark, map => map.MapFrom(m => m.Card.Remark));
        }
    }
}
