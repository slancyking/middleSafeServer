﻿#pragma once
#include "afxdialogex.h"
#include "appSetting.h"

// CSettingDlg 对话框

class CSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSettingDlg)

public:
	CSettingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSettingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SETTING };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()


	appSetting* mAppSetting = NULL;

public:
	CButton mCheckAutoInject;
	CEdit mEditDllPath;
	CEdit mEditProcessDetail;
	CEdit mEditProcessName;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	CEdit mEditWebTitle;
};
