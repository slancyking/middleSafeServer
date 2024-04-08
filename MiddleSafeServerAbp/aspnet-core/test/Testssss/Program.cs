using middleSafeServer.util;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Security.Cryptography;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using static Testssss.RSACrypt2;
using System.Net.Mail;
using System.Net;
using SixLabors.ImageSharp;
using SixLabors.ImageSharp.Formats;
using System.IO;

namespace Testssss
{

    /// <summary>
    /// 客户端请求基类
    /// </summary>
    public class CardClientRequstBase
    {
        /// <summary>
        /// 客户端请求超时时间,单位秒
        /// </summary>
        private const int CardClientRequestTimeOut = 60;

        /// <summary>
        /// 请求时间
        /// </summary>
        public int PostUnix { get; set; }

        /// <summary>
        /// 检测是否超时,超时返回真
        /// </summary>
        /// <returns></returns>
        public bool bCheckTimeout()
        {
            DateTime dtStart = TimeZone.CurrentTimeZone.ToLocalTime(new DateTime(1970, 1, 1));
            long lTime = long.Parse(PostUnix + "0000");
            TimeSpan toNow = new TimeSpan(lTime);
            DateTime dtResult = dtStart.Add(toNow);

            return dtResult.AddSeconds(CardClientRequestTimeOut) < DateTime.Now;
        }

    }


    public class CardPingDto : CardClientRequstBase
    {
        /// <summary>
        /// 登陆凭证
        /// </summary>
        public string Token { get; set; }
    }


   


    internal class Program
    {

        /// <summary>
        /// 取一个随机字符串
        /// </summary>
        /// <param name="length">长度</param>
        /// <returns></returns>
        static public string GetRandomString(int length)
        {
            const string key = "abcdef0123456789";
            if (length < 1)
                return string.Empty;

            Random rnd = new Random();
            byte[] buffer = new byte[8];

            ulong bit = 15;
            ulong result = 0;
            int index = 0;
            StringBuilder sb = new StringBuilder((length / 5 + 1) * 5);

            while (sb.Length < length)
            {
                rnd.NextBytes(buffer);

                buffer[5] = buffer[6] = buffer[7] = 0x00;
                result = BitConverter.ToUInt64(buffer, 0);

                while (result > 0 && sb.Length < length)
                {
                    index = (int)(bit & result);
                    sb.Append(key[index]);
                    result = result >> 5;
                }
            }
            return sb.ToString();
        }


        static public string Token2ShortString(string _content)
        { 

            if (string.IsNullOrEmpty(_content)) return "";
            string srouce = GetRandomString(4) +  _content.Replace("-", "");
            if (srouce.Length % 2 != 0) return "";
            string newString = "";
            int Round = 0;
            for (int i = 0; i < srouce.Length; i++)
            {
                if (i % 2 == 0)
                {
                    Round++;
                    newString += (char) ((Byte)srouce[i]  - Round);
                    continue;
                }
                int lastNumber = int.Parse(srouce[i-1].ToString(), System.Globalization.NumberStyles.HexNumber);
                Byte posByte = (Byte)srouce[i];
                Byte newByte = (byte)(posByte + lastNumber); 
                newString += (char)newByte; 
            }

            return newString;
        }


        static public string ShortString2Token(string _content) {
            if (string.IsNullOrEmpty(_content)) return "";
            if (_content.Length % 2 != 0) return ""; 
            string newString = "";
            int Round = 0;
            for (int i = 0; i < _content.Length; i++)
            {
                if (i % 2 == 0)
                {
                    Round++;
                    newString += ((char)((Byte)_content[i] + Round));
                    continue;
                }
                int lastNumber = int.Parse(((char)((Byte)_content[i - 1] + Round)).ToString(), System.Globalization.NumberStyles.HexNumber);
                Byte posByte = (Byte)_content[i];
                Byte newByte = (byte)(posByte - lastNumber);
                newString += (char)newByte;
            }
            newString = newString.Substring(4);
            return newString.Insert(20, "-").Insert(16, "-").Insert(12, "-").Insert(8, "-");
        }

        static public string GetRandomStringForHex(int length)
        {
            const string key = "abcdef0123456789";
            if (length < 1)
                return string.Empty;

            Random rnd = new Random();
            byte[] buffer = new byte[8];

            ulong bit = 15;
            ulong result = 0;
            int index = 0;
            StringBuilder sb = new StringBuilder((length / 5 + 1) * 5);

            while (sb.Length < length)
            {
                rnd.NextBytes(buffer);

                buffer[5] = buffer[6] = buffer[7] = 0x00;
                result = BitConverter.ToUInt64(buffer, 0);

                while (result > 0 && sb.Length < length)
                {
                    index = (int)(bit & result);
                    sb.Append(key[index]);
                    result = result >> 5;
                }
            }
            return sb.ToString();
        }
        /// <summary>
        /// uuid 的简单加密  
        /// </summary>
        /// <param name="_content"></param>
        /// <returns></returns>
        static public string UUIDEncrypt(string _content)
        {
            if (string.IsNullOrEmpty(_content)) return "";
            string srouce = GetRandomStringForHex(4) + _content.Replace("-", "");
            if (srouce.Length % 2 != 0) return "";
            string newString = "";
            int Round = 0;
            for (int i = 0; i < srouce.Length; i++)
            {
                if (i % 2 == 0)
                {
                    Round++;
                    newString += (char)((Byte)srouce[i] - Round);
                    continue;
                }
                int lastNumber = int.Parse(srouce[i - 1].ToString(), System.Globalization.NumberStyles.HexNumber);
                Byte posByte = (Byte)srouce[i];
                Byte newByte = (byte)(posByte + lastNumber);
                newString += (char)newByte;
            } 
            return newString;
        }


        static public string makeMd5(string _content) {
            MD5 md5 = new MD5CryptoServiceProvider();
             
            byte[] data = Encoding.UTF8.GetBytes(_content);
            byte[] result = md5.ComputeHash(data);
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < 16; i++)
            {
                sb.Append(result[i].ToString("X2")); 
            }

            return sb.ToString();
        }


        static public uint stringToHashNumber(string _content, ushort groupLength)
        {
            if(groupLength == 0) groupLength = 10000;
            byte[] data = Encoding.UTF8.GetBytes(_content);
            uint tmpHex = 0;

            foreach (var item in data)
            {
                if (tmpHex > 212345678) tmpHex = 0;
                tmpHex += item;
            }
            
            return tmpHex % groupLength;
        }




        static public void testSendMail() {
            MailMessage mailmessage = new MailMessage("18680176145@163.com", "119985151@qq.com", "测试标题", "测试内容");
            //from email，to email，主题，邮件内容
            mailmessage.Priority = MailPriority.Normal; //邮件优先级
            SmtpClient smtpClient = new SmtpClient("smtp.163.com", 25); //smtp地址以及端口号
            smtpClient.Credentials = new NetworkCredential("18680176145@163.com", "ZXBOVRTNHGGXYBFO");//smtp用户名密码
            smtpClient.EnableSsl = false; //启用ssl                                            
            smtpClient.Send(mailmessage); //发送邮件
        }

        static public void testLoadImage() {
            System.Net.ServicePointManager.SecurityProtocol = (SecurityProtocolType)(0xc0 | 0x300 | 0xc00);
            WebRequest request = WebRequest.Create("http://client-profile-photo.eateapp.com/headIcon/7890059.jpg");
            WebResponse response = request.GetResponse();
            Stream reader = response.GetResponseStream();

            Image tmpImage = Image.Load(reader);

            reader.Close();
            reader.Dispose();
            response.Close();
            response.Dispose();

            uint Image64Size = (uint)(tmpImage.Width * tmpImage.Height);

            tmpImage.Dispose(); 

        }


        static void Main(string[] args)
        {
            testLoadImage();
            testSendMail();


            uint sdkfl = stringToHashNumber("篇文章也提到加密的问题,也可以使用Hash算法来计算输入的密码字符串,这样就的字符串就几乎不可能破解了。实现的方式将", 10000);



            string cardPwd = "b8efacbb-7d43-4da5-9f48-9a75d8c68d30";
            string token = Guid.NewGuid().ToString();
            Console.WriteLine("token:  " +  token);
            string encryptGuid = UUIDEncrypt(token);
            Console.WriteLine("UUIDEncrypt:  " + encryptGuid); 
            string enRes = HexEncrypt.GetstringDESenctypt(encryptGuid, cardPwd);
            Console.WriteLine("enRes:  " + enRes);

            long sdd = (long)((DateTime.Now.ToUniversalTime().Ticks - 621355968000000000) / 10000000);

            DateTime ss = DateTimeOffset.FromUnixTimeSeconds(sdd).DateTime.ToLocalTime();
             
            DateTime dtStart = TimeZone.CurrentTimeZone.ToLocalTime(new DateTime(1970, 1, 1));
            long lTime = long.Parse(1653316712 + "0000");
            TimeSpan toNow = new TimeSpan(lTime);
            DateTime dtResult = dtStart.Add(toNow);

            bool isTimeout = dtResult.AddSeconds(60) < DateTime.Now;


            //CardPingDto cd = new CardPingDto();
            //cd.PostUnix = 1000;
            //cd.Token = "asdakdlalkwdkac";

            //string serString = JsonConvert.SerializeObject(cd, Formatting.None);

            string sdadas = "{\"Token\":\"asdakdlalkwdkac\",\"PostUnix\":1000}";

            var ress = JsonConvert.DeserializeObject<CardPingDto>(sdadas);


            Stopwatch sw = new Stopwatch();
            sw.Start();
            RSAKEY key = RSACrypt2.GetKey(1024);
            string pub_key = key.PublicKey;
            string prv_key = key.PrivateKey;

            sw.Stop();
            TimeSpan ts2 = sw.Elapsed;
            
            Console.WriteLine("公钥私钥生产时间 {0}ms.", ts2.TotalMilliseconds);

            sw.Restart();


            string data = "mR5fY3TqNhMBuImJdmIR8C9JCPFWeUiURZvauRXu7SzIvMhsOQPWKRC3y7dO2NCtvt7kodgF2VG2cdaU0D2dgn0WDo8qoWcjjP/en9/IaaSlMKYlhrBAMlKI4NkvhkJ0I2KH89go9I4QmO4UDQrlXuaTc3BJ8XaVlYXNl9MQUjg=";
            // string data = "如果为 true，则使用 OAEP 填充（仅可用于运行 Windows XP 及更高版本的计算机）执行直接 RSA 加密；否则，如果为 false，则使用 PKCS#1 v1.5 填充";  
            //string data = "RSA 也可以用来为一个消息签名。签名应注意：不对数据M签名，而是对HASH（M）签名，可以使用时间戳，先签名后加密。实际应用中，对消息字符串的散列值（Message digest，用 MD5、SHA256 等算法求得的长度较短且固定的字符串）使用 RSA 的私钥进行签名（加密散列值）后，得到一个签名字符串，将其附加在消息字符串的合适位置后，一并发送。接收方使用对应的公钥可以从签名字符串中解密出原来的散列值，同时对原始消息再计算一次散列值。二者相比较，假如两者相符的话，则认为发信人持有正确的私钥，并且这个消息在传播路径上没有被篡改过。————————————————版权声明：本文为CSDN博主「基础Met」的原创文章，遵循CC 4.0 BY - SA版权协议，转载请附上原文出处链接及本声明。原文链接：https://blog.csdn.net/weixin_42369053/article/details/117063031";

            string pdecode = RSACrypt2.DecryptByPublicKey(data, "MIGdMA0GCSqGSIb3DQEBAQUAA4GLADCBhwKBgQC/u9fmh7deA00zTA7BKe4VUIYr9NkzN7DJ/t4FtrUEGSbCDX5rjTTC1n7gjxEB5wOHtaJ3d3ngS9V2Y3Fs7ipodXHPs9rjLUfBB1eGjqK4rX8y/6xRZ8CxzVVciehqvvuhG27L8i9JTOPPQMUNSjieoF/ymcjilE9wy9Yo0/tExQIBAw==");

            //for (int i = 0; i < 100; i++)
            //{
            //    ///公钥加密
            //    string encode = RSACrypt1.encryptData(data, pub_key, "utf-8");
            //    ///私钥解密
            //    string decode = RSACrypt1.decryptData(encode, prv_key, "utf-8");

            //    Console.WriteLine(string.Format("公钥加密:{0} ", encode));


            //    ///私钥加密
            //    string pencode = RSACrypt2.EncryptByPrivateKey(data, prv_key);
            //    ///公钥解密
                
            //    Console.WriteLine(string.Format("私钥加密:{0} ", pencode));

            //    Console.WriteLine(string.Format("方案1结果匹配:{0}  方案2:{1}", decode == data, pdecode == data));
            //    Console.WriteLine("==============================================\r\n");
            //}
            sw.Stop();
            TimeSpan ts3 = sw.Elapsed;
            Console.WriteLine("加密总共花费{0}ms.", ts3.TotalMilliseconds);




        }
    }
}
