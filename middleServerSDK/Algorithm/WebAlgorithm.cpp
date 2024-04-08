#include "../pch.h"
#include "CEncrypt.h"
#include "WebAlgorithm.h"
#include "Base64.h"

 
 
std::string WebAlgorithm::GUIDDecrypt(std::string source)
{
	if (source.length() == 0) return "";
    if (source.length() % 2 != 0) return "";
    std::string newString = "";
    int Round = 0;
    int sLen = source.length();
    for (int i = 0; i < sLen; i++)
    {
        if (i % 2 == 0)
        {
            Round++;
            newString += ((char)( (BYTE)source.at(i) + Round));
            continue;
        }
         
        int lastNumber = hex2int((char)((BYTE)source.at(i - 1) + Round)); 
        BYTE posByte = (BYTE)source.at(i);
        BYTE newByte = (BYTE)(posByte - lastNumber);
        newString += (char)newByte;
    }
    newString = newString.substr(4);  
    return newString.insert(20, "-").insert(16, "-").insert(12, "-").insert(8, "-");
     
}



static  std::string cutGuid(std::string gid)
{
    replace_str(gid, "-", "");
    std::string result = gid.substr(0, 16);
    return result;
}


std::string WebAlgorithm::GetstringDecrypt(std::string _content, std::string sguid)
{
    std::string ranKey = _content.substr(_content.length() - 34, 32);
    char decode[32] = { NULL };
    char decodeEx[32] = { NULL };

    replace_str(_content, ranKey, "");

    Base64 b64;
    std::string result1 = b64.Decode(ranKey.c_str(), 32);
    std::string result2 = b64.Decode(result1.c_str(), result1.length());
    std::string winformkey = cutGuid(sguid);
      
    return  CEncrypt::AESDecrypt(winformkey, result2, _content); //std::string();//

     
}
