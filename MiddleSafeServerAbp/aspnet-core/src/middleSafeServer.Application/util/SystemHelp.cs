using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace middleSafeServer.util
{
    /// <summary>
    /// 系统帮助类
    /// </summary>
    public static class SystemHelp
    {
        /// <summary>
        /// 获取系统信息
        /// </summary>
        /// <returns></returns>
        public static string GetSystemInfo()
        {
            StringBuilder sysinfo = new StringBuilder();


            sysinfo.AppendLine(string.Format("操作系统版本:{0}", Environment.OSVersion.ToString()));

            sysinfo.AppendLine(string.Format("系统镜像版本:{0}", Environment.Version.ToString()));

            sysinfo.AppendLine(string.Format("系统启动时间:{0}", TimeSpan.FromMilliseconds(Environment.TickCount).ToString()));

            sysinfo.AppendLine(string.Format("系统盘符: {0}", Environment.GetEnvironmentVariable("systemdrive")));

            String[] drives = Environment.GetLogicalDrives();
            sysinfo.AppendLine(string.Format("计算机盘符枚举: {0}", String.Join(", ", drives)));

            sysinfo.AppendLine(string.Format("当前程序占用内存: {0}", DiskH1elp.ConverToStringB(Environment.WorkingSet)));



            sysinfo.AppendLine(string.Format("程序 {0}", DiskH1elp.GetProgramDirFreeSizeString()));

            sysinfo.AppendLine(string.Format("数据库文件 {0}", DiskH1elp.GetDbDirFreeSizeString()));

            return sysinfo.ToString();
        }

    }
}
