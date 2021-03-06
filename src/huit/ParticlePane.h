#pragma once

#include "ParticleForm.h"
// ParticlePane

class ParticlePane : public CDockablePane
{
	DECLARE_DYNAMIC(ParticlePane)
public:
	ParticleForm* pForm;
public:
	ParticlePane();
	virtual ~ParticlePane();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


