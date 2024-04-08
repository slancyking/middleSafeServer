using System;
using System.Collections.Generic;
using System.Text;
using Volo.Abp.Application.Dtos;

namespace middleSafeServer.SK.ErrorCollects
{
    public class ErrorCollectDto : EntityDto<Guid>
    {
        public DateTime CreationTime { get; set; }
        public Guid BranchId { get; set; }
        public string BranchName { get; set; }
        public Guid CardId { get; set; }
        public string Ip { get; set; }
        public string ErrorTitle { get; set; }
        public string ErrorMessage { get; set; }
        public string BackStackTraceBack { get; set; }
    }
}
