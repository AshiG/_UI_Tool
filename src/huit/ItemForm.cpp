// ItemForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "huit.h"
#include "ItemForm.h"
#include "afxdialogex.h"


// ItemForm 대화 상자

ItemForm* ItemForm::m_pInstance = nullptr;

IMPLEMENT_DYNAMIC(ItemForm, CFormView)
ItemForm* ItemForm::CreateOne(CWnd* pParent)
{
	ItemForm* pForm = new ItemForm();
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}

ItemForm::ItemForm()
	: CFormView(IDD_ItemForm)
{

}

ItemForm::~ItemForm()
{

}

void ItemForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ItemForm, CFormView)
END_MESSAGE_MAP()


// ItemForm 메시지 처리기
