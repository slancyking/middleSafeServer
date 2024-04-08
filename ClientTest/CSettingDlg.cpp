// CSettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "ClientTest.h"
#include "afxdialogex.h"
#include "CSettingDlg.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SETTING, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
	if (mAppSetting != NULL) {
		delete mAppSetting;
		mAppSetting = NULL;
	}
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_AUTO_INJECT, mCheckAutoInject);
	DDX_Control(pDX, IDC_EDIT_DLL_PATH, mEditDllPath);
	DDX_Control(pDX, IDC_EDIT_PROCESSDETAIL, mEditProcessDetail);
	DDX_Control(pDX, IDC_EDIT_PROCESSNAME, mEditProcessName);
	DDX_Control(pDX, IDC_EDIT_webTitle, mEditWebTitle);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSettingDlg::OnBnClickedOk)
END_MESSAGE_MAP()



// CSettingDlg 消息处理程序

void CSettingDlg::OnBnClickedOk()
{ 
	if (mAppSetting)
	{
		CStringW tmpString;

		mAppSetting->mAppSetting.autoInject = mCheckAutoInject.GetCheck();

		mEditDllPath.GetWindowTextW(tmpString);
		StrCpyW(mAppSetting->mAppSetting.dllFile, tmpString);

		mEditProcessDetail.GetWindowTextW(tmpString);
		StrCpyW(mAppSetting->mAppSetting.processDescription, tmpString);

		mEditProcessName.GetWindowTextW(tmpString);
		StrCpyW(mAppSetting->mAppSetting.targetProcessName, tmpString);

 
		mEditWebTitle.GetWindowTextW(tmpString);
		string aTitle(CT2A(tmpString.GetString()));
		safeServer.setCardTitle(aTitle);

		mAppSetting->saveSettiang();
	}
		
	CDialogEx::OnOK();
}


BOOL CSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	mAppSetting = new appSetting();
	mCheckAutoInject.SetCheck(mAppSetting->mAppSetting.autoInject);
	mEditDllPath.SetWindowTextW(mAppSetting->mAppSetting.dllFile);
	mEditProcessDetail.SetWindowTextW(mAppSetting->mAppSetting.processDescription);
	mEditProcessName.SetWindowTextW(mAppSetting->mAppSetting.targetProcessName); 

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


