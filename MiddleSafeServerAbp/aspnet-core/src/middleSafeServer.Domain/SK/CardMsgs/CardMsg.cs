using JetBrains.Annotations;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;
using Volo.Abp.Domain.Entities.Auditing;

namespace middleSafeServer.SK.CardMsgs
{
    public class CardMsg : AuditedAggregateRoot<Guid>

    {  
        public Guid CardId { get; set; }
         
        public bool IsRead { get; set; }

        public string Info { get; set; }

        private CardMsg() {
            
        }


        internal CardMsg(
             Guid id,
             [NotNull] string info,
             [NotNull] Guid cardId,
             [NotNull] bool isRead
             )
             : base(id)
        { 
            CardId = id;
            Info = info;
            IsRead = isRead;
        }


    }
}
