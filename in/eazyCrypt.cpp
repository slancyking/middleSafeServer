#include "pch.h"
#include "eazyCrypt.h"
#pragma warning (disable: 4996)
std::string eazyCrypt::makeMd5ByString(std::string str, bool longger, bool upper)
{ 
    return eazyCrypt::makeMd5ByBuffer((void*)str.c_str(), str.size(), longger, upper); 
}

std::string eazyCrypt::makeMd5ByBuffer(void* buf, size_t size, bool longger, bool upper)
{
    std::string tt = "";
    UINT mdSize = longger ? 16 : 8; 
    unsigned char out[16] = { 0 };
    MD5_CTX c;
    MD5_Init(&c);
    MD5_Update(&c, buf, size);
    MD5_Final(out, &c);
    for (int i = 0; i < mdSize; i++) {
        if (upper) {
            tt += std::format("{:02X}", (int)out[i]);
        }
        else {
            tt += std::format("{:02x}", (int)out[i]);
        }

    }
        

    return tt;
}

