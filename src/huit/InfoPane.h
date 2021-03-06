#pragma once
#include "InfoForm.h"

// InfoPane

class InfoPane : public CDockablePane
{
	DECLARE_DYNAMIC(InfoPane)
public:
	InfoForm* pForm;
public:
	InfoPane();
	virtual ~InfoPane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


