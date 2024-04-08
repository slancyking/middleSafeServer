using Org.BouncyCastle.Asn1;
using Org.BouncyCastle.Asn1.Pkcs;
using Org.BouncyCastle.Asn1.X509;
using Org.BouncyCastle.Crypto;
using Org.BouncyCastle.Crypto.Encodings;
using Org.BouncyCastle.Crypto.Engines;
using Org.BouncyCastle.Crypto.Generators;
using Org.BouncyCastle.Crypto.Parameters;
using Org.BouncyCastle.Pkcs;
using Org.BouncyCastle.Security;
using Org.BouncyCastle.X509;
using System;
using System.Diagnostics;
using System.IO;

namespace middleSafeServer.util
{ 
 public sealed class RSACrypt2
    {
        /// <summary>
        /// 生成签名
        /// </summary>
        public static RSAKEY GetKey(int keyleng)
        {
            //RSA密钥对的构造器  
            RsaKeyPairGenerator keyGenerator = new RsaKeyPairGenerator();
            //RSA密钥构造器的参数  
            RsaKeyGenerationParameters param = new RsaKeyGenerationParameters(
                Org.BouncyCastle.Math.BigInteger.ValueOf(3),
                new Org.BouncyCastle.Security.SecureRandom(),
                keyleng,   //密钥长度  
                25);
            //用参数初始化密钥构造器  
            keyGenerator.Init(param);
            //产生密钥对  
            AsymmetricCipherKeyPair keyPair = keyGenerator.GenerateKeyPair();
            //获取公钥和密钥  
            AsymmetricKeyParameter publicKey = keyPair.Public;
            AsymmetricKeyParameter privateKey = keyPair.Private;
            SubjectPublicKeyInfo subjectPublicKeyInfo = SubjectPublicKeyInfoFactory.CreateSubjectPublicKeyInfo(publicKey);
            PrivateKeyInfo privateKeyInfo = PrivateKeyInfoFactory.CreatePrivateKeyInfo(privateKey);
            Asn1Object asn1ObjectPublic = subjectPublicKeyInfo.ToAsn1Object();
            byte[] publicInfoByte = asn1ObjectPublic.GetEncoded("UTF-8");
            Asn1Object asn1ObjectPrivate = privateKeyInfo.ToAsn1Object();
            byte[] privateInfoByte = asn1ObjectPrivate.GetEncoded("UTF-8");
            RSAKEY item = new RSAKEY()
            {
                PublicKey = Convert.ToBase64String(publicInfoByte),
                PrivateKey = Convert.ToBase64String(privateInfoByte)
            };
            return item;
        }
        private static AsymmetricKeyParameter GetPublicKeyParameter(string s)
        {
            s = s.Replace("\r", "").Replace("\n", "").Replace(" ", "");
            byte[] publicInfoByte = Convert.FromBase64String(s);
            Asn1Object pubKeyObj = Asn1Object.FromByteArray(publicInfoByte);//这里也可以从流中读取，从本地导入   
            AsymmetricKeyParameter pubKey = PublicKeyFactory.CreateKey(publicInfoByte);
            return pubKey;
        }
        private static AsymmetricKeyParameter GetPrivateKeyParameter(string s)
        {
            s = s.Replace("\r", "").Replace("\n", "").Replace(" ", "");
            byte[] privateInfoByte = Convert.FromBase64String(s);
            // Asn1Object priKeyObj = Asn1Object.FromByteArray(privateInfoByte);//这里也可以从流中读取，从本地导入   
            // PrivateKeyInfo privateKeyInfo = PrivateKeyInfoFactory.CreatePrivateKeyInfo(privateKey);
            AsymmetricKeyParameter priKey = PrivateKeyFactory.CreateKey(privateInfoByte);
            return priKey;
        }
        /// <summary>
        /// 私钥加密
        /// </summary>
        /// <param name="s">明文</param>
        /// <param name="key">私钥(java产出的string)</param>
        public static string EncryptByPrivateKey(string s, string key)
        {
            int aa = System.Environment.TickCount; //计时用


            //非对称加密算法，加解密用  
            IAsymmetricBlockCipher engine = new Pkcs1Encoding(new RsaEngine());
            //加密  
            try
            {
                engine.Init(true, GetPrivateKeyParameter(key));
                byte[] byteData = System.Text.Encoding.UTF8.GetBytes(s);
                int MaxBlockSize = engine.GetInputBlockSize();    //加密块最大长度限制
                using (MemoryStream PlaiStream = new MemoryStream(byteData))
                {
                    using (MemoryStream CrypStream = new MemoryStream())
                    {
                        Byte[] Buffer = new Byte[MaxBlockSize];
                        int BlockSize = PlaiStream.Read(Buffer, 0, MaxBlockSize);
                        while (BlockSize > 0)
                        {
                            Byte[] ToEncrypt = new Byte[BlockSize];
                            Array.Copy(Buffer, 0, ToEncrypt, 0, BlockSize);

                            Byte[] Cryptograph = engine.ProcessBlock(ToEncrypt, 0, BlockSize);
                            CrypStream.Write(Cryptograph, 0, Cryptograph.Length);

                            BlockSize = PlaiStream.Read(Buffer, 0, MaxBlockSize);
                        }
                        int useTime = System.Environment.TickCount - aa;
                        Console.WriteLine("加密执行时间: {0} ", useTime);
                        return Convert.ToBase64String(CrypStream.ToArray());
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("加密异常: {0} ", ex.Message);
                return ex.Message;
            }

        }
        /// <summary>
        /// 公钥解密
        /// </summary>
        /// <param name="s">明文</param>
        /// <param name="key">公钥(java产出的string)</param>
        public static string DecryptByPublicKey(string s, string key)
        {
            s = s.Replace("\r", "").Replace("\n", "").Replace(" ", "");
            //非对称加密算法，加解密用  
            IAsymmetricBlockCipher engine = new Pkcs1Encoding(new RsaEngine());
            //解密  
            try
            {
                engine.Init(false, GetPublicKeyParameter(key));
                byte[] byteData = Convert.FromBase64String(s);

                int MaxBlockSize = engine.GetInputBlockSize();    //加密块最大长度限制
                using (MemoryStream PlaiStream = new MemoryStream(byteData))
                {
                    using (MemoryStream CrypStream = new MemoryStream())
                    {
                        Byte[] Buffer = new Byte[MaxBlockSize];
                        int BlockSize = PlaiStream.Read(Buffer, 0, MaxBlockSize);
                        while (BlockSize > 0)
                        {
                            Byte[] ToEncrypt = new Byte[BlockSize];
                            Array.Copy(Buffer, 0, ToEncrypt, 0, BlockSize);

                            Byte[] Cryptograph = engine.ProcessBlock(ToEncrypt, 0, BlockSize);
                            CrypStream.Write(Cryptograph, 0, Cryptograph.Length);

                            BlockSize = PlaiStream.Read(Buffer, 0, MaxBlockSize);
                        }
                        return System.Text.Encoding.UTF8.GetString(CrypStream.ToArray());
                    }
                } 
                
            }
            catch (Exception ex)
            {
                return ex.Message;
            }
        }
        /// <summary>
        /// KEY 结构体
        /// </summary>
        public struct RSAKEY
        {
            public string PublicKey { get; set; }// 公钥
            public string PrivateKey { get; set; }// 私钥
        }
    }

}
