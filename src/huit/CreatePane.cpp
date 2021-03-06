// CreatePane.cpp: 구현 파일
//

#include "stdafx.h"
#include "huit.h"
#include "CreatePane.h"


// CreatePane

IMPLEMENT_DYNAMIC(CreatePane, CDockablePane)

CreatePane::CreatePane()
{

}

CreatePane::~CreatePane()
{
}


BEGIN_MESSAGE_MAP(CreatePane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CreatePane 메시지 처리기




void CreatePane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (pForm)
	{
		pForm->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
}


int CreatePane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
}


int CreatePane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	this->pForm = CreateForm::CreateOne(this);
	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return 0;
}
