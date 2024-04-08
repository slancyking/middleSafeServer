// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "eazyCrypt.h"
#include "msgProtocol.h"
#include "serverProc.h"

#include "wx/wx.h"

using namespace std;

static int mTouchCount = 0; 

void Test() {   

    //消息加解密测试
    string msgKey = "abc123456"; 
    sendMsgProtocol msgT("这是一个测试消息", msgKey); 
    UINT dSize = 0;   
    void* d = msgT.getData(dSize); 




    recvMsgProtocol cMsgP(d, dSize);
    string result = cMsgP.getMsg(msgKey);
    //////////////////////////////////////////////////
     
    time_t uTime = std::time(0);
}
 
 


BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        OutputDebugStringA("DLL_PROCESS_ATTACH \r\n"); 
        Test(); 
        if (serverProc::init()) {
            serverProc::run();
        } 
        break;
    case DLL_THREAD_ATTACH:
        OutputDebugStringA("DLL_THREAD_ATTACH \r\n");
        break;
    case DLL_THREAD_DETACH:
        OutputDebugStringA("DLL_THREAD_DETACH \r\n");
        break;
    case DLL_PROCESS_DETACH:
        OutputDebugStringA("DLL_PROCESS_DETACH \r\n");
        break;
    }
    return TRUE;
}

