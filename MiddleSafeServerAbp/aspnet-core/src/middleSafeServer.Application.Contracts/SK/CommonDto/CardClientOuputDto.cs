using middleSafeServer.util;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text; 
namespace middleSafeServer.SK.CommonDto
{
    /// <summary>
    /// 卡密客户端用的输出实体
    /// </summary>
    public class CardClientOuputDto<T>
    {
        //执行结果实体 的json化 加密结果
        public string Result { get; set; }


        public CardClientOuputDto(T obj,string privateKey,bool b64 = false){
            string serString = JsonConvert.SerializeObject(obj, Formatting.None);

            if (b64) {
                Result = System.Convert.ToBase64String(System.Text.Encoding.Default.GetBytes(serString));
                return;
            }

            if (string.IsNullOrWhiteSpace(privateKey))
            {
                Result = serString;
            }
            else {
                Result = RSACrypt2.EncryptByPrivateKey(serString, privateKey);
            }
            
           
        }

    }
}
