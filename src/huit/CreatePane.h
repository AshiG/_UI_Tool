#pragma once
#include "CreateForm.h"

// CreatePane

class CreatePane : public CDockablePane
{
	DECLARE_DYNAMIC(CreatePane)
public:
	CreateForm* pForm;
public:
	CreatePane();
	virtual ~CreatePane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


