#pragma once
#include "afxcmn.h"
//
#include <list>
//
#include <map>

//MFCTabCtrl


struct _tagTabCtrlinfo{
	CString     name;
	HWND        Hwnd;
};

class CNewTabCtrlDelegate {
public:

	// 纯虚函数, 切换到了一个新的 tab 标签
	virtual void switchTabItem(int itemIndex, CString & columnString, HWND hwnd) const = 0;

};


class CNewTabCtrl : public CTabCtrl {
	DECLARE_DYNAMIC(CNewTabCtrl)
public:
	CNewTabCtrl();

	virtual ~CNewTabCtrl();

protected:
	DECLARE_MESSAGE_MAP()

protected:
	afx_msg void OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult);

public:
	void WriteDelegate(CNewTabCtrlDelegate * pthis) {
		this->gthis_Delegate = pthis;
	};

public:
	BOOL  NewItemBuffer(CString name, HWND  hwnd);

	BOOL  removeItemBuffer(CString name);

	BOOL  RefreshTabCtrlItemBuffer();

	BOOL  SwitchItem(CString name);

	CString  ReadSelItemString();




public:
	int   ReadItemBufferCount();
	HWND  ReadItemHwnd(int iIndex);


protected:
	std::map<int, _tagTabCtrlinfo>  gTabItemBuffer;
	std::map<CString, int>          gItemIndex;


	CNewTabCtrlDelegate         *   gthis_Delegate = NULL;

};

