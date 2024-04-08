// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "httplib.h"
#include " WebAlgorithm.h"
#include "Base64.h"
#include "ServerApi.h" 
#include "CEncrypt.h"


//std::string httpTetst() {
//    httplib::Client cli("www.baidu.com", 80);
//    //cli.set_basic_auth("xxx", "xxx");
//    httplib::Headers headers = {
//        {"Accept-Encoding", "gzip"}
//    }; // [notice: Better set it, otherwise it's download slow]
//    auto res = cli.Get("/"); //cli.Post("url", headers, "post", "application/json"); 
//
//    return "";
//}

void testUUIDDecrypt() {
     



    //////https://localhost:44367
    ServerApi  c("https://localhost:44367");
    bool sc = c.login("84e0b69e-eece-ea72-ffad-3a0421a84e9d");

    int ip = c.ping();

    int lu = c.logout();


    //std::string enStr = "`CbA4l3:,b_o+5^r+jYm.B+7&9Xs\"1TD(9!3";
    //WebAlgorithm wa;
    //std::string result = wa.GUIDDecrypt(enStr);
    //OutputDebugStringA((result + "\r\n").c_str()); //testOK

    //std::string gaStr = "X592WKtarMo04WnsNfyrbrPbShp9Im9h7U9gAy8YXATybYpsWF9Ts8dZAKw6yoYzJ0amVXTjVjMlo0YW0xMGNtSjJSUT09Ke";
    //std::string cardPwd = "b8efacbb-7d43-4da5-9f48-9a75d8c68d30";
    //std::string  sss = wa.GetstringDecrypt(gaStr, cardPwd);

}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        testUUIDDecrypt();
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

