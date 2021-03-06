#pragma once

#include "HierarchyForm.h"
// HierarchyPane

class HierarchyPane : public CDockablePane
{
	DECLARE_DYNAMIC(HierarchyPane)
public:
	HierarchyForm* pForm;
public:
	HierarchyPane();
	virtual ~HierarchyPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


