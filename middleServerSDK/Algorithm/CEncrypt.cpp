 
#include "CEncrypt.h"
#include <openssl/aes.h> 
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/bio.h>  
#include <openssl/buffer.h>   
#include <vcruntime_string.h>
#include <string.h>
#include <memory>
#include <string>  
#include "Base64.h" 
#include <openssl/pem.h>

#define AES_BLOCK_SIZE 16

// base64 编码
std::string __stdcall CEncrypt::base64Encode(const char* buffer, int length, int newLine)
{
    BIO* bmem = NULL;
    BIO* b64 = NULL;
    BUF_MEM* bptr;

    b64 = BIO_new(BIO_f_base64());
    if (!newLine) {
        BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    }
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_write(b64, buffer, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);
    BIO_set_close(b64, BIO_NOCLOSE);
    std::shared_ptr< char > tAsciiString(new char[bptr->length + 1]);
    if (NULL == tAsciiString.get()) { return ""; }
    memset(tAsciiString.get(), 0, sizeof(char) * (bptr->length + 1));
    memcpy(tAsciiString.get(), bptr->data, sizeof(char) * (bptr->length));
    BIO_free_all(b64);
    return tAsciiString.get();
}

int __stdcall CEncrypt::base64_decode(const char* str, int str_len, char* decode, int decode_buffer_len) {
    int len = 0;
    BIO* b64, * bmem;
    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new_mem_buf(str, str_len);
    bmem = BIO_push(b64, bmem);
    len = BIO_read(bmem, decode, str_len);
    decode[len] = 0;
    BIO_free_all(bmem);
    return 0;

}

void __stdcall CEncrypt::handleOpenSSLErrors()
{
    unsigned long errCode;
    printf("An error occurred\n");
    while (errCode = ERR_get_error()) {
        char* err = ERR_error_string(errCode, NULL);
        printf("%s\n", err);
    }
    //abort();
}
/* AES_CBC_PKCS5_BASE64_Encrypt
* 入参:
* src:明文
* srcLen:明文长度
* key:密钥 长度只能是16/24/32字节 否则OPENSSL会对key进行截取或PKCS0填充
* keyLen:密钥长度
* outLen:密文base64后长度
* 返回值: 密文base64后的字符串，使用后请free

   //todo:EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc() ...中的EVP_aes_128_cbc 目前硬编码后续可以优化
*/

std::string  __stdcall CEncrypt::AES_CBC_PKCS5_BASE64_Encrypt(unsigned char* src, unsigned char* key, unsigned char* iv)
{
    int srcLen = strlen((char*)src);
    EVP_CIPHER_CTX* ctx = NULL;
    std::string res = "";
    int blockCount = 0;
    int quotient = srcLen / AES_BLOCK_SIZE;
    int mod = srcLen % AES_BLOCK_SIZE;
    blockCount = quotient + 1;

    int padding = AES_BLOCK_SIZE - mod;
    std::shared_ptr< char > in(new char[AES_BLOCK_SIZE * blockCount]);
    memset(in.get(), padding, AES_BLOCK_SIZE * blockCount);
    memcpy(in.get(), src, srcLen);

    //out
    std::shared_ptr< char > out(new char[AES_BLOCK_SIZE * blockCount]);
    memset(out.get(), 0x00, AES_BLOCK_SIZE * blockCount);
    int outLen = AES_BLOCK_SIZE * blockCount;

    do {
        if (!(ctx = EVP_CIPHER_CTX_new())) {
            handleOpenSSLErrors();
            break;
        }

        if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv)) {
            handleOpenSSLErrors();
            break;
        }

        if (1 != EVP_EncryptUpdate(ctx, (unsigned char*)out.get(), &outLen, (unsigned char*)in.get(), AES_BLOCK_SIZE * blockCount)) {
            handleOpenSSLErrors();
            break;
        }
        res = base64Encode(out.get(), outLen, 0);
    } while (0);

    if (ctx != NULL)
        EVP_CIPHER_CTX_free(ctx);

    return res;
}

// aes 解密
std::string  __stdcall CEncrypt::AESDecrypt(std::string kString, std::string ivString, std::string eString) {
    int t_len = eString.size();
    Base64 b64;
    std::string result = b64.Decode(eString.c_str(), t_len);


    EVP_CIPHER_CTX* evp_cipher = NULL;
    const EVP_CIPHER* aes_128_cbc = NULL;
    unsigned char* aesDecString = NULL;
    int					   aesDecSize = 0;
    std::string				   dString = "";
    //char* eBuffer = new char[eString.length()];
    int		eSize = 0;
    int BufSize = eString.length();
    //base64_decode(eString.c_str(), eString.length(), eBuffer, eSize);


    do
    {
        if (NULL == (evp_cipher = EVP_CIPHER_CTX_new()))
            break;
        if (NULL == (aes_128_cbc = EVP_aes_128_cbc()))
            break;

        uint64_t dBufferSize = BufSize;

        //创建返回内容 缓冲区
        if (NULL == (aesDecString = (unsigned char*)malloc(dBufferSize)))
            break;
        memset(aesDecString, 0, dBufferSize);

        //开始 aes 加密处理
        EVP_CIPHER_CTX_init(evp_cipher);

        EVP_DecryptInit_ex(evp_cipher, aes_128_cbc, 0,
            (unsigned char*)kString.c_str(), (unsigned char*)ivString.c_str()
        );

        EVP_DecryptUpdate(evp_cipher, aesDecString, &eSize,
            (unsigned char*)result.data(), result.size()
        );

        aesDecSize += eSize;

        EVP_DecryptFinal_ex(evp_cipher, &aesDecString[eSize], &eSize);

        aesDecSize += eSize;

        for (size_t i = aesDecSize; i < dBufferSize; i++)
            aesDecString[i] = '\0';

        dString = (char*)aesDecString;
    } while (false);

    if (NULL != evp_cipher)   EVP_CIPHER_CTX_cleanup(evp_cipher);
    if (NULL != aesDecString) free(aesDecString);
    //if (NULL != eBuffer)	  free(eBuffer);
    return dString;
}

 


/* https://www.freesion.com/article/4013555983/
@brief : 公钥解密
@para  : cipher_text -[i] 加密的密文
         pub_key     -[i] 公钥
@return: 解密后的数据
**/
std::string __stdcall CEncrypt::RsaPubDecrypt(const std::string& cipher_text, const std::string& pub_key)
{
     
    Base64 b64;
    std::string debase = b64.Decode(cipher_text.c_str(), cipher_text.size());


    std::string decrypt_text;
    BIO* keybio = BIO_new_mem_buf((unsigned char*)pub_key.c_str(), -1);
    RSA* rsa = RSA_new();

    // 注意-------使用第1种格式的公钥进行解密
    //rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);
    // 注意-------使用第2种格式的公钥进行解密（我们使用这种格式作为示例）
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    if (!rsa)
    {
        unsigned long err = ERR_get_error(); //获取错误号
        char err_msg[1024] = { 0 };
        ERR_error_string(err, err_msg); // 格式：error:errId:库:函数:原因
        //printf("err msg: err:%ld, msg:%s\n", err, err_msg);
        BIO_free_all(keybio);

        return decrypt_text;
    }

    // 获取RSA单次处理的最大长度
    int len = RSA_size(rsa);
    char* sub_text = new char[len + 1];
    memset(sub_text, 0, len + 1);
    int ret = 0;
    std::string sub_str;
    int pos = 0;
    // 对密文进行分段解密
    while (pos < debase.length()) {
        sub_str = debase.substr(pos, len);
        memset(sub_text, 0, len + 1);
        ret = RSA_public_decrypt(sub_str.length(), (const unsigned char*)sub_str.c_str(), (unsigned char*)sub_text, rsa, RSA_PKCS1_PADDING);
        if (ret >= 0) {
            decrypt_text.append(std::string(sub_text, ret));
            printf("pos:%d, sub: %s\n", pos, sub_text);
            pos += len;
        }
    }

    // 释放内存  
    delete[] sub_text;
    BIO_free_all(keybio);
    RSA_free(rsa);

    return decrypt_text;
}

/*
@brief : 公钥加密
@para  : clear_text  -[i] 需要进行加密的明文
         pri_key     -[i] 私钥
@return: 加密后的数据
**/
std::string __stdcall CEncrypt::RsaPubEncrypt(const std::string& clear_text, const std::string& pub_key)
{
    std::string encrypt_text;
    BIO* keybio = BIO_new_mem_buf((unsigned char*)pub_key.c_str(), -1);
    RSA* rsa = RSA_new();
    // 注意-----第1种格式的公钥
    //rsa = PEM_read_bio_RSAPublicKey(keybio, &rsa, NULL, NULL);
    // 注意-----第2种格式的公钥（这里以第二种格式为例）
    rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);

    // 获取RSA单次可以处理的数据块的最大长度
    int key_len = RSA_size(rsa);
    int block_len = key_len - 11;    // 因为填充方式为RSA_PKCS1_PADDING, 所以要在key_len基础上减去11

    // 申请内存：存贮加密后的密文数据
    char* sub_text = new char[key_len + 1];
    memset(sub_text, 0, key_len + 1);
    int ret = 0;
    int pos = 0;
    std::string sub_str;
    // 对数据进行分段加密（返回值是加密后数据的长度）
    while (pos < clear_text.length()) {
        sub_str = clear_text.substr(pos, block_len);
        memset(sub_text, 0, key_len + 1);
        ret = RSA_public_encrypt(sub_str.length(), (const unsigned char*)sub_str.c_str(), (unsigned char*)sub_text, rsa, RSA_PKCS1_PADDING);
        if (ret >= 0) {
            encrypt_text.append(std::string(sub_text, ret));
        }
        pos += block_len;
    }

    // 释放内存  
    BIO_free_all(keybio);
    RSA_free(rsa);
    delete[] sub_text;
    encrypt_text = base64Encode(encrypt_text.c_str(), encrypt_text.size(), 0);
    return encrypt_text;
}