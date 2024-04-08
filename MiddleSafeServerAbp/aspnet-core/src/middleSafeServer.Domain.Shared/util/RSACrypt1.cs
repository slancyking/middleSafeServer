using System;
using System.IO;
using System.Security.Cryptography;
using System.Text;

namespace middleSafeServer.util
{
    public sealed class RSACrypt1
    {

        /// <summary>  
        /// 公钥加密  
        /// </summary>  
        /// <param name="resData">需要加密的字符串</param>  
        /// <param name="publicKey">公钥</param>  
        /// <param name="input_charset">编码格式</param>  
        /// <returns>明文</returns>  
        public static string encryptData(string resData, string publicKey, string input_charset)
        {
            byte[] DataToEncrypt = Encoding.UTF8.GetBytes(resData);
            string result = encrypt(DataToEncrypt, publicKey, input_charset);
            return result;
        }
        /// <summary>  
        /// 私钥解密  
        /// </summary>  
        /// <param name="resData">加密字符串</param>  
        /// <param name="privateKey">私钥</param>  
        /// <param name="input_charset">编码格式</param>  
        /// <returns>明文</returns>  
        public static string decryptData(string resData, string privateKey, string input_charset)
        {
            byte[] DataToDecrypt = Convert.FromBase64String(resData);
            string result = ""; 
             
            result += decrypt(DataToDecrypt, privateKey, input_charset);
            return result;
        }
        private static string encrypt(byte[] data, string publicKey, string input_charset)
        {
            RSACryptoServiceProvider rsa = DecodePemPublicKey(publicKey);

            int MaxBlockSize = rsa.KeySize / 8 - 11;    //加密块最大长度限制 

            if (data.Length <= MaxBlockSize)
                return Convert.ToBase64String(rsa.Encrypt(data, false));

            using (MemoryStream PlaiStream = new MemoryStream(data))
            {
                using (MemoryStream CrypStream = new MemoryStream())
                {
                    Byte[] Buffer = new Byte[MaxBlockSize];
                    int BlockSize = PlaiStream.Read(Buffer, 0, MaxBlockSize);

                    while (BlockSize > 0)
                    {
                        Byte[] ToEncrypt = new Byte[BlockSize];
                        Array.Copy(Buffer, 0, ToEncrypt, 0, BlockSize);

                        Byte[] Cryptograph = rsa.Encrypt(ToEncrypt, false);
                        CrypStream.Write(Cryptograph, 0, Cryptograph.Length);

                        BlockSize = PlaiStream.Read(Buffer, 0, MaxBlockSize);
                    }

                    return Convert.ToBase64String(CrypStream.ToArray(), Base64FormattingOptions.None);

                }
            }  
             
        }
        private static string decrypt(byte[] data, string privateKey, string input_charset)
        {

            string result = "";
            RSACryptoServiceProvider rsa = DecodePemPrivateKey(privateKey);
            int MaxBlockSize = rsa.KeySize / 8;    //解密块最大长度限制

            using (MemoryStream CrypStream = new MemoryStream(data)) {
                using (MemoryStream PlaiStream = new MemoryStream())
                {
                    Byte[] Buffer = new Byte[MaxBlockSize];
                    int BlockSize = CrypStream.Read(Buffer, 0, MaxBlockSize);
                    while (BlockSize > 0)
                    {
                        Byte[] ToDecrypt = new Byte[BlockSize];
                        Array.Copy(Buffer, 0, ToDecrypt, 0, BlockSize);

                        Byte[] Plaintext = rsa.Decrypt(ToDecrypt, false);
                        PlaiStream.Write(Plaintext, 0, Plaintext.Length);

                        BlockSize = CrypStream.Read(Buffer, 0, MaxBlockSize);
                    }

                    byte[] source = PlaiStream.ToArray();
                    char[] asciiChars = new char[Encoding.GetEncoding(input_charset).GetCharCount(source, 0, source.Length)];
                    Encoding.GetEncoding(input_charset).GetChars(source, 0, source.Length, asciiChars, 0);
                    result = new string(asciiChars);
                    return result;
                }
            } 
        }
        private static RSACryptoServiceProvider DecodePemPrivateKey(String pemstr)
        {
            byte[] pkcs8privatekey;
            pkcs8privatekey = Convert.FromBase64String(pemstr);
            if (pkcs8privatekey != null)
            {
                RSACryptoServiceProvider rsa = DecodePrivateKeyInfo(pkcs8privatekey);
                return rsa;
            }
            else
                return null;
        }
        private static RSACryptoServiceProvider DecodePrivateKeyInfo(byte[] pkcs8)
        {
            byte[] SeqOID = { 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00 };
            byte[] seq = new byte[15];
            MemoryStream mem = new MemoryStream(pkcs8);
            int lenstream = (int)mem.Length;
            BinaryReader binr = new BinaryReader(mem);
            byte bt = 0;
            ushort twobytes = 0;
            try
            {
                twobytes = binr.ReadUInt16();
                if (twobytes == 0x8130)
                    binr.ReadByte();
                else if (twobytes == 0x8230)
                    binr.ReadInt16();
                else
                    return null;
                bt = binr.ReadByte();
                if (bt != 0x02)
                    return null;
                twobytes = binr.ReadUInt16();
                if (twobytes != 0x0001)
                    return null;
                seq = binr.ReadBytes(15);
                if (!CompareBytearrays(seq, SeqOID))
                    return null;
                bt = binr.ReadByte();
                if (bt != 0x04)
                    return null;
                bt = binr.ReadByte();
                if (bt == 0x81)
                    binr.ReadByte();
                else
                    if (bt == 0x82)
                    binr.ReadUInt16();
                byte[] rsaprivkey = binr.ReadBytes((int)(lenstream - mem.Position));
                RSACryptoServiceProvider rsacsp = DecodeRSAPrivateKey(rsaprivkey);
                return rsacsp;
            }
            catch (Exception)
            {
                return null;
            }
            finally { binr.Close(); }
        }
        private static bool CompareBytearrays(byte[] a, byte[] b)
        {
            if (a.Length != b.Length)
                return false;
            int i = 0;
            foreach (byte c in a)
            {
                if (c != b[i])
                    return false;
                i++;
            }
            return true;
        }
        private static RSACryptoServiceProvider DecodeRSAPrivateKey(byte[] privkey)
        {
            byte[] MODULUS, E, D, P, Q, DP, DQ, IQ;
            MemoryStream mem = new MemoryStream(privkey);
            BinaryReader binr = new BinaryReader(mem);
            byte bt = 0;
            ushort twobytes = 0;
            int elems = 0;
            try
            {
                twobytes = binr.ReadUInt16();
                if (twobytes == 0x8130)
                    binr.ReadByte();
                else if (twobytes == 0x8230)
                    binr.ReadInt16();
                else
                    return null;
                twobytes = binr.ReadUInt16();
                if (twobytes != 0x0102)
                    return null;
                bt = binr.ReadByte();
                if (bt != 0x00)
                    return null;
                elems = GetIntegerSize(binr);
                MODULUS = binr.ReadBytes(elems);
                elems = GetIntegerSize(binr);
                E = binr.ReadBytes(elems);
                elems = GetIntegerSize(binr);
                D = binr.ReadBytes(elems);
                elems = GetIntegerSize(binr);
                P = binr.ReadBytes(elems);
                elems = GetIntegerSize(binr);
                Q = binr.ReadBytes(elems);
                elems = GetIntegerSize(binr);
                DP = binr.ReadBytes(elems);
                elems = GetIntegerSize(binr);
                DQ = binr.ReadBytes(elems);
                elems = GetIntegerSize(binr);
                IQ = binr.ReadBytes(elems);
                RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();
                RSAParameters RSAparams = new RSAParameters();
                RSAparams.Modulus = MODULUS;
                RSAparams.Exponent = E;
                RSAparams.D = D;
                RSAparams.P = P;
                RSAparams.Q = Q;
                RSAparams.DP = DP;
                RSAparams.DQ = DQ;
                RSAparams.InverseQ = IQ;
                RSA.ImportParameters(RSAparams);
                return RSA;
            }
            catch (Exception)
            {
                return null;
            }
            finally { binr.Close(); }
        }
        private static int GetIntegerSize(BinaryReader binr)
        {
            byte bt = 0;
            byte lowbyte = 0x00;
            byte highbyte = 0x00;
            int count = 0;
            bt = binr.ReadByte();
            if (bt != 0x02)
                return 0;
            bt = binr.ReadByte();
            if (bt == 0x81)
                count = binr.ReadByte();
            else
                if (bt == 0x82)
            {
                highbyte = binr.ReadByte();
                lowbyte = binr.ReadByte();
                byte[] modint = { lowbyte, highbyte, 0x00, 0x00 };
                count = BitConverter.ToInt32(modint, 0);
            }
            else
            {
                count = bt;
            }
            while (binr.ReadByte() == 0x00)
            {
                count -= 1;
            }
            binr.BaseStream.Seek(-1, SeekOrigin.Current);
            return count;
        }
        private static RSACryptoServiceProvider DecodePemPublicKey(String pemstr)
        {
            byte[] pkcs8publickkey;
            pkcs8publickkey = Convert.FromBase64String(pemstr);
            if (pkcs8publickkey != null)
            {
                RSACryptoServiceProvider rsa = DecodeRSAPublicKey(pkcs8publickkey);
                return rsa;
            }
            else
                return null;
        }

        private static RSACryptoServiceProvider DecodeRSAPublicKey(byte[] publickey)
        {
            byte[] SeqOID = { 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, 0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00 };
            byte[] seq = new byte[15];
            MemoryStream mem = new MemoryStream(publickey);
            BinaryReader binr = new BinaryReader(mem);
            byte bt = 0;
            ushort twobytes = 0;
            try
            {
                twobytes = binr.ReadUInt16();
                if (twobytes == 0x8130)
                    binr.ReadByte();
                else if (twobytes == 0x8230)
                    binr.ReadInt16();
                else
                    return null;
                seq = binr.ReadBytes(15);
                if (!CompareBytearrays(seq, SeqOID))
                    return null;
                twobytes = binr.ReadUInt16();
                if (twobytes == 0x8103)
                    binr.ReadByte();
                else if (twobytes == 0x8203)
                    binr.ReadInt16();
                else
                    return null;
                bt = binr.ReadByte();
                if (bt != 0x00)
                    return null;
                twobytes = binr.ReadUInt16();
                if (twobytes == 0x8130)
                    binr.ReadByte();
                else if (twobytes == 0x8230)
                    binr.ReadInt16();
                else
                    return null;
                twobytes = binr.ReadUInt16();
                byte lowbyte = 0x00;
                byte highbyte = 0x00;
                if (twobytes == 0x8102)
                    lowbyte = binr.ReadByte();
                else if (twobytes == 0x8202)
                {
                    highbyte = binr.ReadByte();
                    lowbyte = binr.ReadByte();
                }
                else
                    return null;
                byte[] modint = { lowbyte, highbyte, 0x00, 0x00 };
                int modsize = BitConverter.ToInt32(modint, 0);
                byte firstbyte = binr.ReadByte();
                binr.BaseStream.Seek(-1, SeekOrigin.Current);
                if (firstbyte == 0x00)
                {
                    binr.ReadByte();
                    modsize -= 1;
                }
                byte[] modulus = binr.ReadBytes(modsize);
                if (binr.ReadByte() != 0x02)
                    return null;
                int expbytes = (int)binr.ReadByte();
                byte[] exponent = binr.ReadBytes(expbytes);
                RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();
                RSAParameters RSAKeyInfo = new RSAParameters();
                RSAKeyInfo.Modulus = modulus;
                RSAKeyInfo.Exponent = exponent;
                RSA.ImportParameters(RSAKeyInfo);
                return RSA;
            }
            catch (Exception)
            {
                return null;
            }
            finally { binr.Close(); }
        }
    }

}
