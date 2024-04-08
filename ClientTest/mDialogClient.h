#pragma once
#include "afxdialogex.h" 
#include "clientProc.h" 
#include "ServerApi.h"
// mDialogClient 对话框

class mDialogClient : public CDialogEx
{
	DECLARE_DYNAMIC(mDialogClient)

public:
	mDialogClient(CWnd* pParent = nullptr);   // 标准构造函数
	mDialogClient(DWORD cPID, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~mDialogClient();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLIENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();

	void reDrawClient();




public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	CStatic mMsgGroup;
	CStatic mLogGroup;
	CRichEditCtrl mLogRichEdit;
	CListBox mMsgRecord; 
	CEdit mEditSendMsg;
	CButton mButtonSendMsg;
	CButton mButtonRunScript;
	CButton mButtonCloseClient;
	CStatic mOptionGroup;
	afx_msg void OnBnClickedButtonSendmsg();
	afx_msg void OnBnClickedButtonRunScript();
	afx_msg void OnBnClickedButtonClientClose();
	 
	DWORD m_pid;
	tagServerReportResponse clientInfo;
	clientProc* mClientProc = NULL;

	void printLog(string log);
	 
	void addRecordCommond(CString cmd);
	 

	afx_msg void OnLbnDblclkListMsgRecord();
};

//子线程函数 负责客户端心跳
UINT thread_ClientPing(LPVOID pParam);