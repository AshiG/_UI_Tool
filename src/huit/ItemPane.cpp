// ItemPane.cpp: 구현 파일
//

#include "stdafx.h"
#include "huit.h"
#include "ItemPane.h"


// ItemPane

IMPLEMENT_DYNAMIC(ItemPane, CDockablePane)

ItemPane::ItemPane()
{

}

ItemPane::~ItemPane()
{
}


BEGIN_MESSAGE_MAP(ItemPane, CDockablePane)
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// ItemPane 메시지 처리기




void ItemPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	if (pForm)
	{
		pForm->SetWindowPos(NULL, 0, 0, cx, cy, SWP_NOZORDER);
	}
}


int ItemPane::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CFrameWnd* pParentFrame = GetParentFrame();
	if (pParentFrame == pDesktopWnd || pDesktopWnd->IsChild(pParentFrame))
	{
		return CDockablePane::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return MA_NOACTIVATE;
}


int ItemPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	this->pForm = ItemForm::CreateOne(this);
	return 0;
}
