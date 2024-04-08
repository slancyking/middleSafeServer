#pragma once
#include "afxdialogex.h"


// DialogLogin 对话框

class DialogLogin : public CDialogEx
{
	DECLARE_DYNAMIC(DialogLogin)

public:
	DialogLogin(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~DialogLogin();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LOGIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit mEditCardPassword;
	CButton m_button_login;
	afx_msg void OnBnClickedButtonLogin();
};
