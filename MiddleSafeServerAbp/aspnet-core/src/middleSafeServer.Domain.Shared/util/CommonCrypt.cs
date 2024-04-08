using System;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;

namespace middleSafeServer.util
{
    public class CommonCrypt
    {
        static public string makeMd5(string _content)
        {
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

        static public uint stringToHashNumber(string _content, ushort groupLength = 10000)
        {
            if (groupLength == 0) groupLength = 10000;
            byte[] data = Encoding.UTF8.GetBytes(_content);
            uint tmpHex = 0;
            foreach (var item in data)
            {
                if (tmpHex > 212345678) tmpHex = 0;
                tmpHex += item;
            }

            return tmpHex % groupLength;
        }

    }
}
