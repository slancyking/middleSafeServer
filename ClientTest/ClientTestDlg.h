
// ClientTestDlg.h: 头文件
//

#pragma once
#include "CNewTabCtrl.h"
#include "../CRejection/CRejection.h"
#include "mDialogClient.h"
// CClientTestDlg 对话框
class CClientTestDlg : public CDialogEx
{
// 构造
public:
	CClientTestDlg(CWnd* pParent = nullptr);	// 标准构造函数
	~CClientTestDlg();
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLIENTTEST_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	virtual void OnOK();

	

	


public:
	CNewTabCtrl m_tabClient;
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void drawClientList();

	//新增一个客户端到tab标签
	bool addClient(DWORD pid);
	//移除一个客户端从tab标签
	void removeClient(DWORD pid);


	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);


	CRejection lockClient;
	std::map<DWORD, mDialogClient*> clientList;

	CMenu m_menu;

	afx_msg void OnSetting();
	afx_msg void OnLogout();
};

//子线程函数 负责检测新增客户端
UINT thread_CheckClients(LPVOID pParam);