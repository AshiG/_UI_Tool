// InfoForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "huit.h"
#include "InfoForm.h"
#include "afxdialogex.h"
#include "Sample.h"

// InfoForm 대화 상자
InfoForm* InfoForm::m_pInstance = nullptr;

IMPLEMENT_DYNAMIC(InfoForm, CFormView)
InfoForm* InfoForm::CreateOne(CWnd* pParent)
{
	InfoForm* pForm = new InfoForm();
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}
InfoForm::InfoForm()
	: CFormView(IDD_InfoForm)
{
	m_pInstance = this;
}
InfoForm::~InfoForm()
{
	m_pInstance = nullptr;
	m_pInstance = NULL;
}

void InfoForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SpriteListBox, m_pSpriteList);
	DDX_Control(pDX, IDC_bRender, m_bRender);
	DDX_Control(pDX, IDC_pfEvnetClick, m_pfClick);
	DDX_Control(pDX, IDC_pfEvnetPress, m_pfPress);
	DDX_Control(pDX, IDC_pfEvnetHover, m_pfHover);
	DDX_Control(pDX, IDC_GameMode, m_GameMode);
	DDX_Control(pDX, IDC_VHType, m_VHType);
	DDX_Control(pDX, IDC_SpriteType, m_SpriteType);
	DDX_Control(pDX, IDC_SpriteLoop, m_pSpriteLoop);
	DDX_Control(pDX, Info_KeyHold, m_KeyHold);
	DDX_Control(pDX, Info_KeyDown, m_KeyDown);
	DDX_Control(pDX, IDC_PassWord, m_PassWord);
	DDX_Control(pDX, Info_Align, m_Align);
	DDX_Control(pDX, IDC_Decrease, m_Decrease);
}


BEGIN_MESSAGE_MAP(InfoForm, CFormView)
	ON_EN_CHANGE(Info_PosZ, &InfoForm::OnEnChangePosz)
	ON_EN_CHANGE(Info_PosX, &InfoForm::OnEnChangePosx)
	ON_EN_CHANGE(Info_PosY, &InfoForm::OnEnChangePosy)
	ON_EN_CHANGE(Info_RotX, &InfoForm::OnEnChangeRotx)
	ON_EN_CHANGE(Info_RotY, &InfoForm::OnEnChangeRoty)
	ON_EN_CHANGE(Info_RotZ, &InfoForm::OnEnChangeRotz)
	ON_EN_CHANGE(Info_SclX, &InfoForm::OnEnChangeSclx)
	ON_EN_CHANGE(Info_SclY, &InfoForm::OnEnChangeScly)
	ON_EN_CHANGE(Info_SclZ, &InfoForm::OnEnChangeSclz)
	ON_BN_CLICKED(IDC_NORMAL_CHANGE, &InfoForm::OnBnClickedNormalChange)
	ON_BN_CLICKED(IDC_HOVER_CHANGE, &InfoForm::OnBnClickedHoverChange)
	ON_BN_CLICKED(IDC_PRESS_CHANGE, &InfoForm::OnBnClickedPressChange)
	ON_BN_CLICKED(IDC_Name_Change, &InfoForm::OnBnClickedNameChange)
	ON_EN_CHANGE(IDC_FIND_txNORMAL, &InfoForm::OnEnChangeFindtxnormal)
	ON_EN_CHANGE(IDC_FIND_txHOVER, &InfoForm::OnEnChangeFindtxhover)
	ON_EN_CHANGE(IDC_FIND_txPRESS, &InfoForm::OnEnChangeFindtxpress)
	ON_EN_CHANGE(IDC_FIND_Sprite, &InfoForm::OnEnChangeFindSprite)
	ON_BN_CLICKED(Info_Sprite_Change, &InfoForm::OnBnClickedSpriteChange)
	ON_BN_CLICKED(Info_Sprite_Clear, &InfoForm::OnBnClickedSpriteClear)
	ON_BN_CLICKED(IDC_SpriteAnim_Change, &InfoForm::OnBnClickedSpriteanimChange)
	ON_BN_CLICKED(IDC_TextString_Change, &InfoForm::OnBnClickedTextstringChange)
	ON_BN_CLICKED(IDC_bRender, &InfoForm::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_NumRender_Change, &InfoForm::OnBnClickedNumrenderChange)
	ON_BN_CLICKED(IDC_EventClick_Change, &InfoForm::OnBnClickedClickChange)
	ON_BN_CLICKED(IDC_EventPress_Change, &InfoForm::OnBnClickedEventpressChange)
	ON_BN_CLICKED(IDC_EventHover_Change, &InfoForm::OnBnClickedEventhoverChange)
	ON_BN_CLICKED(IDC_EventOn, &InfoForm::OnBnClickedEventon)
	ON_BN_CLICKED(IDC_EventOff, &InfoForm::OnBnClickedEventoff)
	ON_BN_CLICKED(IDC_VHType_Change, &InfoForm::OnBnClickedVhtypeChange)
	ON_EN_CHANGE(Info_Value, &InfoForm::OnEnChangeValue)
	ON_BN_CLICKED(IDC_ListColumn_Change, &InfoForm::OnBnClickedListcolumnChange)
	ON_BN_CLICKED(IDC_SpriteType_Change, &InfoForm::OnBnClickedSpritetypeChange)
	ON_BN_CLICKED(IDC_SpriteRowCol_Change, &InfoForm::OnBnClickedSpriterowcolChange)
	ON_BN_CLICKED(IDC_SpritePlay, &InfoForm::OnBnClickedSpriteplay)
	ON_BN_CLICKED(IDC_Key_Change, &InfoForm::OnBnClickedKeyChange)
	ON_EN_CHANGE(ColorX, &InfoForm::OnEnChangeColorx)
	ON_EN_CHANGE(ColorY, &InfoForm::OnEnChangeColory)
	ON_EN_CHANGE(ColorZ, &InfoForm::OnEnChangeColorz)
	ON_EN_CHANGE(ColorW, &InfoForm::OnEnChangeColorw)
	ON_BN_CLICKED(IDC_PassWord, &InfoForm::OnBnClickedPassword)
	ON_BN_CLICKED(IDC_InvenRowCol_Change, &InfoForm::OnBnClickedInvenrowcolChange)
	ON_BN_CLICKED(IDC_AddSlot, &InfoForm::OnBnClickedAddslot)
	ON_EN_CHANGE(IDC_FIND_txITEM, &InfoForm::OnEnChangeFindtxitem)
	ON_BN_CLICKED(IDC_SlotClear, &InfoForm::OnBnClickedSlotclear)
	ON_BN_CLICKED(IDC_SlotDelete, &InfoForm::OnBnClickedSlotdelete)
	ON_BN_CLICKED(IDC_SlotSort, &InfoForm::OnBnClickedSlotsort)
	ON_EN_CHANGE(Info_SubSclX, &InfoForm::OnEnChangeSubsclx)
	ON_EN_CHANGE(Info_SubSclY, &InfoForm::OnEnChangeSubscly)
	ON_EN_CHANGE(Info_SubSclZ, &InfoForm::OnEnChangeSubsclz)
END_MESSAGE_MAP()


// InfoForm 메시지 처리기
// ====================================================================================
// Transform
// ====================================================================================
void InfoForm::OnEnChangePosx()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_PosX, temp);
	Sample::Get()->pCurCtrl->m_vPos.x = (float)_wtof(temp.GetString());
}
void InfoForm::OnEnChangePosy()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_PosY, temp);
	Sample::Get()->pCurCtrl->m_vPos.y = (float)_wtof(temp.GetString());
}
void InfoForm::OnEnChangePosz()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_PosZ, temp);
	Sample::Get()->pCurCtrl->m_vPos.z = (float)_wtof(temp.GetString());
}
void InfoForm::OnEnChangeRotx()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_RotX, temp);
	Sample::Get()->pCurCtrl->m_vRot.x = (float)D3DXToRadian((float)_wtof(temp.GetString()));
}
void InfoForm::OnEnChangeRoty()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_RotY, temp);
	Sample::Get()->pCurCtrl->m_vRot.y = (float)D3DXToRadian((float)_wtof(temp.GetString()));
}
void InfoForm::OnEnChangeRotz()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_RotZ, temp);
	Sample::Get()->pCurCtrl->m_vRot.z = (float)D3DXToRadian((float)_wtof(temp.GetString()));
}
void InfoForm::OnEnChangeSclx()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_SclX, temp);
	Sample::Get()->pCurCtrl->m_vScl.x = (float)_wtof(temp.GetString());
}
void InfoForm::OnEnChangeScly()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_SclY, temp);
	Sample::Get()->pCurCtrl->m_vScl.y = (float)_wtof(temp.GetString());
}
void InfoForm::OnEnChangeSclz()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_SclZ, temp);
	Sample::Get()->pCurCtrl->m_vScl.z = (float)_wtof(temp.GetString());
}
// ====================================================================================
// Name,  ParentName
// ====================================================================================
void InfoForm::OnBnClickedNameChange()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	if (Sample::Get()->pCurCtrl->m_pParent == nullptr) return;
	CString NodeName, ParentName;
	GetDlgItemText(Info_NodeName, NodeName);
	GetDlgItemText(Info_ParentName, ParentName);

	/* 새로운 부모꺼에 넣음 */
	JPanel* pParent = Sample::Get()->pRoot->find_child(ParentName.GetString());
	if (pParent == nullptr)
	{
		AfxMessageBox(L"순회 결과 ParentName이 잘못됫다리");
		return;
	}
	/* 원래 부모에 있던 요소 지움 */
	JPanel* pDelParent = Sample::Get()->pCurCtrl->m_pParent;
	for (auto iC = pDelParent->m_pChildList.begin(); iC != pDelParent->m_pChildList.end(); iC++)
	{
		if ((*iC)->m_NodeName == Sample::Get()->pCurCtrl->m_NodeName)
		{
			pDelParent->m_pChildList.erase(iC);
			break;
		}
	}
	Sample::Get()->pCurCtrl->m_NodeName = NodeName;
	Sample::Get()->pCurCtrl->m_ParentName = ParentName;
	pParent->push_child(Sample::Get()->pCurCtrl);
	//static auto Circuit = [](JPanel* pRoot) // 캡쳐
	Sample::Get()->ParentNameCircuit(pParent);

	Sample::Get()->TreeInitialization(Sample::Get()->pRoot);
	Sample::Get()->UpdateInfo();
}
// ====================================================================================
// Texture
// ====================================================================================
void InfoForm::OnEnChangeFindtxnormal()
{
	CString temp;
	GetDlgItemText(IDC_FIND_txNORMAL, temp);
	wstring txName = UI::JDxHelper::NameDivide(temp);
	SetDlgItemText(Info_txNORMAL, txName.data());
}
void InfoForm::OnEnChangeFindtxhover()
{
	CString temp;
	GetDlgItemText(IDC_FIND_txHOVER, temp);
	wstring txName = UI::JDxHelper::NameDivide(temp);
	SetDlgItemText(Info_txHOVER, txName.data());
}
void InfoForm::OnEnChangeFindtxpress()
{
	CString temp;
	GetDlgItemText(IDC_FIND_txPRESS, temp);
	wstring txName = UI::JDxHelper::NameDivide(temp);
	SetDlgItemText(Info_txPRESS, txName.data());
}
void InfoForm::OnBnClickedNormalChange()
{
	CString temp; 
	GetDlgItemText(IDC_FIND_txNORMAL, temp); // 풀 패스
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	int iTemp = I_TexMgr.Add(DxManager::GetDevice(), temp);
	if (iTemp < 0)
	{
		AfxMessageBox(L"텍스쳐가 없어연");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == BUTTON || pCtrl->m_Type == TEXT || 
		pCtrl->m_Type == LIST || pCtrl->m_Type == EDIT || pCtrl->m_Type == IMAGE)
	{
		Sample::Get()->pCurCtrl->m_pIndexList[UI::txNORMAL] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == CHECK)
	{
		Sample::Get()->pCurCtrl->m_pIndexList[UI::txDISABLE] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == PROGRESS)
	{
		JProgressBar* pSlider = (JProgressBar*)Sample::Get()->pCurCtrl;
		pSlider->m_pBackGround->m_pIndexList[UI::txNORMAL] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)Sample::Get()->pCurCtrl;
		pSlider->m_pSliderBar->m_pIndexList[UI::txNORMAL] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == SLOT)
	{
		JSlot* pSlot = (JSlot*)Sample::Get()->pCurCtrl;
		pSlot->m_pBack->m_pIndexList[UI::txNORMAL] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)Sample::Get()->pCurCtrl;
		pInven->m_pBack->m_pIndexList[UI::txNORMAL] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnBnClickedHoverChange()
{
	CString temp;
	GetDlgItemText(IDC_FIND_txHOVER, temp); // 풀 패스
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	int iTemp = I_TexMgr.Add(DxManager::GetDevice(), temp);
	if (iTemp < 0)
	{
		AfxMessageBox(L"텍스쳐가 없어연");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == BUTTON || pCtrl->m_Type == TEXT)
	{
		Sample::Get()->pCurCtrl->m_pIndexList[UI::txHOVER] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == CHECK)
	{
		Sample::Get()->pCurCtrl->m_pIndexList[UI::txENABLE] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == PROGRESS)
	{
		JProgressBar* pProg = (JProgressBar*)Sample::Get()->pCurCtrl;
		pProg->m_pFrontGround->m_pIndexList[UI::txNORMAL] = iTemp;
		pProg->m_pMiddleGround->m_pIndexList[UI::txNORMAL] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)Sample::Get()->pCurCtrl;
		pSlider->m_pSliderHandle->m_pIndexList[UI::txNORMAL] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)Sample::Get()->pCurCtrl;
		pInven->m_strSlotBack = I_TexMgr.GetPtr(iTemp)->m_szName;
		for(auto& pItem : pInven->m_pItemList)
			pItem->m_pBack->m_pIndexList[UI::txNORMAL] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnBnClickedPressChange()
{
	CString temp;
	GetDlgItemText(IDC_FIND_txPRESS, temp); // 풀 패스
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	int iTemp = I_TexMgr.Add(DxManager::GetDevice(), temp);
	if (iTemp < 0)
	{
		AfxMessageBox(L"텍스쳐가 없어연");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == BUTTON || pCtrl->m_Type == TEXT)
	{
		Sample::Get()->pCurCtrl->m_pIndexList[UI::txPRESS] = iTemp;
		Sample::Get()->UpdateInfo();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnEnChangeFindSprite()
{
	CString temp;
	GetDlgItemText(IDC_FIND_Sprite, temp); // 풀 패스
	m_pSpriteList.AddString(UI::JDxHelper::NameDivide(temp));
	m_pSpritePath.push_back(temp.GetString());
}
void InfoForm::OnBnClickedSpriteChange()
{
	CString temp;
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}

	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SPRITE)
	{
		JSpriteCtrl* pSprite = (JSpriteCtrl*)Sample::Get()->pCurCtrl;
		pSprite->m_pIndexList.clear();
		pSprite->m_iCurrentIndex = 0;
		for (int iIndex = 0; iIndex < m_pSpritePath.size(); iIndex++)
		{
			int iTemp = I_TexMgr.Add(DxManager::GetDevice(), m_pSpritePath[iIndex].data());
			if (iTemp < 0)
			{
				AfxMessageBox(L"SpriteTexture 읽는 도중 에러뜸...");
				return;
			}
			pSprite->m_pIndexList.push_back(iTemp);
		}
		pSprite->m_iNumTexture = (int)pSprite->m_pIndexList.size();
		pSprite->m_fAnimTime = pSprite->m_fAnimTime;
		pSprite->m_fChangeTime = pSprite->m_fAnimTime / pSprite->m_iNumTexture;
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == PARTICLE)
	{
		JParticleSystem* pParticle = (JParticleSystem*)Sample::Get()->pCurCtrl;
		pParticle->m_pSprite->m_pIndexList.clear();
		pParticle->m_pSprite->m_iCurrentIndex = 0;
		for (int iIndex = 0; iIndex < m_pSpritePath.size(); iIndex++)
		{
			int iTemp = I_TexMgr.Add(DxManager::GetDevice(), m_pSpritePath[iIndex].data());
			if (iTemp < 0)
			{
				AfxMessageBox(L"ParticleTexture 읽는 도중 에러뜸...");
				return;
			}
			pParticle->m_pSprite->m_pIndexList.push_back(iTemp);
		}
		pParticle->m_pSprite->m_iNumTexture = (int)pParticle->m_pSprite->m_pIndexList.size();
		pParticle->m_pSprite->m_fAnimTime = pParticle->m_pSprite->m_fAnimTime;
		pParticle->m_pSprite->m_fChangeTime = pParticle->m_pSprite->m_fAnimTime / pParticle->m_pSprite->m_iNumTexture;
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnBnClickedSpriteClear()
{
	m_pSpriteList.ResetContent();
	m_pSpritePath.clear();
}
void InfoForm::OnBnClickedSpriteanimChange()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	CString temp;
	GetDlgItemText(Info_SpriteAnimTime, temp);
	if (pCtrl->m_Type == SPRITE)
	{
		JSpriteCtrl* pSprite = (JSpriteCtrl*)Sample::Get()->pCurCtrl;
		pSprite->SetAnimTime((float)_wtof(temp.GetString()));
		return;
	}
	else if (pCtrl->m_Type == PARTICLE)
	{
		JParticleSystem* pParticle = (JParticleSystem*)Sample::Get()->pCurCtrl;
		pParticle->m_pSprite->SetAnimTime((float)_wtof(temp.GetString()));
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
	Sample::Get()->UpdateInfo();
}
void InfoForm::OnBnClickedTextstringChange()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	CString temp;
	if (pCtrl->m_Type == TEXT)
	{
		JTextCtrl* pText = (JTextCtrl*)Sample::Get()->pCurCtrl;
		GetDlgItemText(Info_TextString, temp);
		pText->m_Text = temp;
		GetDlgItemText(Info_TextSize, temp);
		pText->m_fSize = (float)_wtof(temp.GetString());
		GetDlgItemText(Info_Align, temp);
		pText->m_Align = Sample::Get()->FindAlign(temp.GetString());
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == LIST)
	{
		JListCtrl* pList = (JListCtrl*)Sample::Get()->pCurCtrl;
		GetDlgItemText(Info_TextString, temp);
		pList->push_string(temp.GetString());
		GetDlgItemText(Info_TextSize, temp);
		pList->m_fSize = (float)_wtof(temp.GetString());
		GetDlgItemText(Info_Align, temp);
		pList->m_Align = Sample::Get()->FindAlign(temp.GetString());
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == EDIT)
	{
		JEditCtrl* pEdit = (JEditCtrl*)Sample::Get()->pCurCtrl;
		GetDlgItemText(Info_TextSize, temp);
		pEdit->m_fSize = (float)_wtof(temp.GetString());
		GetDlgItemText(Info_MaxLength, temp);
		pEdit->m_iMaxLength = (float)_wtof(temp.GetString());		
		GetDlgItemText(Info_Align, temp);
		pEdit->m_Align = Sample::Get()->FindAlign(temp.GetString());
		Sample::Get()->UpdateInfo();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
// bRender
void InfoForm::OnBnClickedCheck1()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	Sample::Get()->pCurCtrl->m_bRender = m_bRender.GetCheck();
}
// NumRender
void InfoForm::OnBnClickedNumrenderChange()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_NumRender, temp);
	Sample::Get()->pCurCtrl->m_iNumRender = (int)_wtoi(temp.GetString());

	Sample::Get()->SortCircuit(Sample::Get()->pRoot);
	Sample::Get()->TreeInitialization(Sample::Get()->pRoot);
	Sample::Get()->UpdateInfo();
}
// ====================================================================================
// Event
// ====================================================================================
void InfoForm::OnBnClickedClickChange()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString pf, vp;
	GetDlgItemText(Info_vpEventClick, vp);
	GetDlgItemText(IDC_pfEvnetClick, pf);

	if (vp != L"" && Sample::Get()->pRoot->find_child(vp.GetString()) == nullptr)
	{
		AfxMessageBox(L"순회 결과 Ctrl이 없어요.");
		return;
	}

	JPanel* pPanel = Sample::Get()->pCurCtrl;
	pPanel->m_pfClick = Sample::Get()->FindPointerFunc(pf.GetString());
	pPanel->m_vpClick = vp.GetString();
	Sample::Get()->UpdateInfo();
}
void InfoForm::OnBnClickedEventpressChange()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString pf, vp;
	GetDlgItemText(Info_vpEventPress, vp);
	GetDlgItemText(IDC_pfEvnetPress, pf);

	if (vp != L"" && Sample::Get()->pRoot->find_child(vp.GetString()) == nullptr)
	{
		AfxMessageBox(L"순회 결과 Ctrl이 없어요.");
		return;
	}

	JPanel* pPanel = Sample::Get()->pCurCtrl;
	pPanel->m_pfPress = Sample::Get()->FindPointerFunc(pf.GetString());
	pPanel->m_vpPress = vp.GetString();
	Sample::Get()->UpdateInfo();
}
void InfoForm::OnBnClickedEventhoverChange()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString pf, vp;
	GetDlgItemText(Info_vpEventHover, vp);
	GetDlgItemText(IDC_pfEvnetHover, pf);

	if (vp != L"" && Sample::Get()->pRoot->find_child(vp.GetString()) == nullptr)
	{
		AfxMessageBox(L"순회 결과 Ctrl이 없어요.");
		return;
	}

	JPanel* pPanel = Sample::Get()->pCurCtrl;
	pPanel->m_pfHover = Sample::Get()->FindPointerFunc(pf.GetString());
	pPanel->m_vpHover = vp.GetString();
	Sample::Get()->UpdateInfo();
}
// Event On Off
void InfoForm::OnBnClickedEventon()
{
	Sample::Get()->m_Write.RunWrite(Sample::Get()->pRoot, L"temp");

	Sample::Get()->pCurCtrl = nullptr;
	Sample::Get()->pRoot->m_pChildList.clear();
	Sample::Get()->par.FileLoad(DxManager::GetDevice(), L"temp", *Sample::Get()->pRoot);
	Sample::Get()->TreeInitialization(Sample::Get()->pRoot);
	Sample::Get()->EventCircuit(Sample::Get()->pRoot, true);
	Sample::Get()->IntroEvent();
	Sample::Get()->LobbyEvent();
	Sample::Get()->InGameEvent();
	Sample::Get()->LoadingEvent();
}
void InfoForm::OnBnClickedEventoff()
{
	Sample::Get()->EventCircuit(Sample::Get()->pRoot, false);
}
// VHType
void InfoForm::OnBnClickedVhtypeChange()
{
	CString strVHType, fValue;
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SLIDER)
	{
		GetDlgItemText(IDC_VHType, strVHType);
		GetDlgItemText(Info_Value, fValue);
		JSliderCtrl* pSlider = (JSliderCtrl*)Sample::Get()->pCurCtrl;
		pSlider->m_VHType = Sample::Get()->FindVHType(strVHType.GetString());
		*pSlider->m_fValue = (float)_wtof(fValue.GetString());
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == PROGRESS)
	{
		GetDlgItemText(IDC_VHType, strVHType);
		JProgressBar* pProg = (JProgressBar*)Sample::Get()->pCurCtrl;
		pProg->m_VHType = Sample::Get()->FindVHType(strVHType.GetString());
		pProg->m_fCurValue = (float)_wtof(fValue.GetString());
		pProg->m_bDecrease = m_Decrease.GetCheck();
		Sample::Get()->UpdateInfo();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
// change value
void InfoForm::OnEnChangeValue()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == PROGRESS)
	{
		GetDlgItemText(Info_Value, temp);
		JProgressBar* pProg = (JProgressBar*)Sample::Get()->pCurCtrl;
		//pProg->m_fTemp = (float)_wtof(temp.GetString());
		//if (pProg->m_fTemp <= 0) pProg->m_fTemp = 0.0f;
		//if (pProg->m_fTemp >= 1) pProg->m_fTemp = 1.0f;
		*pProg->m_fCur = (float)_wtof(temp.GetString());
		if (*pProg->m_fCur <= 0) *pProg->m_fCur = 0.0f;
		if (*pProg->m_fCur >= 1) *pProg->m_fCur = 1.0f;
		return;
	}
}
void InfoForm::OnBnClickedListcolumnChange()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	CString temp;
	if (pCtrl->m_Type == LIST)
	{
		JListCtrl* pList = (JListCtrl*)Sample::Get()->pCurCtrl;
		GetDlgItemText(Info_ListColumn, temp);
		pList->SetColumn((int)_wtoi(temp.GetString()));
		Sample::Get()->UpdateInfo();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnBnClickedSpritetypeChange()
{
	CString SpriteType;
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SPRITE)
	{
		GetDlgItemText(IDC_SpriteType, SpriteType);
		JSpriteCtrl* pSprite = (JSpriteCtrl*)Sample::Get()->pCurCtrl;
		pSprite->m_SpriteType = Sample::Get()->FindSpriteType(SpriteType.GetString());
		pSprite->m_bLoop = m_pSpriteLoop.GetCheck();
		if (pSprite->m_SpriteType == TEXSPRITE)
		{
			pSprite->m_iNumTexture = (int)pSprite->m_pIndexList.size();
		}
		else if (pSprite->m_SpriteType == UVSPRITE)
		{
			pSprite->m_iNumTexture = 0;
		}
		Sample::Get()->UpdateInfo();
		return;
	}
	else if (pCtrl->m_Type == PARTICLE)
	{
		GetDlgItemText(IDC_SpriteType, SpriteType);
		JParticleSystem* pParticle = (JParticleSystem*)Sample::Get()->pCurCtrl;
		pParticle->m_pSprite->m_SpriteType = Sample::Get()->FindSpriteType(SpriteType.GetString());
		pParticle->m_pSprite->m_bLoop = m_pSpriteLoop.GetCheck();
		if (pParticle->m_pSprite->m_SpriteType == TEXSPRITE)
		{
			pParticle->m_pSprite->m_iNumTexture = (int)pParticle->m_pSprite->m_pIndexList.size();
		}
		else if (pParticle->m_pSprite->m_SpriteType == UVSPRITE)
		{
			pParticle->m_pSprite->m_iNumTexture = 0;
		}
		Sample::Get()->UpdateInfo();
		return;
	}
}
void InfoForm::OnBnClickedSpriterowcolChange()
{
	CString CRow, CCol;
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = (JPanel*)Sample::Get()->pCurCtrl;
	GetDlgItemText(Info_SpriteRows, CRow);
	GetDlgItemText(Info_SpriteCols, CCol);
	if (pCtrl->m_Type == SPRITE)
	{
		JSpriteCtrl* pSprite = (JSpriteCtrl*)pCtrl;
		if (pSprite->m_SpriteType == TEXSPRITE)
		{
			AfxMessageBox(L"SpriteType이 TextureSprite 입니다.");
		}
		else if(pSprite->m_SpriteType == UVSPRITE)
		{
			pSprite->SetUV((int)_wtoi(CRow.GetString()), (int)_wtoi(CCol.GetString()));
		}
	}
	else if (pCtrl->m_Type == PARTICLE)
	{
		JParticleSystem* pParticle = (JParticleSystem*)pCtrl; 
		if (pParticle->m_pSprite->m_SpriteType == TEXSPRITE)
		{
			AfxMessageBox(L"SpriteType이 TextureSprite 입니다.");
		}
		else if (pParticle->m_pSprite->m_SpriteType == UVSPRITE)
		{
			pParticle->m_pSprite->SetUV((int)_wtoi(CRow.GetString()), (int)_wtoi(CCol.GetString()));
		}
	}
}
void InfoForm::OnBnClickedSpriteplay()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = (JPanel*)Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SPRITE)
	{
		JSpriteCtrl* pSprite = (JSpriteCtrl*)pCtrl;
		pSprite->m_bPlay = true;
		return;
	}
	else if (pCtrl->m_Type == PARTICLE)
	{
		JParticleSystem* pParticle = (JParticleSystem*)pCtrl;
		pParticle->m_pSprite->m_bPlay = true;
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 안써욧!");
}
void InfoForm::OnBnClickedKeyChange()
{
	CString Down, Hold;
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	GetDlgItemText(Info_KeyDown, Down);
	GetDlgItemText(Info_KeyHold, Hold);
	wstring down = Down.GetString();
	wstring hold = Hold.GetString();
	JPanel* pCtrl = (JPanel*)Sample::Get()->pCurCtrl;
	// down ===========================================================
	if (down == L"")
	{
		pCtrl->m_pKeyDown = VK_F24;
	}
	else if (down == L"TAB")
	{
		pCtrl->m_pKeyDown = VK_TAB;
	}
	else if (down == L"SPACE")
	{
		pCtrl->m_pKeyDown = VK_SPACE;
	}
	else if (down == L"ENTER")
	{
		pCtrl->m_pKeyDown = VK_RETURN;
	}
	else if (down == L"ESC")
	{
		pCtrl->m_pKeyDown = VK_ESCAPE;
	}
	else
	{
		pCtrl->m_pKeyDown = down.front();
	}

	// hold ===========================================================
	if (hold == L"")
	{
		pCtrl->m_pKeyHold = VK_F24;
	}
	else if (hold == L"TAB")
	{
		pCtrl->m_pKeyHold = VK_TAB;
	}
	else if (hold == L"SPACE")
	{
		pCtrl->m_pKeyHold = VK_SPACE;
	}
	else if (hold == L"ENTER")
	{
		pCtrl->m_pKeyHold = VK_RETURN;
	}
	else if (hold == L"ESC")
	{
		pCtrl->m_pKeyHold = VK_ESCAPE;
	}
	else
	{
		pCtrl->m_pKeyHold = hold.front();
	}
}
void InfoForm::OnEnChangeColorx()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(ColorX, temp);
	JPanel* pCur = Sample::Get()->pCurCtrl;
	if (pCur->m_Type == PARTICLE || pCur->m_Type == PANEL)
	{
		return;
	}
	else if (pCur->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)pCur;
		pSlider->m_pSliderBar->m_pShape->m_cbData.vColor.x = (float)_wtof(temp.GetString());
		pSlider->m_pSliderHandle->m_pShape->m_cbData.vColor.x = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == PROGRESS)
	{
		JProgressBar* pProg = (JProgressBar*)pCur;
		pProg->m_pBackGround->m_pShape->m_cbData.vColor.x = (float)_wtof(temp.GetString());
		pProg->m_pFrontGround->m_pShape->m_cbData.vColor.x = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == SLOT)
	{
		JSlot* pSlot = (JSlot*)pCur;
		pSlot->m_pBack->m_pShape->m_cbData.vColor.x = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)pCur;
		pInven->m_pBack->m_pShape->m_cbData.vColor.x = (float)_wtof(temp.GetString());
		return;
	}
	else
	{
		Sample::Get()->pCurCtrl->m_pShape->m_cbData.vColor.x = (float)_wtof(temp.GetString());
		return;
	}
}
void InfoForm::OnEnChangeColory()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(ColorY, temp);
	JPanel* pCur = Sample::Get()->pCurCtrl;
	if (pCur->m_Type == PARTICLE || pCur->m_Type == PANEL)
	{
		return;
	}
	else if (pCur->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)pCur;
		pSlider->m_pSliderBar->m_pShape->m_cbData.vColor.y = (float)_wtof(temp.GetString());
		pSlider->m_pSliderHandle->m_pShape->m_cbData.vColor.y = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == PROGRESS)
	{
		JProgressBar* pProg = (JProgressBar*)pCur;
		pProg->m_pBackGround->m_pShape->m_cbData.vColor.y = (float)_wtof(temp.GetString());
		pProg->m_pFrontGround->m_pShape->m_cbData.vColor.y = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == SLOT)
	{
		JSlot* pSlot = (JSlot*)pCur;
		pSlot->m_pBack->m_pShape->m_cbData.vColor.y = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)pCur;
		pInven->m_pBack->m_pShape->m_cbData.vColor.y = (float)_wtof(temp.GetString());
		return;
	}
	else
	{
		Sample::Get()->pCurCtrl->m_pShape->m_cbData.vColor.y = (float)_wtof(temp.GetString());
		return;
	}
}
void InfoForm::OnEnChangeColorz()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(ColorZ, temp);
	JPanel* pCur = Sample::Get()->pCurCtrl;
	if (pCur->m_Type == PARTICLE || pCur->m_Type == PANEL)
	{
		return;
	}
	else if (pCur->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)pCur;
		pSlider->m_pSliderBar->m_pShape->m_cbData.vColor.z = (float)_wtof(temp.GetString());
		pSlider->m_pSliderHandle->m_pShape->m_cbData.vColor.z = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == PROGRESS)
	{
		JProgressBar* pProg = (JProgressBar*)pCur;
		pProg->m_pBackGround->m_pShape->m_cbData.vColor.z = (float)_wtof(temp.GetString());
		pProg->m_pFrontGround->m_pShape->m_cbData.vColor.z = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == SLOT)
	{
		JSlot* pSlot = (JSlot*)pCur;
		pSlot->m_pBack->m_pShape->m_cbData.vColor.z = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)pCur;
		pInven->m_pBack->m_pShape->m_cbData.vColor.z = (float)_wtof(temp.GetString());
		return;
	}
	else
	{
		Sample::Get()->pCurCtrl->m_pShape->m_cbData.vColor.z = (float)_wtof(temp.GetString());
		return;
	}
}
void InfoForm::OnEnChangeColorw()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(ColorW, temp); 
	JPanel* pCur = Sample::Get()->pCurCtrl;
	if (pCur->m_Type == PARTICLE || pCur->m_Type == PANEL)
	{
		return;
	}
	else if (pCur->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)pCur;
		pSlider->m_pSliderBar->m_pShape->m_cbData.vColor.w = (float)_wtof(temp.GetString());
		pSlider->m_pSliderHandle->m_pShape->m_cbData.vColor.w = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == PROGRESS)
	{
		JProgressBar* pProg = (JProgressBar*)pCur;
		pProg->m_pBackGround->m_pShape->m_cbData.vColor.w = (float)_wtof(temp.GetString());
		pProg->m_pFrontGround->m_pShape->m_cbData.vColor.w = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == SLOT)
	{
		JSlot* pSlot = (JSlot*)pCur;
		pSlot->m_pBack->m_pShape->m_cbData.vColor.w = (float)_wtof(temp.GetString());
		return;
	}
	else if (pCur->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)pCur;
		pInven->m_pBack->m_pShape->m_cbData.vColor.w = (float)_wtof(temp.GetString());
		return;
	}
	else
	{
		Sample::Get()->pCurCtrl->m_pShape->m_cbData.vColor.w = (float)_wtof(temp.GetString());
		return;
	}
}
void InfoForm::OnBnClickedPassword()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(ColorW, temp);
	JPanel* pCur = Sample::Get()->pCurCtrl;
	if (pCur->m_Type == EDIT)
	{
		JEditCtrl* pEdit = (JEditCtrl*)pCur;
		pEdit->m_bPrivate = m_PassWord.GetCheck();
	}
}
void InfoForm::OnBnClickedInvenrowcolChange()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	CString Row, Col;
	if (pCtrl->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)Sample::Get()->pCurCtrl;
		GetDlgItemText(Info_InvenRow, Row);
		GetDlgItemText(Info_InvenCol, Col);
		wstring txName = pInven->m_pItemList[0]->m_pBack->m_pTexture->m_szFullPath;
		pInven->CreateItemSlot(DxManager::GetDevice(), (int)_wtoi(Row.GetString()), (int)_wtoi(Col.GetString()), txName.data());
		Sample::Get()->UpdateInfo();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnBnClickedAddslot()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	CString temp;
	GetDlgItemText(IDC_FIND_txITEM, temp); // 풀 패스
	int iKey = I_TexMgr.Add(DxManager::GetDevice(), temp);
	if (iKey < 0)
	{
		AfxMessageBox(L"텍스쳐가 없어연");
		return;
	}

	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SLOT)
	{
		JSlot* pSlot = (JSlot*)Sample::Get()->pCurCtrl;
		if (pSlot->m_bEmpty)
		{
			pSlot->m_pItem->m_pIndexList[txNORMAL] = iKey;
			pSlot->m_bEmpty = false;
		}
		else
		{
			pSlot->m_pItem->m_pIndexList[txNORMAL] = iKey;
		}
		return;
	}
	else if (pCtrl->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)Sample::Get()->pCurCtrl;
		//pInven->m_iNumItem += 1;
		for (auto& pItem : pInven->m_pItemList)
		{
			if (pItem->m_bEmpty)
			{
				pItem->m_pItem->m_pIndexList[txNORMAL] = iKey;
				pItem->m_bEmpty = false;
				break;
			}
		}
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnEnChangeFindtxitem()
{
	CString temp;
	GetDlgItemText(IDC_FIND_txITEM, temp);
	wstring txName = UI::JDxHelper::NameDivide(temp);
	SetDlgItemText(Info_txITEM, txName.data());
}
void InfoForm::OnBnClickedSlotclear()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SLOT)
	{
		JSlot* pSlot = (JSlot*)pCtrl;
		pSlot->DelItem();
		return;
	}
	else if (pCtrl->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)pCtrl;
		pInven->ClearItem();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnBnClickedSlotdelete()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SLOT)
	{
		JSlot* pSlot = (JSlot*)pCtrl;
		pSlot->DelItem();
		return;
	}
	else if (pCtrl->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)pCtrl;
		pInven->DelItem();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
void InfoForm::OnBnClickedSlotsort()
{
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == INVENTORY)
	{
		JInventory* pInven = (JInventory*)pCtrl;
		pInven->SortItem();
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}


void InfoForm::OnEnChangeSubsclx()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_SubSclX, temp);
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if(pCtrl->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)pCtrl;
		pSlider->m_pSliderHandle->m_vScl.x = (float)_wtof(temp.GetString());
	}
	else if (pCtrl->m_Type == PROGRESS)
	{
		JProgressBar* pProg = (JProgressBar*)pCtrl;
		pProg->m_pFrontGround->m_vScl.x = (float)_wtof(temp.GetString());
	}
}
void InfoForm::OnEnChangeSubscly()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_SubSclY, temp);
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)pCtrl;
		pSlider->m_pSliderHandle->m_vScl.y = (float)_wtof(temp.GetString());
	}
	else if (pCtrl->m_Type == PROGRESS)
	{
		JProgressBar* pProg = (JProgressBar*)pCtrl;
		pProg->m_pFrontGround->m_vScl.y = (float)_wtof(temp.GetString());
	}
}
void InfoForm::OnEnChangeSubsclz()
{
	if (Sample::Get()->pCurCtrl == nullptr) return;
	CString temp;
	GetDlgItemText(Info_SubSclZ, temp);
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == SLIDER)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)pCtrl;
		pSlider->m_pSliderHandle->m_vScl.z = (float)_wtof(temp.GetString());
	}
	else if (pCtrl->m_Type == PROGRESS)
	{
		JProgressBar* pProg = (JProgressBar*)pCtrl;
		pProg->m_pFrontGround->m_vScl.z = (float)_wtof(temp.GetString());
	}
}
