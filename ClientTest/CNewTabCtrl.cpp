#pragma once 
#include "pch.h"
#include "CNewTabCtrl.h"


CNewTabCtrl::CNewTabCtrl() : CTabCtrl(){



}


CNewTabCtrl::~CNewTabCtrl(){

}

IMPLEMENT_DYNAMIC(CNewTabCtrl, CTabCtrl)


BOOL CNewTabCtrl::NewItemBuffer(CString name, HWND  hwnd){
	int tNewBufferIndex = this->gTabItemBuffer.size();

	if (this->gItemIndex.find(name) != this->gItemIndex.end()){
		return FALSE;
	}

	this->gItemIndex.insert(std::pair<CString, int>(name, tNewBufferIndex));

	this->gTabItemBuffer.insert(std::pair<int, _tagTabCtrlinfo>(tNewBufferIndex, { name, hwnd }));

	return TRUE;
}

BOOL CNewTabCtrl::removeItemBuffer(CString name)
{
	int removeIndex = 0;

	std::map<CString, int>::iterator mPosItemIndex = this->gItemIndex.find(name);
	if (mPosItemIndex == this->gItemIndex.end())
		return FALSE;
	
	removeIndex = mPosItemIndex->second;

	std::map<int, _tagTabCtrlinfo>::iterator mPosTabItemBuf = this->gTabItemBuffer.find(mPosItemIndex->second);

	if (mPosTabItemBuf == this->gTabItemBuffer.end())
		return FALSE;

	this->gTabItemBuffer.erase(mPosTabItemBuf);

	this->gItemIndex.erase(mPosItemIndex);
	
	//索引修复
	for (auto& idx : this->gItemIndex) 
		if (idx.second > removeIndex)
			idx.second--;

	size_t bufCount = this->gTabItemBuffer.size();

	for (size_t i = removeIndex + 1; i <= bufCount; i++)
	{ 
		auto node = this->gTabItemBuffer.extract(i);

		if (!node.empty())
		{
			node.key() = i - 1;
			this->gTabItemBuffer.insert(std::move(node));
		}  
	}


	return TRUE;
}

BOOL CNewTabCtrl::RefreshTabCtrlItemBuffer(){

	this->DeleteAllItems();

	for (std::map<int, _tagTabCtrlinfo>::iterator i = this->gTabItemBuffer.begin(); i != this->gTabItemBuffer.end(); i++){

		if (FALSE == IsWindow(i->second.Hwnd)){ continue; }

		if (CB_ERR == this->InsertItem(this->GetItemCount(), i->second.name)){
			return FALSE;
		}

		::ShowWindow(i->second.Hwnd, SW_HIDE);
	}

	//展示 当前选中的 tab 下面绑定的子窗口
	if (this->gTabItemBuffer.find(this->GetCurSel()) != this->gTabItemBuffer.end()){
		::ShowWindow(this->gTabItemBuffer[this->GetCurSel()].Hwnd, SW_SHOW);
	}

	return TRUE;
}


BEGIN_MESSAGE_MAP(CNewTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(TCN_SELCHANGE, &CNewTabCtrl::OnTcnSelchange)
	ON_NOTIFY_REFLECT(TCN_SELCHANGING, &CNewTabCtrl::OnTcnSelchanging)
END_MESSAGE_MAP()


void CNewTabCtrl::OnTcnSelchange(NMHDR *pNMHDR, LRESULT *pResult){
	// TODO:  在此添加控件通知处理程序代码
	if (this->gTabItemBuffer.find(this->GetCurSel()) == this->gTabItemBuffer.end()){
		return ;
	}

	//是否已设置委任
	if (NULL != this->gthis_Delegate)
		this->gthis_Delegate->switchTabItem(this->GetCurSel(), this->gTabItemBuffer[this->GetCurSel()].name, this->GetSafeHwnd());

	//展示主窗口
	::ShowWindow(this->gTabItemBuffer[this->GetCurSel()].Hwnd, SW_SHOW);

	*pResult = 0;
}


void CNewTabCtrl::OnTcnSelchanging(NMHDR *pNMHDR, LRESULT *pResult){
	// TODO:  在此添加控件通知处理程序代码

	if (this->gTabItemBuffer.find(this->GetCurSel()) == this->gTabItemBuffer.end()){
		return;
	}

	::ShowWindow(this->gTabItemBuffer[this->GetCurSel()].Hwnd, SW_HIDE);

	*pResult = 0;
}


int   CNewTabCtrl::ReadItemBufferCount(){
	return this->gTabItemBuffer.size();
}

HWND  CNewTabCtrl::ReadItemHwnd(int iIndex){
	if (this->gTabItemBuffer.find(iIndex) == this->gTabItemBuffer.end()){
		return NULL;
	}
	return this->gTabItemBuffer[iIndex].Hwnd;
}

BOOL  CNewTabCtrl::SwitchItem(CString name){
	for (std::map<int, _tagTabCtrlinfo>::iterator i = this->gTabItemBuffer.begin(); i != this->gTabItemBuffer.end(); i++){
		if (FALSE == IsWindow(i->second.Hwnd)){ continue; }

		::ShowWindow(i->second.Hwnd, SW_HIDE);
	}

	//切换 tab
	if (this->gItemIndex.find(name) == this->gItemIndex.end()){
		return FALSE;
	}
	this->SetCurSel(this->gItemIndex[name]);

	//展示下面的子窗口
	if (this->gTabItemBuffer.find(this->gItemIndex[name]) == this->gTabItemBuffer.end()){
		return FALSE;
	}
	//是否已设置委任
	if (NULL != this->gthis_Delegate)
		this->gthis_Delegate->switchTabItem(this->gItemIndex[name], this->gTabItemBuffer[this->gItemIndex[name]].name, this->GetSafeHwnd());

	::ShowWindow(this->gTabItemBuffer[this->gItemIndex[name]].Hwnd, SW_SHOW);
	return TRUE;
}


CString  CNewTabCtrl::ReadSelItemString() {
	int t_index = this->GetCurSel();
	if (this->gTabItemBuffer.find(t_index) == this->gTabItemBuffer.end()) {
		return _T("");
	}
	return this->gTabItemBuffer[t_index].name;
}