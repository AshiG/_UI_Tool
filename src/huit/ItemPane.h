#pragma once

#include "ItemForm.h"
// ItemPane

class ItemPane : public CDockablePane
{
	DECLARE_DYNAMIC(ItemPane)
public:
	ItemForm* pForm;
public:
	ItemPane();
	virtual ~ItemPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


