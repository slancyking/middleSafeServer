#pragma once
#include <string>  
 


namespace CEncrypt { 

    // base64 ±‡¬Î
    std::string __stdcall base64Encode(const char* buffer, int length, int newLine);

    int __stdcall base64_decode(const char* str, int str_len, char* decode, int decode_buffer_len);

    void __stdcall handleOpenSSLErrors();
    std::string  __stdcall AES_CBC_PKCS5_BASE64_Encrypt(unsigned char* src, unsigned char* key, unsigned char* iv);
    // aes Ω‚√‹
    std::string  __stdcall AESDecrypt(std::string kString, std::string ivString, std::string eString);
     

    std::string __stdcall RsaPubDecrypt(const std::string& cipher_text, const std::string& pub_key);
    std::string __stdcall RsaPubEncrypt(const std::string& clear_text, const std::string& pub_key);
};