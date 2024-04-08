using JetBrains.Annotations;
using middleSafeServer.SK.Projects;
using Nito.AsyncEx;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Volo.Abp.DistributedLocking;
using Volo.Abp.Domain.Repositories;
using Volo.Abp.Domain.Services;

namespace middleSafeServer.SK.NetworkAddressPool.IpLogs
{
    public class IpLogManager : DomainService
    {
        private readonly IIpLogRepository _ipLogRepository;
        private readonly IAbpDistributedLock _abpDistributedLock;
        private readonly IProjectRepository _projectRepository;
        public IpLogManager(IIpLogRepository ipLogRepository, IAbpDistributedLock abpDistributedLock, IProjectRepository projectRepository)
        {
            _ipLogRepository = ipLogRepository; 
            _abpDistributedLock = abpDistributedLock;
            _projectRepository = projectRepository;
        }

        public async Task<Tuple<IpLog,int,string>> TryUseIpAsync(
            [NotNull] string IpAddress,
            [NotNull] Guid ProjectId,
            [NotNull] Guid CardId,
            [NotNull] string LogMark,
            string Nation,
            string Province,
            string City,
            string District
            )
        {

            var project = await _projectRepository.FirstOrDefaultAsync(p => p.Id.Equals(ProjectId));
             
            int ipMaxUser = project == null ? 2 : project.IpMaxUserCount; //每个ip在同一个项目中限制多少个客户端使用, 后面在项目扩展设置里面加入
            IpLog logResult = null;
            await using (var handle = await _abpDistributedLock.TryAcquireAsync("lockForQueryIpLog:" + IpAddress, new TimeSpan(0, 0, 5))) { //根据ip地址做互斥,最多等待5秒
                if (handle != null)
                {
                    DateTime expiredTime = DateTime.Now;
                    var tmpIpLog = await _ipLogRepository.GetListAsync(i => i.IpAddress.Equals(IpAddress) && i.ProjectId.Equals(ProjectId));
                    int usingCount = tmpIpLog.Where(i => !i.bExpired()).Count(); //在使用的数目

                    if (tmpIpLog != null && usingCount > ipMaxUser)
                        return Tuple.Create(logResult, 10, "ip同时使用次数超过限制");

                    if (tmpIpLog != null)
                    {
                        foreach (var item in tmpIpLog)
                        {
                            if (item.CardId.Equals(CardId) && item.LogMark.Equals(LogMark))
                            {
                                item.updateExpireTime();
                                await _ipLogRepository.UpdateAsync(item);
                                return Tuple.Create(logResult, 0, "操作成功");
                            }
                        }
                    }
                    if (usingCount < ipMaxUser)
                    {
                        logResult = new IpLog(GuidGenerator.Create(), IpAddress, CardId, ProjectId, LogMark, Nation, Province, City, District);
                        await _ipLogRepository.InsertAsync(logResult);
                        return Tuple.Create(logResult, 0, "操作成功");
                    }
                    return Tuple.Create(logResult, 11, "ip同时使用次数达到限制");
                }
                else {
                    return Tuple.Create(logResult, 12, "无法访问资源");
                }
            }


        }



    }
}
