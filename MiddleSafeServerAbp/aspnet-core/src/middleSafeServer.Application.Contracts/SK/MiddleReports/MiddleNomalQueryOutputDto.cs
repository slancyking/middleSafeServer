namespace middleSafeServer.SK.MiddleReports
{

    /// <summary>
    /// 中间 自然查询 输出实体
    /// </summary>
    public class MiddleNomalQueryOutputDto
    {
        /// <summary>
        /// 服务端的标志位,可以是进程id.之类的
        /// </summary>
        public string Flag { get; set; }

        /// <summary>
        /// 随机端口
        /// </summary> 
        public int RandomPort { get; set; }

        /// <summary>
        /// 随机秘钥
        /// </summary> 
        public string RandomKey { get; set; }

        /// <summary>
        /// 秘钥索引
        /// </summary>
        public int KeyIndex { get; set; }

        /// <summary>
        /// 提示信息
        /// </summary>
        public string Info { get; set; }

    }
}
