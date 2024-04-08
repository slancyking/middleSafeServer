using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace middleSafeServer.util
{
    /// <summary>
    /// 硬盘帮助类
    /// </summary>
    public static class DiskH1elp
    {
        private const long KiloByte = 1024;
        private const long MegaByte = KiloByte * KiloByte;
        private const long GigaByte = MegaByte * KiloByte;
        private const long TeraByte = GigaByte * KiloByte;

        private const string Err_DbFile = "(数据库文件不存在,请检查 appsettings.json 中 [UserConfig]:[DbFile]配置项是否正常)";


        /// <summary>
        /// 数据库文件
        /// </summary>
        private static readonly string sDbFile = ConfigHelper.GetAppSetting("UserConfig", "DbFile");
        /// <summary>
        /// 数据库日志文件
        /// </summary>
        private static readonly string sDbLogFile = ConfigHelper.GetAppSetting("UserConfig", "DblogFile");

        private const string IISLogFile = @"\inetpub\logs\LogFiles";

        /// <summary>
        /// 换算成kb
        /// </summary>
        /// <param name="v">字节数</param>
        /// <returns></returns>
        private static string ConverToKb(long v)
        {
            return string.Format("{0:N2} Kb", ((double)v / KiloByte));
        }

        /// <summary>
        /// 换算成Mb
        /// </summary>
        /// <param name="v">字节数</param>
        /// <returns></returns>
        private static string ConverToMb(long v)
        {
            return string.Format("{0:N2} Mb", ((double)v / MegaByte));
        }

        /// <summary>
        /// 单位换算换算成Gb
        /// </summary>
        /// <param name="v">字节数</param>
        /// <returns></returns>
        private static string ConverToGb(long v)
        {
            return string.Format("{0:N2} Gb", ((double)v / GigaByte));
        }

        /// <summary>
        /// 换算成Tb
        /// </summary>
        /// <param name="v">字节数</param>
        /// <returns></returns>
        private static string ConverToTb(long v)
        {
            return string.Format("{0:N2} Tb", ((double)v / TeraByte));
        }


        /// <summary>
        /// 字节转换到描述
        /// </summary>
        /// <param name="v"></param>
        /// <returns></returns>
        public static string ConverToStringB(long v)
        {
            string B = string.Empty;
            if (v >= TeraByte) { B = ConverToTb(v); }
            else if (v >= GigaByte) { B = ConverToGb(v); }
            else if (v >= MegaByte) { B = ConverToMb(v); }
            else if (v >= KiloByte) { B = ConverToKb(v); }
            else
            {
                B = string.Format("{0} Byte", v);
            }

            return B;
        }


        /// <summary>
        /// 格式化硬盘容量字符串
        /// </summary>
        /// <param name="Name"></param>
        /// <param name="AllSize"></param>
        /// <param name="FreeSize"></param>
        /// <returns></returns>
        public static string FormatSpaceString(string Name, long AllSize, long FreeSize)
        {
            string fString = string.Empty;
            string sAllsize = ConverToStringB(AllSize), sFreeSize = ConverToStringB(FreeSize);
            fString = string.Format("{0} (可用 {1},总共 {2})", Name, sAllsize, sFreeSize);
            return fString;
        }



        /// <summary>
        /// 获取某一文件夹的大小
        /// </summary>
        /// <param name="dir">文件夹目录</param>
        /// <param name="dirSize">文件夹大小</param>
        public static void GetDirSizeByPath(string dir, ref long dirSize)
        {
            try
            {
                DirectoryInfo dirInfo = new DirectoryInfo(dir);
                if (!dirInfo.Exists) { return; }
                DirectoryInfo[] dirs = dirInfo.GetDirectories();
                FileInfo[] files = dirInfo.GetFiles();

                foreach (var item in dirs)
                {
                    GetDirSizeByPath(item.FullName, ref dirSize);
                }

                foreach (var item in files)
                {
                    dirSize += item.Length;
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("获取文件大小失败" + ex.Message);
            }
        }

        /// <summary>
        /// 获取IIS日志大小
        /// </summary>
        /// <returns></returns>
        public static long GetIISLogSize()
        {
            string sIISlogFloder = Environment.GetEnvironmentVariable("systemdrive") + IISLogFile;
            long dirSize = 0;
            GetDirSizeByPath(sIISlogFloder, ref dirSize);
            return dirSize;
        }

        /// <summary>
        /// 根据一个目录返回所在盘符剩余空间
        /// </summary>
        /// <param name="floder"></param>
        /// <returns></returns>
        public static long GetDeriveFreeeSizeByFolder(string floder)
        {
            DirectoryInfo fdir = new DirectoryInfo(floder);
            if (!fdir.Exists) return 0;

            DriveInfo[] allDirves = DriveInfo.GetDrives();
            //检索计算机上的所有逻辑驱动器名称
            foreach (DriveInfo item in allDirves)
            {
                //Fixed 硬盘
                //Removable 可移动存储设备，如软盘驱动器或USB闪存驱动器。

                if (item.IsReady && floder.StartsWith(item.Name))
                {
                    return item.TotalFreeSpace;
                }
            }
            return 0;
        }

        /// <summary>
        /// 根据文件夹返回所在盘符
        /// </summary>
        /// <param name="floder"></param>
        /// <returns></returns>
        public static string GetDeriveNameByFolder(string floder)
        {
            DirectoryInfo fdir = new DirectoryInfo(floder);
            if (!fdir.Exists) return "";

            DriveInfo[] allDirves = DriveInfo.GetDrives();
            //检索计算机上的所有逻辑驱动器名称
            foreach (DriveInfo item in allDirves)
            {
                //Fixed 硬盘
                //Removable 可移动存储设备，如软盘驱动器或USB闪存驱动器。

                if (item.IsReady && floder.StartsWith(item.Name))
                {
                    return item.Name;
                }
            }
            return "";

        }


        /// <summary>
        /// 获取数据库文件大小
        /// </summary>
        /// <returns></returns>
        public static long GetDbFileSize()
        {
            FileInfo dbFileInfo = new FileInfo(sDbFile);
            if (!dbFileInfo.Exists) return 0;
            return dbFileInfo.Length;
        }

        /// <summary>
        /// 获取数据库文件大小字符串
        /// </summary>
        /// <returns></returns>
        public static string GetDbFileSizeString()
        {
            long dSize = GetDbFileSize();
            if (dSize == 0) { return Err_DbFile; }
            return ConverToStringB(dSize);
        }

        /// <summary>
        /// 获取数据库日志文件大小
        /// </summary>
        /// <returns></returns>
        public static long GetDbLogFileSize()
        {
            FileInfo dbLogFileInfo = new FileInfo(sDbLogFile);
            if (!dbLogFileInfo.Exists) return 0;
            return dbLogFileInfo.Length;
        }

        /// <summary>
        /// 获取数据库日志文件大小字符串
        /// </summary>
        /// <returns></returns>
        public static string GetDbLogFileSizeString()
        {
            long dSize = GetDbLogFileSize();
            if (dSize == 0) { return Err_DbFile; }
            return ConverToStringB(dSize);
        }

        /// <summary>
        /// 获取程序所在文件夹大小
        /// </summary>
        /// <returns></returns>
        public static long GetAppFolderSize()
        {
            long dirSize = 0;
            GetDirSizeByPath(Environment.CurrentDirectory, ref dirSize);
            return dirSize;
        }

        /// <summary>
        /// 获取程序所在文件夹大小字符串
        /// </summary>
        /// <returns></returns>
        public static string GetAppFolderSizeString()
        {
            long dSize = GetAppFolderSize();
            if (dSize == 0) { return Err_DbFile; }
            return ConverToStringB(dSize);
        }

        /// <summary>
        /// 获取文件所在盘符剩余空间
        /// </summary>
        /// <returns>字节数</returns>
        public static long GetDriveFreeSizeByFloder(string floder)
        {
            return GetDeriveFreeeSizeByFolder(floder);
        }


        /// <summary>
        /// 获取文件所在盘符剩余空间字符串
        /// </summary>
        /// <returns>字节数</returns>
        public static string GetDriveFreeSizeStringByFloder(string floder)
        {
            return ConverToStringB(GetDriveFreeSizeByFloder(floder));
        }

        /// <summary>
        /// 获取程序所在目录剩余空间
        /// </summary>
        /// <returns></returns>
        public static long GetProgramDirFreeSize()
        {
            return GetDriveFreeSizeByFloder(Environment.CurrentDirectory);
        }

        /// <summary>
        /// 获取程序所在目录剩余空间 字符串 例如 2.1mb
        /// </summary>
        /// <returns></returns>
        public static string GetProgramDirFreeSizeString()
        {
            return string.Format("所在目录 {0} ,剩余空间 {1}", Environment.CurrentDirectory, GetDriveFreeSizeStringByFloder(Environment.CurrentDirectory));
        }

        /// <summary>
        /// 获取数据库所在目录剩余空间
        /// </summary>
        /// <returns>字节数</returns>
        public static long GetDbDirFreeSize()
        {
            return GetDriveFreeSizeByFloder(sDbFile);
        }

        /// <summary>
        /// 获取数据库所在目录剩余空间 字符串  例如 2.1mb
        /// </summary>
        /// <returns></returns>
        public static string GetDbDirFreeSizeString()
        {
            return string.Format("所在目录 {0} ,剩余空间 {1}", sDbFile, GetDriveFreeSizeStringByFloder(sDbFile));
        }

    }
}
