// CreateForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "huit.h"
#include "CreateForm.h"
#include "afxdialogex.h"

#include "InfoForm.h"
#include "Sample.h"
// CreateForm 대화 상자
CreateForm* CreateForm::m_pInstance = nullptr;

IMPLEMENT_DYNAMIC(CreateForm, CFormView)
CreateForm* CreateForm::CreateOne(CWnd* pParent)
{
	CreateForm* pForm = new CreateForm();
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}
CreateForm::CreateForm()
	: CFormView(IDD_CreateForm)
{
	m_pInstance = this;
}

CreateForm::~CreateForm()
{
	m_pInstance = nullptr;
	m_pInstance = NULL;
}

void CreateForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CreateForm, CFormView)
	ON_BN_CLICKED(IDD_CButton, &CreateForm::OnBnClickedCbutton)
	ON_BN_CLICKED(IDD_CCheck, &CreateForm::OnBnClickedCcheck)
	ON_BN_CLICKED(IDD_CProgress, &CreateForm::OnBnClickedCprogress)
	ON_BN_CLICKED(IDD_CSlider, &CreateForm::OnBnClickedCslider)
	ON_BN_CLICKED(IDD_CSprite, &CreateForm::OnBnClickedCsprite)
	ON_BN_CLICKED(IDD_CText, &CreateForm::OnBnClickedCtext)
	ON_BN_CLICKED(IDD_CParticle, &CreateForm::OnBnClickedCparticle)
	ON_BN_CLICKED(IDD_CPanel, &CreateForm::OnBnClickedCpanel)
	ON_BN_CLICKED(IDD_Save, &CreateForm::OnBnClickedSave)
	ON_BN_CLICKED(IDD_Load, &CreateForm::OnBnClickedLoad)
	ON_BN_CLICKED(IDD_CTRL_DELETE, &CreateForm::OnBnClickedCtrlDelete)
	ON_BN_CLICKED(IDD_CList, &CreateForm::OnBnClickedClist)
	ON_BN_CLICKED(IDD_Edit, &CreateForm::OnBnClickedEdit)
	ON_BN_CLICKED(IDD_Image, &CreateForm::OnBnClickedImage)
	ON_BN_CLICKED(IDD_CSlot, &CreateForm::OnBnClickedCslot)
	ON_BN_CLICKED(IDD_CInventory, &CreateForm::OnBnClickedCinventory)
END_MESSAGE_MAP()


// CreateForm 메시지 처리기
void CreateForm::OnBnClickedCbutton()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateButton(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
// =================================================================================================
// Check
// =================================================================================================
void CreateForm::OnBnClickedCcheck()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateCheck(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
// =================================================================================================
// Progress
// =================================================================================================
void CreateForm::OnBnClickedCprogress()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateProgress(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
// =================================================================================================
// Slider
// =================================================================================================
void CreateForm::OnBnClickedCslider()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateSlider(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
// =================================================================================================
// Sprite
// =================================================================================================
void CreateForm::OnBnClickedCsprite()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateSprite(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
// =================================================================================================
// Text
// =================================================================================================
void CreateForm::OnBnClickedCtext()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateText(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
// =================================================================================================
// Particle
// =================================================================================================
void CreateForm::OnBnClickedCparticle()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateParticle(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
// =================================================================================================
// Panel
// =================================================================================================
void CreateForm::OnBnClickedCpanel()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreatePanel(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
void CreateForm::OnBnClickedClist()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateList(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
void CreateForm::OnBnClickedEdit()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateEdit(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
void CreateForm::OnBnClickedImage()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateImage(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
// =================================================================================================
// Save / Load
// =================================================================================================
void CreateForm::OnBnClickedSave()
{
	CString SaveName;
	GetDlgItemText(IDC_SaveFileName, SaveName);
	Sample::Get()->SaveData(SaveName.GetString());
}
void CreateForm::OnBnClickedLoad()
{
	CString LoadName;
	GetDlgItemText(IDC_LoadFileName, LoadName);
	Sample::Get()->LoadData(LoadName.GetString());
}
// Delete
void CreateForm::OnBnClickedCtrlDelete()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pDelCtrl = Sample::Get()->pRoot->find_child(Sample::Get()->pCurCtrl->m_NodeName);
	if (pDelCtrl == nullptr || pDelCtrl == Sample::Get()->pRoot)
	{
		AfxMessageBox(L"지울 컨트롤이 없네염.");
		return;
	}
	JPanel* pDelParent = pDelCtrl->m_pParent;
	for (auto iC = pDelParent->m_pChildList.begin(); iC != pDelParent->m_pChildList.end(); iC++)
	{
		if ((*iC)->m_NodeName == pDelCtrl->m_NodeName)
		{
			pDelParent->m_pChildList.erase(iC);
			break;
		}
	}
	Sample::Get()->TreeInitialization(Sample::Get()->pRoot);
	Sample::Get()->UpdateInfo();
}
void CreateForm::OnBnClickedCslot()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateSlot(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}
void CreateForm::OnBnClickedCinventory()
{
	CString NodeName, ParentName;
	GetDlgItemText(IDC_CNodeName, NodeName);
	GetDlgItemText(IDC_CParentName, ParentName);
	if (NodeName == L"")
	{
		AfxMessageBox(L"NodeName은 필수라구요");
		return;
	}
	if (Sample::Get()->pRoot->find_child(NodeName.GetString()) != nullptr)
	{
		AfxMessageBox(L"이미 있는 NodeName 이군요. 유감임.");
		SetDlgItemText(IDC_CNodeName, L"");
		SetDlgItemText(IDC_CParentName, L"");
		return;
	}
	Sample::Get()->CreateInventory(NodeName.GetString(), ParentName.GetString());
	SetDlgItemText(IDC_CNodeName, L"");
	SetDlgItemText(IDC_CParentName, L"");
}

