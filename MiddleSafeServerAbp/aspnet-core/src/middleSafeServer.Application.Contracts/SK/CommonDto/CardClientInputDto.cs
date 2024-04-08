using middleSafeServer.util;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace middleSafeServer.SK.CommonDto
{
    /// <summary>
    /// 卡密客户端用的输入实体
    /// </summary>
    public class CardClientInputDto<T>
    {
        /// <summary>
        /// 卡密
        /// </summary>
        [Required]
        [StringLength(SKConsts.MaxCardPassword)]
        public string Password { get; set; }


        /// <summary>
        /// 参数 为具体参数实体 json化后加密
        /// </summary>
        [Required]
        public string Param { get; set; }

        /// <summary>
        /// 获取解密后参数
        /// </summary>
        /// <param name="privateKey"></param>
        /// <returns></returns>
        public T getParam(string privateKey) {
            string srouceString = RSACrypt1.decryptData(Param, privateKey, "utf-8"); 
            return JsonConvert.DeserializeObject<T>(srouceString);
        }





    }
}
