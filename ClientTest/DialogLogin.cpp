// DialogLogin.cpp: 实现文件
//

#include "pch.h"
#include "ClientTest.h"
#include "afxdialogex.h"
#include "DialogLogin.h"
#include <string>
#include "stringHelp.h"
#include "../middleServerSDK/stringHelp.h"
using namespace std;
// DialogLogin 对话框

IMPLEMENT_DYNAMIC(DialogLogin, CDialogEx)

DialogLogin::DialogLogin(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
{

}

DialogLogin::~DialogLogin()
{
}

void DialogLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1_CARDPWD, mEditCardPassword);
	DDX_Control(pDX, IDC_BUTTON_LOGIN, m_button_login);
}


BEGIN_MESSAGE_MAP(DialogLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &DialogLogin::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// DialogLogin 消息处理程序



void upLoadNameCollectTest() {
	//获得文件路径
	CString path = L"D:\\test.txt";
	//以只读方式打开
	CFile file(path, CFile::modeRead);
	//设置一个读取缓冲区
	char* pBuf;
	//获得文件内容长度
	int cnt = file.GetLength();
	//根据对应字符编码模式下的sizeof(TCHAR)，计算有多少个字符
	int chars = cnt / sizeof(char);
	//为缓冲区分配大小，+1操作是为了在结尾加一个结束符
	pBuf = new char[chars + 1];
	//第一个是将读到的内容放入的地方，第二个是读取的长度
	file.Read(pBuf, cnt);
	//结尾+一个结束符
	pBuf[chars] = 0;

	//关闭文件
	file.Close();


	Json::Value nameList;
	Json::Value dto;
	dto["name"] = stringHelp::GBKToUTF8("小伙贼帅");
	dto["sex"] = 1;
	dto["headIconUrl"] = "http://client-profile-photo.eateapp.com/headIcon/7890083.jpg";
	dto["extendJson"] = stringHelp::GBKToUTF8("{ \"preName\":\"斌\"}");
	dto["infoAgentId"] = "3a07c004-8825-8439-81ce-17a6af12ae8e";
	dto["imageCollect"] = "";// string(pBuf);
	nameList.append(dto);
	safeServer.nameCollect(nameList.toStyledString());

	//文档关闭后释放申请的空间
	delete[] pBuf;
}










//登陆
void DialogLogin::OnBnClickedButtonLogin()
{
	CString pwd = L"3a07c1be-7c08-30f7-409c-f884e9cd92fd";
	//mEditCardPassword.GetWindowTextW(pwd); 

	if (pwd.IsEmpty()) {
		MessageBoxW(L"请输入卡密", L"异常", MB_OK | MB_ICONERROR);
		return;
	}

	string aPwd(CT2A(pwd.GetString()));
	tagServerResponse sc = safeServer.login(aPwd);

	//登陆异常
	if (sc.code != 0) {
		string detail = std::format("登陆失败,错误代码{} ,描述:{}", sc.code, sc.info); 
		MessageBoxA(this->GetSafeHwnd(), detail.c_str(), "异常", MB_OK | MB_ICONERROR);
		return;
	}

	//sc = safeServer.setCardTitle("堆栈,无!");								  //测试通过
	//safeServer.errorCollect("测试异常", "异常消息1", "异常堆栈无");		  //测试通过

	//safeServer.reportPropCollect("测试物品收集", "1234fa", 10, "测试备注"); //测试通过
	  
	//upLoadNameCollectTest(); 									          //测试通过


	//tagServerRandomNameCollectResponse nameInfo = safeServer.getRandomNameCollect("3A077E2D-A770-9E5E-BA72-14AA3CD22A5F");
	

	this->PostMessageW(WM_CLOSE, 0, 0);

}

