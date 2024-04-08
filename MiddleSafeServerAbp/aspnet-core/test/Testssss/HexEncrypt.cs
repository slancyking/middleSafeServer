using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Security.Cryptography;


namespace middleSafeServer.util
{
    public static class HexEncrypt
    {
        /// <summary>
        /// AES加密
        /// </summary>
        /// <param name="plainStr">明文字符串</param>
        /// <returns>密文</returns>
        private static string AESEncrypt(string plainStr, string Key, string IV)
        {
            byte[] bKey = Encoding.UTF8.GetBytes(Key);
            byte[] bIV = Encoding.UTF8.GetBytes(IV);
            byte[] byteArray = Encoding.UTF8.GetBytes(plainStr);

            string encrypt = null;
            Rijndael aes = Rijndael.Create();
            try
            {
                using (MemoryStream mStream = new MemoryStream())
                {
                    using (CryptoStream cStream = new CryptoStream(mStream, aes.CreateEncryptor(bKey, bIV), CryptoStreamMode.Write))
                    {
                        cStream.Write(byteArray, 0, byteArray.Length);
                        cStream.FlushFinalBlock();
                        encrypt = Convert.ToBase64String(mStream.ToArray());
                    }
                }
            }
            catch { }
            aes.Clear();

            return encrypt;
        }

        /// <summary>
        /// AES加密
        /// </summary>
        /// <param name="plainStr">明文字符串</param>
        /// <param name="returnNull">加密失败时是否返回 null，false 返回 String.Empty</param>
        /// <returns>密文</returns>
        public static string AESEncrypt(string plainStr, string Key, string IV, bool returnNull = true)
        {
            string encrypt = AESEncrypt(plainStr, Key, IV);
            return returnNull ? encrypt : (encrypt == null ? String.Empty : encrypt);
        }

        /// <summary>
        /// AES解密
        /// </summary>
        /// <param name="encryptStr">密文字符串</param>
        /// <returns>明文</returns>
        private static string AESDecrypt(string encryptStr, string Key, string IV)
        {
            byte[] bKey = Encoding.UTF8.GetBytes(Key);
            byte[] bIV = Encoding.UTF8.GetBytes(IV);
            byte[] byteArray = Convert.FromBase64String(encryptStr);

            string decrypt = null;
            Rijndael aes = Rijndael.Create();
            try
            {
                using (MemoryStream mStream = new MemoryStream())
                {
                    using (CryptoStream cStream = new CryptoStream(mStream, aes.CreateDecryptor(bKey, bIV), CryptoStreamMode.Write))
                    {
                        cStream.Write(byteArray, 0, byteArray.Length);
                        cStream.FlushFinalBlock();
                        decrypt = Encoding.UTF8.GetString(mStream.ToArray());
                    }
                }
            }
            catch { }
            aes.Clear();

            return decrypt;
        }

        /// <summary>
        /// AES解密
        /// </summary>
        /// <param name="encryptStr">密文字符串</param>
        /// <param name="returnNull">解密失败时是否返回 null，false 返回 String.Empty</param>
        /// <returns>明文</returns>
        public static string AESDecrypt(string encryptStr, string Key, string IV, bool returnNull = true)
        {
            string decrypt = AESDecrypt(encryptStr, Key, IV);
            return returnNull ? decrypt : (decrypt == null ? String.Empty : decrypt);
        }



        /// <summary>
        /// Base64加密，解密方法
        /// </summary>
        /// <param name="s">输入字符串</param>
        /// <param name="c">true-加密,false-解密</param>
        static public string base64(string s, bool c)
        {
            try
            {
                if (c)
                {
                    return System.Convert.ToBase64String(System.Text.Encoding.Default.GetBytes(s));
                }
                else
                {
                    return System.Text.Encoding.Default.GetString(System.Convert.FromBase64String(s));
                }
            }
            catch (Exception e)
            {
                return "计算出错";
            }
        }

        /// <summary>
        /// 取一个随机字符串
        /// </summary>
        /// <param name="length">长度</param>
        /// <returns></returns>
        static public string GetRandomString(int length)
        {
            const string key = "abcdefghijklmnopqrstuvwxyzABCDEFGHJKLMNPQRSTUVWXYZ0123456789";
            if (length < 1)
                return string.Empty;

            Random rnd = new Random();
            byte[] buffer = new byte[8];

            ulong bit = 31;
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

        /*
            Guid.NewGuid().ToString() + "||" + (new Guid()).ToString()

            b8efacbb-7d43-4da5-9f48-9a75d8c68d30||00000000-0000-0000-0000-000000000000
             */
        static public string cutGuid(string gid)
        {
            string result = gid.Replace("-", "");
            result = result.Substring(0, 16);
            return result;
        }


        static public string GetstringDESenctypt(string _content, string sguid)
        {
            try
            {
                string winformkey = cutGuid(sguid);
                string _randomStr = GetRandomString(16);
                _content = AESEncrypt(_content, winformkey, _randomStr);
                _randomStr = base64(_randomStr, true);
                _randomStr = base64(_randomStr, true);
                _content = _content.Insert(_content.Length - 2, _randomStr);
                return _content;
            }
            catch
            {
                return "";
            }
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

        /// <summary>
        /// uuid的简单解密 
        /// </summary>
        /// <param name="_content"></param>
        /// <returns></returns>
        static public string UUIDDecrypt(string _content)
        {
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
          

    }
}
