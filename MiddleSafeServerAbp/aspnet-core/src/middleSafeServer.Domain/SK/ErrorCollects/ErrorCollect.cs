using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.Auditing;
using Volo.Abp.Domain.Entities;

namespace middleSafeServer.SK.ErrorCollects
{
    public class ErrorCollect : Entity<Guid>, IHasCreationTime
    {

        public DateTime CreationTime { get; set; }
        public Guid BranchId { get; set; }
        public Guid CardId { get; set; } 
        public string Ip { get; set; }
        public string ErrorTitle { get; set; }
        public string ErrorMessage { get; set; }
        public string BackStackTraceBack { get; set; }

        public ErrorCollect(Guid id,Guid branchId,Guid cardId, string errorTitle, string errorMessage, string backStackTraceBack,string ip) : base(id)
        {
            this.CreationTime = DateTime.Now;
            this.BranchId = branchId;
            this.CardId = cardId;
            this.ErrorTitle = errorTitle;
            this.ErrorMessage = errorMessage;
            this.BackStackTraceBack = backStackTraceBack; 
            this.Ip = ip;
        }


    }
}
