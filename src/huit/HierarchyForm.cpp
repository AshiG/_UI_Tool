// HierarchyForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "huit.h"
#include "HierarchyForm.h"
#include "afxdialogex.h"


// HierarchyForm 대화 상자
HierarchyForm* HierarchyForm::m_pInstance = nullptr;

IMPLEMENT_DYNAMIC(HierarchyForm, CFormView)

HierarchyForm* HierarchyForm::CreateOne(CWnd* pParent)
{
	HierarchyForm* pForm = new HierarchyForm();
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}
HierarchyForm::HierarchyForm()
	: CFormView(IDD_HierarchyForm)
{
	m_pInstance = this;
}

HierarchyForm::~HierarchyForm()
{
	m_pInstance = nullptr;
	m_pInstance = NULL;
}

void HierarchyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HierarchyTree, m_HierarchyTree);
}


BEGIN_MESSAGE_MAP(HierarchyForm, CFormView)
	ON_NOTIFY(NM_DBLCLK, IDC_HierarchyTree, &HierarchyForm::OnNMDblclkHierarchytree)
	ON_NOTIFY(NM_CLICK, IDC_HierarchyTree, &HierarchyForm::OnNMClickHierarchytree)
END_MESSAGE_MAP()


// HierarchyForm 메시지 처리기


void HierarchyForm::OnNMDblclkHierarchytree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint p;
	GetCursorPos(&p);
	UINT flag;
	m_HierarchyTree.ScreenToClient(&p);
	HTREEITEM hItem = m_HierarchyTree.HitTest(p, &flag);
	for (int iChild = 0; iChild < Sample::Get()->pRoot->m_pChildList.size(); iChild++)
	{
		//if (m_HierarchyTree.GetItemText(hItem) == Sample::Get()->pRoot->m_pChildList[iChild]->m_NodeName.data())
		//{
			Sample::Get()->pCurCtrl = Sample::Get()->pRoot->find_child(m_HierarchyTree.GetItemText(hItem).GetString());
			//Sample::Get()->pCurCtrl = Sample::Get()->pRoot->m_pChildList[iChild];
			Sample::Get()->UpdateInfo();
		//}
	}
	// =======================================================
	*pResult = 0;
}


void HierarchyForm::OnNMClickHierarchytree(NMHDR *pNMHDR, LRESULT *pResult)
{
	CPoint p;
	GetCursorPos(&p);
	UINT flag;
	m_HierarchyTree.ScreenToClient(&p);
	HTREEITEM hItem = m_HierarchyTree.HitTest(p, &flag);
	for (int iChild = 0; iChild < Sample::Get()->pRoot->m_pChildList.size(); iChild++)
	{
		Sample::Get()->pCurCtrl = Sample::Get()->pRoot->find_child(m_HierarchyTree.GetItemText(hItem).GetString());
		Sample::Get()->UpdateInfo();
	}
	*pResult = 0;
}
