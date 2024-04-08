
// ClientTestDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ClientTest.h"
#include "ClientTestDlg.h"
#include "afxdialogex.h" 
#include "CSettingDlg.h"
#include "ProcessInfoShare.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//#pragma comment( lib, "middleServerSDK.lib" )


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
 
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
//	virtual void OnOK();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClientTestDlg 对话框



CClientTestDlg::CClientTestDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENTTEST_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CClientTestDlg::~CClientTestDlg()
{
	for (auto& c : clientList) {
		delete c.second; 
	}

}

void CClientTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_FOR_CLIENT, m_tabClient);
}

BEGIN_MESSAGE_MAP(CClientTestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	ON_COMMAND(ID_32772, &CClientTestDlg::OnSetting)
	ON_COMMAND(ID_32773, &CClientTestDlg::OnLogout)
END_MESSAGE_MAP()


// CClientTestDlg 消息处理程序

BOOL CClientTestDlg::OnInitDialog()
{  




	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	 
	/*if (NULL == AfxBeginThread(thread_CheckClients,this)) {
		MessageBox(_T("子线程 [检测客户端] 创建失败!"), _T("异常×"));
		exit(0);
	}*/

	m_menu.LoadMenuW(IDR_MENU1);
	SetMenu(&m_menu);

	/*drawClientList();*/

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClientTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClientTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClientTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
 

void CClientTestDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialogEx::OnOK();
}


void CClientTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	  
	//drawClientList();
	// TODO: 在此处添加消息处理程序代码



}

void CClientTestDlg::drawClientList()
{
	if (m_tabClient.GetSafeHwnd() == NULL) { return; }

	RECT rct = {};
	this->GetClientRect(&rct);
	m_tabClient.MoveWindow(0, 20, rct.right, rct.bottom - 20, TRUE);				
	 

	for (auto& c : clientList) {
		if (c.second->GetSafeHwnd() != NULL)
		{
			c.second->MoveWindow(10, 50, rct.right - 20, rct.bottom - 60, TRUE);
		}
	}
	 
}


bool CClientTestDlg::addClient(DWORD pid)
{
	CString strPid;
	strPid.Format(_T("%d"), pid);
	lockClient.OpenRejection();

	mDialogClient* newClient = new mDialogClient(pid, this);
	if (FALSE == newClient->Create(IDD_DIALOG_CLIENT, this)) {
		OutputDebugStringA("初始化 测试客户端 窗口失败");
		return FALSE;
	} 
	m_tabClient.NewItemBuffer(strPid, newClient->GetSafeHwnd()); 
	m_tabClient.RefreshTabCtrlItemBuffer(); 
	clientList.insert(std::pair<DWORD, mDialogClient*>(pid, newClient));

	lockClient.CloseRejection();
	 
	drawClientList();

	return true;
}

void CClientTestDlg::removeClient(DWORD pid)
{
	CString strPid;
	strPid.Format(_T("%d"), pid); 
	lockClient.OpenRejection();

	std::map<DWORD, mDialogClient*>::iterator mPosClient = clientList.find(pid);
	if (mPosClient != clientList.end())
	{
		delete mPosClient->second; 
		clientList.erase(mPosClient);
	}

	m_tabClient.removeItemBuffer(strPid);
	m_tabClient.RefreshTabCtrlItemBuffer(); 
	lockClient.CloseRejection();
}

void CClientTestDlg::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	lpMMI->ptMinTrackSize.x = 1024;			//最小宽度
	lpMMI->ptMinTrackSize.y = 768;			//最小高度
	CDialogEx::OnGetMinMaxInfo(lpMMI); 
}


BOOL CClientTestDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (MSG_CLOSE_CLIENT == message)
	{
		removeClient((DWORD)wParam);
		return TRUE;
	}
	if (MSG_OPEN_CLIENT == message) {
		addClient((DWORD)wParam);
		return TRUE;
	}

	return CDialogEx::OnWndMsg(message, wParam, lParam, pResult);
}

UINT thread_CheckClients(LPVOID pParam)
{
	CClientTestDlg* _this = (CClientTestDlg*)pParam;
	HWND hWnd = _this->GetSafeHwnd();
	int clientCount = -1;
	while (::IsWindow(hWnd))
	{ 

		if (_this->clientList.size() == 0)
			_this->SetWindowTextW(L"等待客户端连接...");
		else {
			CString title;
			title.Format(L"当前客户端数:%ld", _this->clientList.size());
			_this->SetWindowTextW(title);
		}
		DWORD pid = ProcessInfoShare::getClientPid();
		if (pid == 0)
		{
			Sleep(1000);
			continue;
		}
		 
		if (GetProcessVersion(pid))		 //此处用途  确认进程是否存在
			_this->SendMessage(MSG_OPEN_CLIENT, pid);
		 
		Sleep(1000);
	}

	return 0;
}


void CClientTestDlg::OnSetting()
{
	CSettingDlg  set = CSettingDlg(); 
	set.DoModal();
}


void CClientTestDlg::OnLogout()
{
	tagServerResponse sc = safeServer.logout();
	if (sc.code != 0) 
		MessageBoxA(this->GetSafeHwnd(), "提示", format("错误代码:{} ,信息:{}", sc.code, sc.info).c_str(), 0);

	exit(0);
}
