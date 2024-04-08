// mDialogClient.cpp: 实现文件
//

#include "pch.h"
#include "ClientTest.h"
#include "afxdialogex.h"
#include "mDialogClient.h"



// mDialogClient 对话框

IMPLEMENT_DYNAMIC(mDialogClient, CDialogEx)

mDialogClient::mDialogClient(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CLIENT, pParent)
{

}

mDialogClient::mDialogClient(DWORD cPID, CWnd* pParent) : CDialogEx(IDD_DIALOG_CLIENT, pParent)
{
	m_pid = cPID;
	clientInfo = safeServer.normalQuery(format("{}", cPID));
	mClientProc = new clientProc(clientInfo.report.randomPort, clientInfo.report.randomKey);
	if (false == mClientProc->init()) {
		OutputDebugString(L"mClientProc->init() FF"); 
	}
}

mDialogClient::~mDialogClient()
{
	if (mClientProc != NULL)
	{
		delete mClientProc;
		mClientProc = NULL;
	}
}

void mDialogClient::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_GROUP_MSG, mMsgGroup);
	DDX_Control(pDX, IDC_STATIC_GROUP_LOG, mLogGroup);
	DDX_Control(pDX, IDC_RICHEDIT2_LOG, mLogRichEdit);
	DDX_Control(pDX, IDC_LIST_MSG_RECORD, mMsgRecord);
	//  DDX_Control(pDX, IDC_EDIT_MSGSEND, mButtonSendMsg);
	DDX_Control(pDX, IDC_EDIT_MSGSEND, mEditSendMsg);
	DDX_Control(pDX, IDC_BUTTON_SENDMSG, mButtonSendMsg);
	DDX_Control(pDX, IDC_BUTTON_RUN_SCRIPT, mButtonRunScript);
	DDX_Control(pDX, IDC_BUTTON_CLIENT_CLOSE, mButtonCloseClient);
	DDX_Control(pDX, IDC_STATIC_GROUP_OPTION, mOptionGroup);
}


BEGIN_MESSAGE_MAP(mDialogClient, CDialogEx)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_SENDMSG, &mDialogClient::OnBnClickedButtonSendmsg)
	ON_BN_CLICKED(IDC_BUTTON_RUN_SCRIPT, &mDialogClient::OnBnClickedButtonRunScript)
	ON_BN_CLICKED(IDC_BUTTON_CLIENT_CLOSE, &mDialogClient::OnBnClickedButtonClientClose)
	ON_LBN_DBLCLK(IDC_LIST_MSG_RECORD, &mDialogClient::OnLbnDblclkListMsgRecord)
END_MESSAGE_MAP()


// mDialogClient 消息处理程序


void mDialogClient::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}

void mDialogClient::reDrawClient()
{
	if (mMsgGroup.GetSafeHwnd() == NULL) { return; }


	//计算分组位置
	RECT rct = {};
	this->GetClientRect(&rct);
	mMsgGroup.MoveWindow(0, 10, 380, rct.bottom - 20, TRUE); 
	mLogGroup.MoveWindow(390, 70, rct.right - 400, rct.bottom - 80, TRUE); 
	mOptionGroup.MoveWindow(390, 10, rct.right - 400, 60, TRUE);

	//计算消息组位置 
	mMsgGroup.GetClientRect(&rct); 
	mEditSendMsg.MoveWindow(rct.left + 10, rct.top + 30, rct.right - 20, (rct.bottom - rct.top) / 2 - 20);
	mMsgRecord.MoveWindow(rct.left + 10, (rct.bottom - rct.top) / 2 + 20, rct.right - 20, (rct.bottom - rct.top) / 2 - 20);

	//计算日志组位置
	mLogGroup.GetClientRect(&rct);
	mLogRichEdit.MoveWindow(rct.left + 400, rct.top + 90, rct.right - 20, rct.bottom - rct.top - 30);

	 
}


BOOL mDialogClient::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	  
	mEditSendMsg.SetWindowTextW(L"{\r\n\t\"msgID\":\"ping\",\
		         \r\n\t\"args\":{ }\
		\r\n}");

	if (NULL == AfxBeginThread(thread_ClientPing, this)) {
		MessageBox(_T("子线程 [ping客户端] 创建失败!"), _T("异常×"));
		exit(0);
	}

	mLogRichEdit.SendMessage(WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), MAKELPARAM(FALSE, 0));

	reDrawClient();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void mDialogClient::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	reDrawClient(); 
}

//发送消息
void mDialogClient::OnBnClickedButtonSendmsg()
{
	CString _msg;
    mEditSendMsg.GetWindowTextW(_msg);

	addRecordCommond(_msg);

	string aMsg(CT2A(_msg.GetString()));
	string result = mClientProc->sendMsgByString(aMsg,"");

	printLog(format("发送消息:\r\n{} \r\n \r\n返回:\r\n{} \r\n\r\n\r\n\r\n ====================================================\r\n", aMsg, result));

}

//执行脚本
void mDialogClient::OnBnClickedButtonRunScript()
{
	// TODO: 在此添加控件通知处理程序代码
}

//关闭客户端
void mDialogClient::OnBnClickedButtonClientClose()
{
	HWND hc = FindMainWindow(m_pid);
	if (hc != NULL)
		::SendMessage(hc, WM_CLOSE, 0, 0);

 

	if (mClientProc != NULL)
	{
		delete mClientProc;
		mClientProc = NULL;
	}

	this->GetParent()->SendMessage(MSG_CLOSE_CLIENT, m_pid);
}

void mDialogClient::printLog(string log)
{
	CString _timeHead = CTime::GetCurrentTime().Format("%d %H:%M:%S") + " : " + CString(CA2T(log.c_str())) + L"\r\n";
	  
	mLogRichEdit.SetSel(-1, -1);
	mLogRichEdit.ReplaceSel(_timeHead);
	mLogRichEdit.SendMessage(WM_VSCROLL, SB_BOTTOM, 0);

}

void mDialogClient::addRecordCommond(CString cmd)
{ 
	mMsgRecord.InsertString(0, cmd); 
}

//负责与服务端心跳
UINT thread_ClientPing(LPVOID pParam)
{
	mDialogClient* _this = (mDialogClient*)pParam;
	HWND hWnd = _this->GetSafeHwnd();
	while (::IsWindow(hWnd))
	{ 
		if (_this->mClientProc->ping() == false)
			break;

		Sleep(5000);
	}
	OutputDebugStringA("退出线程 thread_ClientPing ");
	return 0;
}


void mDialogClient::OnLbnDblclkListMsgRecord()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel = mMsgRecord.GetCurSel();
	if (sel == -1)
		return;

	CString cmd;
	mMsgRecord.GetText(sel, cmd);
	mEditSendMsg.SetWindowTextW(cmd);
}
