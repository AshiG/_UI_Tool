#include "stdafx.h"
#include "Sample.h"
#include "InfoForm.h"
#include "ParticleForm.h"
#include "HierarchyForm.h"
#include "resource.h"

/* z 값 비교를 위한 변수 */
//static float g_fPanelCnt = 0.0f;
Sample* Sample::m_pInstance = nullptr;
struct UISort
{
	bool operator()(const JPanel* src, const JPanel* desk)
	{
		if (src->m_iNumRender < desk->m_iNumRender)
			return TRUE;
		return FALSE;
	}
};

// ime msgevent
void Sample::MsgEvent(const MSG& _message) noexcept
{
	Input::Get().MsgEvent(_message);
	ime::Get()->WndProc(_message);
}
void Sample::SortCircuit(JPanel* pPanel)
{
	pPanel->m_pChildList.sort(UISort());

	for (auto iC = pPanel->m_pChildList.begin(); iC != pPanel->m_pChildList.end(); iC++)
	{
		SortCircuit(*iC);
	}
}
void Sample::ParentNameCircuit(JPanel* pParent)
{
	for (auto& pChild : pParent->m_pChildList)
	{
		pChild->m_ParentName = pParent->m_NodeName;
		ParentNameCircuit(pChild);
	}
}
/* ====================================================================== */
/* Save, Load */
/* ====================================================================== */
void Sample::SaveData(wstring SaveFileName)
{
	m_Write.RunWrite(pRoot, SaveFileName);
}
void Sample::LoadData(wstring LoadFileName)
{
	pCurCtrl = nullptr;
	pRoot->Release();
	pRoot->m_pChildList.clear();
	// HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
	par.FileLoad(DxManager::GetDevice(), LoadFileName.data(), *pRoot);
	TreeInitialization(pRoot);
	EventCircuit(pRoot, false);
	if (LoadFileName == L"Intro") IntroEvent();
	if (LoadFileName == L"Lobby") LobbyEvent();
	if (LoadFileName == L"InGame") InGameEvent();
}
void Sample::IntroEvent()
{
	//JPanel* pEffect = pRoot->find_child(L"effect_panel");
	//if (pEffect == nullptr) return;
	//pEffect->PreEvent.first = E_INTRO;
	//pEffect->PreEvent.second = pEffect;
	JPanel* pMouseCursor = pRoot->find_child(L"mouse_cursor");
	if (pMouseCursor == nullptr) return;
	pMouseCursor->PreEvent.first = UI::E_MOUSE_CURSOR;
	pMouseCursor->PreEvent.second = pMouseCursor;

	JPanel* pGameStart = pRoot->find_child(L"gamestart");
	if (pGameStart == nullptr) return;
	JPanel* pLogin = pRoot->find_child(L"Login_Panel");
	if (pLogin == nullptr) return;
	pGameStart->EventClick.first = E_REVERSE_SHOW;
	pGameStart->EventClick.second = pLogin;

	//JPanel* pLoginExit = (JPanel*)pRoot->find_child(L"Login_Exit");
	//if (pLoginExit == nullptr) return;
	//pLoginExit->EventClick.first = E_NOTSHOW;
	//pLoginExit->EventClick.second = pLoginExit->m_pParent;

	JPanel* pSignUp = (JPanel*)pRoot->find_child(L"Login_SignUp");
	JPanel* pSignUpPanel = (JPanel*)pRoot->find_child(L"SignUp_Panel");
	if (pSignUp == nullptr) return;
	if (pSignUpPanel == nullptr) return;
	pSignUp->EventClick.first = E_REVERSE_SHOW;
	pSignUp->EventClick.second = pSignUpPanel;

	//JPanel* pSignUpExit = (JPanel*)pRoot->find_child(L"SignUp_Top_Exit");
	//if (pSignUpExit == nullptr) return;
	//pSignUpExit->EventClick.first = E_NOTSHOW;
	//pSignUpExit->EventClick.second = pSignUpPanel;

	JPanel* pHelpText = (JPanel*)pRoot->find_child(L"Help_txt");
	if (pHelpText == nullptr) return;
	static auto E_HelpText = [](void* vp)
	{
		JPanel* pPanel = (JPanel*)vp;
		
		if(pPanel->m_bRender)
			pPanel->m_fUITimer += Timer::SPF;

		if (pPanel->m_fUITimer >= 3.0f)
		{
			pPanel->m_bRender = false;
			pPanel->m_fUITimer = 0.0f;
		}
	};
	pHelpText->PreEvent.first = E_HelpText;
	pHelpText->PreEvent.second = pHelpText;

	JPanel* pSkeleton = (JPanel*)pRoot->find_child(L"SkeletonFront");
	if (pSkeleton == nullptr) return;
	static auto E_REVERSE_ALPHA = [](void* vp)
	{
		JPanel* pPanel = (JPanel*)vp;
		static bool bAlpha = false;
		if (!bAlpha)
		{
			pPanel->m_pShape->m_cbData.vColor.w -= Timer::SPF;
			if (pPanel->m_pShape->m_cbData.vColor.w <= 0.0f)
				bAlpha = true;
		}
		else
		{
			pPanel->m_pShape->m_cbData.vColor.w += Timer::SPF;
			if (pPanel->m_pShape->m_cbData.vColor.w >= 1.0f)
				bAlpha = false;
		}
	};
	pSkeleton->PreEvent.first = E_REVERSE_ALPHA;
	pSkeleton->PreEvent.second = pSkeleton;
}
void Sample::LobbyEvent()
{
	JPanel* pGuest = (JPanel*)pRoot->find_child(L"Guest");
	if (pGuest == nullptr) return;
	JPanel* pGuestBtn = (JPanel*)pRoot->find_child(L"D_Guest");
	if (pGuestBtn == nullptr) return;
	pGuestBtn->EventClick.first = E_REVERSE_SHOW;
	pGuestBtn->EventClick.second = pGuest;

	//JPanel* pGuestExit = (JPanel*)pRoot->find_child(L"G_Exit");
	//if (pGuestExit == nullptr) return;
	//pGuestExit->EventClick.first = E_NOTSHOW;
	//pGuestExit->EventClick.second = pGuestExit->m_pParent;

	//JPanel* pMouseParticle = pRoot->find_child(L"mouse_particle");
	//if (pMouseParticle == nullptr) return;
	//pMouseParticle->PreEvent.first = UI::E_MOUSE_PARTICLE;
	//pMouseParticle->PreEvent.second = pMouseParticle;

	JPanel* pMouseCursor = pRoot->find_child(L"mouse_cursor");
	if (pMouseCursor == nullptr) return;
	pMouseCursor->PreEvent.first = UI::E_MOUSE_CURSOR;
	pMouseCursor->PreEvent.second = pMouseCursor;

	//JSpriteCtrl* pCursorClick = (JSpriteCtrl*)pRoot->find_child(L"mouse_click_sprite");
	//if (pCursorClick == nullptr) return;
	//pCursorClick->PreEvent.first = E_MOUSE_CLICK_SPRITE;
	//pCursorClick->PreEvent.second = pCursorClick;

	//JSpriteCtrl* pCursorErase = (JSpriteCtrl*)pRoot->find_child(L"mouse_click_sprite_panel");
	//if (pCursorErase == nullptr) return;
	//pCursorErase->PreEvent.first = E_MOUSE_SPRITE_ERASE;
	//pCursorErase->PreEvent.second = pCursorErase;

	JPanel* pHelpImg = (JPanel*)pRoot->find_child(L"HelpRect");
	if (pHelpImg == nullptr) return;
	pHelpImg->PreEvent.first = E_HELP_IMG;
	pHelpImg->PreEvent.second = pHelpImg;

	// effect
	//JPanel* pEff1 = (JPanel*)pRoot->find_child(L"fadeout");
	//if (pEff1 == nullptr) return;
	//pEff1->PreEvent.first = E_FADEOUT;
	//pEff1->PreEvent.second = pEff1;

	//JPanel* pEff2 = (JPanel*)pRoot->find_child(L"fadein");
	//if (pEff2 == nullptr) return;
	//pEff2->PreEvent.first = E_FADEIN;
	//pEff2->PreEvent.second = pEff2;

	//JPanel* pEff3 = (JPanel*)pRoot->find_child(L"effect3");
	//if (pEff3 == nullptr) return;
	//pEff3->PreEvent.first = E_EFFECT3;
	//pEff3->PreEvent.second = pEff3;

	JPanel* pEff4 = (JPanel*)pRoot->find_child(L"effect_hos");
	if (pEff4 == nullptr) return;
	pEff4->PreEvent.first = E_HOS;
	pEff4->PreEvent.second = pEff4;

	JPanel* pMatching_Panel = (JPanel*)pRoot->find_child(L"Matching_Panel");
	if (pMatching_Panel == nullptr) return;
	JPanel* AutoMatching = (JPanel*)pRoot->find_child(L"D_AutoMatching");
	if (AutoMatching == nullptr) return;
	AutoMatching->EventClick.first = E_REVERSE_SHOW;
	AutoMatching->EventClick.second = pMatching_Panel;

	//JPanel* pMatchingExit = (JPanel*)pRoot->find_child(L"Matching_Top_Exit");
	//if (pMatchingExit == nullptr) return;
	//pMatchingExit->EventClick.first = E_NOTSHOW;
	//pMatchingExit->EventClick.second = pMatching_Panel;

	JImageCtrl* pDrag = (JImageCtrl*)pRoot->find_child(L"Drag_Img");
	if (pDrag == nullptr) return;
	pDrag->PreEvent.first = E_DRAG;
	pDrag->PreEvent.second = pDrag;

	JPanel* pisMatching = (JPanel*)pRoot->find_child(L"isMatching_Sprite_Panel");
	if (pisMatching == nullptr) return;
	pisMatching->PreEvent.first = E_ISMATCHING;
	pisMatching->PreEvent.second = pisMatching;

	JPanel* pisMatchingTitle = (JPanel*)pRoot->find_child(L"isMatching_Title");
	if (pisMatchingTitle == nullptr) return;
	pisMatchingTitle->PreEvent.first = E_FONTCOLOR;	
	pisMatchingTitle->PreEvent.second = pisMatchingTitle;
	
}
void Sample::InGameEvent()
{
	JPanel* pMouseCursor = pRoot->find_child(L"mouse_cursor");
	if (pMouseCursor == nullptr) return;
	pMouseCursor->PreEvent.first = UI::E_MOUSE_CURSOR;
	pMouseCursor->PreEvent.second = pMouseCursor;

	//JSpriteCtrl* pCursorClick = (JSpriteCtrl*)pRoot->find_child(L"mouse_click_sprite");
	//if (pCursorClick == nullptr) return;
	//pCursorClick->PreEvent.first = E_MOUSE_CLICK_SPRITE;
	//pCursorClick->PreEvent.second = pCursorClick;

	//JSpriteCtrl* pCursorErase = (JSpriteCtrl*)pRoot->find_child(L"mouse_click_sprite_panel");
	//if (pCursorErase == nullptr) return;
	//pCursorErase->PreEvent.first = E_MOUSE_SPRITE_ERASE;
	//pCursorErase->PreEvent.second = pCursorErase;


	JPanel* pStatePanel = (JPanel*)pRoot->find_child(L"State_Panel");
	if (pStatePanel == nullptr) return;
	pStatePanel->PreEvent.first = E_STATE_SHOW;
	pStatePanel->PreEvent.second = pStatePanel;

	JPanel* pSetting = (JPanel*)pRoot->find_child(L"Set_Panel");
	pSetting->PreEvent.first = E_KEY_REVERSESHOW;
	pSetting->PreEvent.second = pSetting;

	JSliderCtrl* pChatSlider = (JSliderCtrl*)pRoot->find_child(L"Chat_Slider");
	JListCtrl* pList = (JListCtrl*)pRoot->find_child(L"Chat_Log");
	pList->m_fValue = &pChatSlider->m_fValue;
	
	// effect
	JPanel* pEff1 = (JPanel*)pRoot->find_child(L"fadeout");
	if (pEff1 == nullptr) return;
	pEff1->PreEvent.first = E_FADEOUT;
	pEff1->PreEvent.second = pEff1;

	JPanel* pEff3 = (JPanel*)pRoot->find_child(L"fadeout_white");
	if (pEff3 == nullptr) return;
	pEff3->PreEvent.first = E_FADEOUT;
	pEff3->PreEvent.second = pEff3;

	JPanel* pEff2 = (JPanel*)pRoot->find_child(L"fadein");
	if (pEff2 == nullptr) return;
	pEff2->PreEvent.first = E_FADEIN;
	pEff2->PreEvent.second = pEff2;

	//JPanel* pJohn = (JPanel*)pRoot->find_child(L"JohnSprite");
	//if (pJohn == nullptr) return;
	//pJohn->PreEvent.first = E_FADEOUT;
	//pJohn->PreEvent.second = pJohn;

	JPanel* pCrossHair = (JPanel*)pRoot->find_child(L"CrossHair");
	if (pCrossHair == nullptr) return;
	pCrossHair->PreEvent.first = E_CROSSHAIR;
	pCrossHair->PreEvent.second = pCrossHair;

	JPanel* pFight = (JPanel*)pRoot->find_child(L"fight_panel");
	if (pFight == nullptr) return;
	pFight->PreEvent.first = E_FIGHT;
	pFight->PreEvent.second = pFight;
	
	//JPanel* pTimeOver = (JPanel*)pRoot->find_child(L"TimeOver");
	//if (pTimeOver == nullptr) return;
	//pTimeOver->PreEvent.first = E_FADEINOUT;
	//pTimeOver->PreEvent.second = pTimeOver;

	JListCtrl* pKillToDeath = (JListCtrl*)pRoot->find_child(L"KilltoDeath");
	if (pKillToDeath == nullptr) return;
	pKillToDeath->PreEvent.first = E_KILLTODEATH;
	pKillToDeath->PreEvent.second = pKillToDeath;

	//JPanel* pChatEnter = (JPanel*)pRoot->find_child(L"Chat_Enter");
	//if (pChatEnter == nullptr) return;
	//pChatEnter->PreEvent.first = E_CHATENTER;
	//pChatEnter->PreEvent.second = pChatEnter;

	//JPanel* pEndingEffect = (JPanel*)pRoot->find_child(L"Effect_Ending_Panel");
	//if (pEndingEffect == nullptr) return;
	//pEndingEffect->PreEvent.first = E_ENDING_EFFECT;
	//pEndingEffect->PreEvent.second = pEndingEffect;

	JPanel* pInventoryPanel = (JPanel*)pRoot->find_child(L"Inventory_Panel");
	if (pInventoryPanel == nullptr) return;
	pInventoryPanel->PreEvent.first = E_KEY_REVERSESHOW;
	pInventoryPanel->PreEvent.second = pInventoryPanel;

	//JPanel* pInventoryExit = (JPanel*)pInventoryPanel->find_child(L"Inventory_Exit");
	//if (pInventoryExit == nullptr) return;
	//pInventoryExit->EventClick.first = E_NOTSHOW;
	//pInventoryExit->EventClick.second = pInventoryPanel;

	JPanel* pInventorySort = (JPanel*)pInventoryPanel->find_child(L"Inventory_Sort");
	JPanel* pInventorySlot = (JPanel*)pInventoryPanel->find_child(L"Inventory_Slot");
	if (pInventorySort == nullptr) return;
	pInventorySort->EventClick.first = E_INVENTORY_SORT;
	pInventorySort->EventClick.second = pInventorySlot;

	JPanel* pInventoryAdd = (JPanel*)pInventoryPanel->find_child(L"Inventory_ItemAdd");
	if (pInventoryAdd == nullptr) return;
	pInventoryAdd->EventClick.first = E_INVENTORY_ADD;
	pInventoryAdd->EventClick.second = pInventorySlot;

	JPanel* pInventoryDel = (JPanel*)pInventoryPanel->find_child(L"Inventory_Del");
	if (pInventoryDel == nullptr) return;
	pInventoryDel->EventClick.first = E_INVENTORY_DEL;
	pInventoryDel->EventClick.second = pInventorySlot;

	JPanel* pInfoPanel = (JPanel*)pRoot->find_child(L"Info_Panel");
	if (pInfoPanel == nullptr) return;
	pInfoPanel->PreEvent.first = E_KEY_REVERSESHOW;
	pInfoPanel->PreEvent.second = pInfoPanel;	
}
void Sample::EventCircuit(JPanel* pPanel, bool bValue)
{
	pPanel->m_bEvent = bValue;
	for (auto iC = pPanel->m_pChildList.begin(); iC != pPanel->m_pChildList.end(); iC++)
	{
		EventCircuit(*iC, bValue);
	}
}
/* ====================================================================== */
/* 트리 초기화 */
/* ====================================================================== */
void Sample::TreeInitialization(JPanel* Panel)
{
	/* 트리초기화 */
	HierarchyForm::Get()->m_HierarchyTree.DeleteAllItems();
	hChildList.clear();
	/* 루트 insert */
	hRoot = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pRoot->m_NodeName.data(), 0, 1, TVI_ROOT, TVI_LAST);
	Hierarchy RootTree;
	RootTree.hChild = hRoot;
	RootTree.strName = Panel->m_NodeName;
	hChildList.push_back(RootTree);

	TreeCircuit(Panel); // 트리 순회
}
void Sample::TreeCircuit(JPanel* Panel)
{
	if (Panel->m_pParent != nullptr)
	{
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			if (hChildList[iChild].strName == Panel->m_ParentName)
			{
				Hierarchy hierar;
				hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(Panel->m_NodeName.data(), 0, 1, hChildList[iChild].hChild, TVI_LAST);
				hierar.strName = Panel->m_NodeName;
				hChildList.push_back(hierar);
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
				break;
			}
		}
	}
	for (auto iC = Panel->m_pChildList.begin(); iC != Panel->m_pChildList.end(); iC++)
	{
		TreeCircuit(*iC);
	}
}
/* ====================================================================== */
/* Create Ctrl */
/* ====================================================================== */
void Sample::CreateButton(wstring NodeName, wstring ParentName)
{
	JButtonCtrl* btn = new JButtonCtrl(NodeName);
	btn->Create(DxManager::GetDevice(),
		L"../../data/ui/NO_IMAGE.png",
		L"../../data/ui/NO_IMAGE.png",
		L"../../data/ui/NO_IMAGE.png");
	btn->m_vScl = D3DXVECTOR3(50, 50, 1);
	/* Name */
	if (ParentName == L"")
	{
		//btn->m_vPos.z = 1.0f - ++pRoot->m_pChildList.size() * 0.000001f;
		pRoot->push_child(btn);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(btn->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = btn->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(btn);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(btn->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = btn->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = btn;
	UpdateInfo();
}
void Sample::CreateCheck(wstring NodeName, wstring ParentName)
{
	JCheckCtrl* chk = new JCheckCtrl(NodeName);
	chk->Create(DxManager::GetDevice(),
		L"../../data/ui/NO_IMAGE.png",
		L"../../data/ui/NO_IMAGE.png");
	chk->m_vScl = D3DXVECTOR3(50, 50, 1);
	//chk->m_vPos.z = 1.0f - ++g_fPanelCnt * 0.000001f;
	/* Name */
	if (ParentName == L"")
	{
		pRoot->push_child(chk);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(chk->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = chk->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(chk);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(chk->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = chk->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = chk;
	UpdateInfo();
}
void Sample::CreateProgress(wstring NodeName, wstring ParentName)
{
	JProgressBar* prog = new JProgressBar(NodeName);
	prog->Create(DxManager::GetDevice(),
		L"../../data/ui/NO_IMAGE.png",
		L"../../data/ui/NO_IMAGE.png");
	prog->m_vScl = D3DXVECTOR3(50, 10, 1);
	prog->m_pFrontGround->m_vScl = D3DXVECTOR3(50, 10, 1);
	//prog->m_vPos.z = 1.0f - ++g_fPanelCnt * 0.000001f;
	/* Name */
	if (ParentName == L"")
	{
		pRoot->push_child(prog);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(prog->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = prog->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(prog);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(prog->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = prog->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = prog;
	UpdateInfo();
}
void Sample::CreateSlider(wstring NodeName, wstring ParentName)
{
	JSliderCtrl* slider = new JSliderCtrl(NodeName);
	slider->Create(DxManager::GetDevice(),
		L"../../data/ui/NO_IMAGE.png",
		L"../../data/ui/NO_IMAGE.png");
	slider->m_vScl = D3DXVECTOR3(50, 10, 1); // Bar scl
	slider->m_pSliderHandle->m_vScl = D3DXVECTOR3(15, 15, 1);
	//slider->m_vPos.z = 1.0f - ++g_fPanelCnt * 0.000001f;
	/* Name */
	if (ParentName == L"")
	{
		pRoot->push_child(slider);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(slider->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = slider->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(slider);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(slider->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = slider->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = slider;
	UpdateInfo();
}
void Sample::CreateSprite(wstring NodeName, wstring ParentName)
{
	JSpriteCtrl* sprite = new JSpriteCtrl(NodeName);
	T_STR_VECTOR FileList;
	wstring temp = L"../../data/ui/NO_IMAGE.png";
	FileList.push_back(temp);
	sprite->Create(DxManager::GetDevice(), 1.0f, FileList);
	sprite->m_vScl = D3DXVECTOR3(50, 50, 1);
	//sprite->m_vPos.z = 1.0f - ++g_fPanelCnt * 0.000001f;
	/* Name */
	if (ParentName == L"")
	{
		pRoot->push_child(sprite);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(sprite->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = sprite->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(sprite);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(sprite->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = sprite->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = sprite;
	UpdateInfo();
}
void Sample::CreateText(wstring NodeName, wstring ParentName)
{
	JTextCtrl* txt = new JTextCtrl(NodeName);
	txt->Create(DxManager::GetDevice(),
		L"Sample txt",
		15,
		L"../../data/ui/NO_IMAGE.png",
		L"../../data/ui/NO_IMAGE.png",
		L"../../data/ui/NO_IMAGE.png");
	txt->m_vScl = D3DXVECTOR3(50, 50, 1);
	//txt->m_vPos.z = 1.0f - ++g_fPanelCnt * 0.000001f;
	/* Name */
	if (ParentName == L"")
	{
		pRoot->push_child(txt);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(txt->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = txt->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(txt);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(txt->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = txt->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = txt;
	UpdateInfo();
}
void Sample::CreateParticle(wstring NodeName, wstring ParentName)
{
	JParticleSystem* particle = new JParticleSystem(NodeName);
	particle->m_vScl = D3DXVECTOR3(50, 50, 1);
	//particle->m_vPos.z = 1.0f - ++g_fPanelCnt * 0.000001f;
	T_STR_VECTOR FileList;
	wstring str = L"../../data/ui/NO_IMAGE.png";
	FileList.push_back(str);
	particle->Create(DxManager::GetDevice(), 128, 1.0f, FileList);
	particle->SetScale(1, 10);
	particle->SetColor(D3DXVECTOR4(0, 0, 0, 1), D3DXVECTOR4(1, 1, 1, 1));
	particle->SetTurnDirection(false, false, false);
	particle->SetStartPos(D3DXVECTOR3(0, 0, 1), D3DXVECTOR3(0, 0, 1));
	particle->SetLifeTime(1, 1);
	particle->SetDirection(D3DXVECTOR3(-1, -1, 0), D3DXVECTOR3(1, 1, 0));
	particle->SetDirectionAngle(D3DXQUATERNION(0, 0, -1, 1), D3DXQUATERNION(0, 0, 1, 1));
	particle->SetMoveSpeed(150, 200);
	particle->SetRotateSpeed(5, 10);
	/* Name */
	if (ParentName == L"")
	{
		pRoot->push_child(particle);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(particle->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = particle->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(particle);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(particle->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = particle->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = particle;
	UpdateInfo();
}
void Sample::CreatePanel(wstring NodeName, wstring ParentName)
{
	JPanel* panel = new JPanel(NodeName);
	//panel->m_vPos.z = 1.0f - ++g_fPanelCnt * 0.000001f;
	/* Name */
	if (ParentName == L"")
	{
		pRoot->push_child(panel);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(panel->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = panel->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(panel);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(panel->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = panel->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = panel;
	UpdateInfo();
}
void Sample::CreateList(wstring NodeName, wstring ParentName)
{
	JListCtrl* pList = new JListCtrl(NodeName);
	pList->Create(DxManager::GetDevice(), L"../../data/ui/NO_IMAGE.png");
	pList->m_vScl = D3DXVECTOR3(50, 50, 1);
	/* Name */
	if (ParentName == L"")
	{
		//btn->m_vPos.z = 1.0f - ++pRoot->m_pChildList.size() * 0.000001f;
		pRoot->push_child(pList);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pList->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = pList->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(pList);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pList->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = pList->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = pList;
	UpdateInfo();
}
void Sample::CreateEdit(wstring NodeName, wstring ParentName)
{
	JEditCtrl* pEdit = new JEditCtrl(NodeName);
	pEdit->Create(DxManager::GetDevice(), 15.0f, L"../../data/ui/NO_IMAGE.png");
	pEdit->m_vScl = D3DXVECTOR3(50, 50, 1);
	// pEdit->Play();
	/* Name */
	if (ParentName == L"")
	{
		//btn->m_vPos.z = 1.0f - ++pRoot->m_pChildList.size() * 0.000001f;
		pRoot->push_child(pEdit);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pEdit->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = pEdit->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(pEdit);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pEdit->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = pEdit->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = pEdit;
	UpdateInfo();
}
void Sample::CreateImage(wstring NodeName, wstring ParentName)
{
	JImageCtrl* pImage = new JImageCtrl(NodeName);
	pImage->Create(DxManager::GetDevice());
	pImage->SetTexture(DxManager::GetDevice(), L"../../data/ui/NO_IMAGE.png");
	pImage->m_vScl = D3DXVECTOR3(50, 50, 1);
	// pEdit->Play();
	/* Name */
	if (ParentName == L"")
	{
		//btn->m_vPos.z = 1.0f - ++pRoot->m_pChildList.size() * 0.000001f;
		pRoot->push_child(pImage);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pImage->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = pImage->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(pImage);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pImage->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = pImage->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = pImage;
	UpdateInfo();
}
void Sample::CreateSlot(wstring NodeName, wstring ParentName)
{
	JSlot* pSlot = new JSlot(NodeName);
	pSlot->Create(DxManager::GetDevice(), L"../../data/ui/NO_IMAGE.png", L"../../data/ui/NO_IMAGE.png");
	//pSlot->SetTexture(DxManager::GetDevice(), L"../../data/ui/NO_IMAGE.png");
	pSlot->m_vScl = D3DXVECTOR3(50, 50, 1);
	// pEdit->Play();
	/* Name */
	if (ParentName == L"")
	{
		//btn->m_vPos.z = 1.0f - ++pRoot->m_pChildList.size() * 0.000001f;
		pRoot->push_child(pSlot);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pSlot->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = pSlot->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(pSlot);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pSlot->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = pSlot->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = pSlot;
	UpdateInfo();
}
void Sample::CreateInventory(wstring NodeName, wstring ParentName)
{
	JInventory* pInven = new JInventory(NodeName);
	pInven->Create(DxManager::GetDevice(), 2, 2, L"../../data/ui/NO_IMAGE.png", L"../../data/ui/NO_IMAGE.png");
	//pSlot->SetTexture(DxManager::GetDevice(), L"../../data/ui/NO_IMAGE.png");
	pInven->m_vScl = D3DXVECTOR3(100, 100, 1);
	// pEdit->Play();
	/* Name */
	if (ParentName == L"")
	{
		//btn->m_vPos.z = 1.0f - ++pRoot->m_pChildList.size() * 0.000001f;
		pRoot->push_child(pInven);
		Hierarchy hierar;
		hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pInven->m_NodeName.data(), 1, 1, hRoot, TVI_LAST);
		hierar.strName = pInven->m_NodeName;
		hChildList.push_back(hierar);
		/* Hierarchy 펼치기 */
		HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
		for (int iChild = 0; iChild < hChildList.size(); iChild++)
		{
			HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
		}
	}
	else
	{
		JPanel* pParent = pRoot->find_child(ParentName);
		if (pParent == nullptr)
			AfxMessageBox(L"Parent Name Error");
		else
		{
			pParent->push_child(pInven);
			/* HTREEITEM 저장 (Hierarchy) */
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				if (hChildList[iChild].strName == ParentName)
				{
					Hierarchy hierar;
					hierar.hChild = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pInven->m_NodeName.data(), 1, 1, hChildList[iChild].hChild, TVI_LAST);
					hierar.strName = pInven->m_NodeName;
					hChildList.push_back(hierar);
				}
			}
			/* Hierarchy 펼치기 */
			HierarchyForm::Get()->m_HierarchyTree.Expand(hRoot, TVE_EXPAND);
			for (int iChild = 0; iChild < hChildList.size(); iChild++)
			{
				HierarchyForm::Get()->m_HierarchyTree.Expand(hChildList[iChild].hChild, TVE_EXPAND);
			}
		}
	}
	/* =================================== */
	pCurCtrl = pInven;
	UpdateInfo();
}
/* ====================================================================== */
/* Update */
/* ====================================================================== */
wstring Sample::FindType()
{
	if (pCurCtrl->m_Type == PANEL)
		return L"PANEL";
	if (pCurCtrl->m_Type == BUTTON)
		return L"BUTTON";
	if (pCurCtrl->m_Type == CHECK)
		return L"CHECK";
	if (pCurCtrl->m_Type == PROGRESS)
		return L"PROGRESS";
	if (pCurCtrl->m_Type == SLIDER)
		return L"SLIDER";
	if (pCurCtrl->m_Type == SPRITE)
		return L"SPRITE";
	if (pCurCtrl->m_Type == TEXT)
		return L"TEXT";
	if (pCurCtrl->m_Type == PARTICLE)
		return L"PARTICLE";
	if (pCurCtrl->m_Type == LIST)
		return L"LIST";
	if (pCurCtrl->m_Type == EDIT)
		return L"EDIT";
	if (pCurCtrl->m_Type == IMAGE)
		return L"IMAGE";
	if (pCurCtrl->m_Type == SLOT)
		return L"SLOT";
	if (pCurCtrl->m_Type == INVENTORY)
		return L"INVENTORY";
	return L"";
}
VHType Sample::FindVHType(wstring type)
{
	if (type == L"Vertical")
		return Vertical;
	if (type == L"Horizontal")
		return Horizontal;
	return NONE;
}
wstring Sample::FindVHType(VHType type)
{
	if (type == Vertical)
		return L"Vertical";
	if (type == Horizontal)
		return L"Horizontal";
	return L"";
}
SpriteType Sample::FindSpriteType(wstring type)
{
	if (type == L"TEXSPRITE")
		return TEXSPRITE;
	if (type == L"UVSPRITE")
		return UVSPRITE;
	return TEMPSPRITE;
}
wstring Sample::FindSpriteType(SpriteType type)
{
	if (type == TEXSPRITE)
		return L"TEXSPRITE";
	if (type == UVSPRITE)
		return L"UVSPRITE";
	return L"";
}
wstring Sample::FindAlign(EAlign type)
{
	if (type == EAlign::Near)
		return L"LEFT";
	if (type == EAlign::Center)
		return L"CENTER";
	if (type == EAlign::Far)
		return L"RIGHT";
	return L"";
}
EAlign Sample::FindAlign(wstring type)
{
	if (type == L"LEFT")
		return EAlign::Near;
	if (type == L"CENTER")
		return EAlign::Center;
	if (type == L"RIGHT")
		return EAlign::Far;
	return EAlign::Near;
}
void Sample::pushSelect(JPanel* pPanel)
{
	for (auto iC = pPanel->m_pChildList.begin(); iC != pPanel->m_pChildList.end(); iC++)
	{
		JPanel* pCtrl = (*iC);
		/* 클릭한 곳의 Panel들을 전부 넣는다. */
		if (!pCtrl->m_bRender || pCtrl->m_Type == UIType::INVENTORYSLOT) continue;
		if ( JDxHelper::RectInPt(pCtrl->m_rt, pCtrl->m_ptMouse.Getpt()))
		{
			pSelectList.push_back(pCtrl);
		}
		pushSelect(pCtrl);
	}
}
void Sample::Update()
{
	/* 화면 바깥으로 마우스 넘어가면 ㄾ */
	POINT pt = pRoot->m_ptMouse.Getpt();
	if (pt.x > pRoot->m_fWidth / 2.0f || pt.x < -(pRoot->m_fWidth / 2.0f) ||
		pt.y > pRoot->m_fHeight / 2.0f || pt.y < -(pRoot->m_fHeight / 2.0f))
	{
		m_Type = FREE;
		return;
	}
	else
	{
		m_Type = m_BeforeType;
	}
	/* CurCtrl Select */
	if (Input::GetKeyState(EMouseButton::Left) == EKeyState::DOWN)
	{
		pushSelect(pRoot);

		// 수정/* SelectList에 넣어진 Panel들끼리 z값비교하고 맨 위의 Panel이 CurCtrl이 된다. */
		/* 걍 앞에있는놈이 Cur */
		if (pSelectList.size() == 0)
		{
			//pCurCtrl = nullptr;
		}
		else if (pSelectList.size() == 1)
		{
			pCurCtrl = pSelectList[0];
			UpdateInfo();
			pSelectList.clear();
		}
		else
		{
			//JPanel* pSelect = pSelectList[0];
			//for (int iSelect = 1; iSelect < pSelectList.size(); iSelect++)
			//{
			//	JPanel* Src = pSelectList[iSelect];
			//	JPanel* Desk = pSelect;
			//	/* z값 작은 panel find */
			//	if (Src->m_matWorld._43 < Desk->m_matWorld._43)
			//	{
			//		pSelect = Src;
			//	}
			//	else
			//	{
			//		pSelect = Desk;
			//	}
			//}
			//pCurCtrl = pSelect;
			pCurCtrl = pSelectList[pSelectList.size() - 1];
			UpdateInfo();
			pSelectList.clear();
		}
	}

	/* Type Setting */
	if (Input::GetKeyState(VK_SHIFT) == EKeyState::HOLD && Input::GetKeyState('1') == EKeyState::DOWN) m_Type = m_BeforeType = TRANS;
	if (Input::GetKeyState(VK_SHIFT) == EKeyState::HOLD && Input::GetKeyState('2') == EKeyState::DOWN) m_Type = m_BeforeType = ROTATE;
	if (Input::GetKeyState(VK_SHIFT) == EKeyState::HOLD && Input::GetKeyState('3') == EKeyState::DOWN) m_Type = m_BeforeType = SCALE;

	/* Value값 갱신하게... */
	if (pCurCtrl != nullptr && pCurCtrl->m_Type == SLIDER)
	{
		UpdateInfo();
	}

	/* Mouse SRT*/
	ptScaling();
	ptRotation();
	ptTransition();
	/* Key SRT */
	KeyScaling();
	KeyRotation();
	KeyTransition();
}
void Sample::UpdateInfo()
{
	if (pCurCtrl == nullptr) return;
	// == SRT
	InfoForm::Get()->SetDlgItemTextW(Info_PosX, std::to_wstring(pCurCtrl->m_vPos.x).data());
	InfoForm::Get()->SetDlgItemTextW(Info_PosY, std::to_wstring(pCurCtrl->m_vPos.y).data());
	InfoForm::Get()->SetDlgItemTextW(Info_PosZ, std::to_wstring(pCurCtrl->m_vPos.z).data());
	InfoForm::Get()->SetDlgItemTextW(Info_RotX, std::to_wstring(D3DXToDegree(pCurCtrl->m_vRot.x)).data());
	InfoForm::Get()->SetDlgItemTextW(Info_RotY, std::to_wstring(D3DXToDegree(pCurCtrl->m_vRot.y)).data());
	InfoForm::Get()->SetDlgItemTextW(Info_RotZ, std::to_wstring(D3DXToDegree(pCurCtrl->m_vRot.z)).data());
	InfoForm::Get()->SetDlgItemTextW(Info_SclX, std::to_wstring(pCurCtrl->m_vScl.x).data());
	InfoForm::Get()->SetDlgItemTextW(Info_SclY, std::to_wstring(pCurCtrl->m_vScl.y).data());
	InfoForm::Get()->SetDlgItemTextW(Info_SclZ, std::to_wstring(pCurCtrl->m_vScl.z).data());

	// == value
	//InfoForm::Get()->SetDlgItemTextW(Info_Value, 0);
	// == bRender
	InfoForm::Get()->m_bRender.SetCheck(pCurCtrl->m_bRender);
	// == name type numrender
	InfoForm::Get()->SetDlgItemTextW(Info_NodeName, pCurCtrl->m_NodeName.data());
	InfoForm::Get()->SetDlgItemTextW(Info_ParentName, pCurCtrl->m_ParentName.data());
	InfoForm::Get()->SetDlgItemTextW(Info_CtrlType, FindType().data());
	InfoForm::Get()->SetDlgItemTextW(Info_NumRender, std::to_wstring(pCurCtrl->m_iNumRender).data());
	// == info event
	InfoForm::Get()->SetDlgItemTextW(Info_vpEventHover, pCurCtrl->m_vpHover.data());
	InfoForm::Get()->m_pfHover.SetCurSel(InfoForm::Get()->m_pfHover.FindString(0, FindPointerFunc(pCurCtrl->m_pfHover).data()));
	InfoForm::Get()->SetDlgItemTextW(Info_vpEventPress, pCurCtrl->m_vpPress.data());
	InfoForm::Get()->m_pfPress.SetCurSel(InfoForm::Get()->m_pfPress.FindString(0, FindPointerFunc(pCurCtrl->m_pfPress).data()));
	InfoForm::Get()->SetDlgItemTextW(Info_vpEventClick, pCurCtrl->m_vpClick.data());
	InfoForm::Get()->m_pfClick.SetCurSel(InfoForm::Get()->m_pfClick.FindString(0, FindPointerFunc(pCurCtrl->m_pfClick).data()));
	// sprite uv
	InfoForm::Get()->SetDlgItemTextW(Info_SpriteRows, L"");
	InfoForm::Get()->SetDlgItemTextW(Info_SpriteCols, L"");
	InfoForm::Get()->SetDlgItemTextW(Info_MaxLength, L"");
	//// sub
	//InfoForm::Get()->SetDlgItemTextW(Info_SubSclX, L"");
	//InfoForm::Get()->SetDlgItemTextW(Info_SubSclY, L"");
	//InfoForm::Get()->SetDlgItemTextW(Info_SubSclZ, L"");
	// keyDown keyHold
	InfoForm::Get()->m_KeyDown.SetCurSel(InfoForm::Get()->m_KeyDown.FindString(0, FindKeyDownHold(pCurCtrl->m_pKeyDown).data()));
	InfoForm::Get()->m_KeyHold.SetCurSel(InfoForm::Get()->m_KeyHold.FindString(0, FindKeyDownHold(pCurCtrl->m_pKeyHold).data()));

	InfoForm::Get()->m_PassWord.SetCheck(false);

	if (pCurCtrl->m_Type == PANEL)
	{
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER,  L"");
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS,  L"");

		InfoForm::Get()->SetDlgItemTextW(ColorX, L"");
		InfoForm::Get()->SetDlgItemTextW(ColorY, L"");
		InfoForm::Get()->SetDlgItemTextW(ColorZ, L"");
		InfoForm::Get()->SetDlgItemTextW(ColorW, L"");

		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == BUTTON)
	{
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pCurCtrl->m_pIndexList[UI::txNORMAL])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, I_TexMgr.GetPtr(pCurCtrl->m_pIndexList[UI::txHOVER])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, I_TexMgr.GetPtr(pCurCtrl->m_pIndexList[UI::txPRESS])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pCurCtrl->m_pShape->m_cbData.vColor.x).data());
		InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pCurCtrl->m_pShape->m_cbData.vColor.y).data());
		InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pCurCtrl->m_pShape->m_cbData.vColor.z).data());
		InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pCurCtrl->m_pShape->m_cbData.vColor.w).data());
		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == CHECK)
	{
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pCurCtrl->m_pIndexList[UI::txDISABLE])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, I_TexMgr.GetPtr(pCurCtrl->m_pIndexList[UI::txENABLE])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
		InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pCurCtrl->m_pShape->m_cbData.vColor.x).data());
		InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pCurCtrl->m_pShape->m_cbData.vColor.y).data());
		InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pCurCtrl->m_pShape->m_cbData.vColor.z).data());
		InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pCurCtrl->m_pShape->m_cbData.vColor.w).data());
		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == PROGRESS)
	{
		JProgressBar* pProgress = (JProgressBar*)pCurCtrl;
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pProgress->m_pBackGround->m_pIndexList[UI::txNORMAL])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, I_TexMgr.GetPtr(pProgress->m_pFrontGround->m_pIndexList[UI::txNORMAL])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_Value, std::to_wstring(pProgress->m_fValue).data());
		InfoForm::Get()->m_VHType.SetCurSel(InfoForm::Get()->m_VHType.FindString(0, FindVHType(pProgress->m_VHType).data()));
		//InfoForm::Get()->SetDlgItemTextW(IDC_VHType, FindVHType(pProgress->m_VHType).data());

		InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pProgress->m_pBackGround->m_pShape->m_cbData.vColor.x).data());
		InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pProgress->m_pBackGround->m_pShape->m_cbData.vColor.y).data());
		InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pProgress->m_pBackGround->m_pShape->m_cbData.vColor.z).data());
		InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pProgress->m_pBackGround->m_pShape->m_cbData.vColor.w).data());
		InfoForm::Get()->SetDlgItemTextW(Info_SubSclX, std::to_wstring(pProgress->m_pFrontGround->m_vScl.x).data());
		InfoForm::Get()->SetDlgItemTextW(Info_SubSclY, std::to_wstring(pProgress->m_pFrontGround->m_vScl.y).data());
		InfoForm::Get()->SetDlgItemTextW(Info_SubSclZ, std::to_wstring(pProgress->m_pFrontGround->m_vScl.z).data());

		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == SLIDER)
	{
		JSliderCtrl* pslider = (JSliderCtrl*)pCurCtrl;
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pslider->m_pSliderBar->m_pIndexList[UI::txNORMAL])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, I_TexMgr.GetPtr (pslider->m_pSliderHandle->m_pIndexList[UI::txNORMAL])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_Value, std::to_wstring(pslider->m_fValue).data());
		InfoForm::Get()->m_VHType.SetCurSel(InfoForm::Get()->m_VHType.FindString(0, FindVHType(pslider->m_VHType).data()));
		InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pslider->m_pSliderBar->m_pShape->m_cbData.vColor.x).data());
		InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pslider->m_pSliderBar->m_pShape->m_cbData.vColor.y).data());
		InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pslider->m_pSliderBar->m_pShape->m_cbData.vColor.z).data());
		InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pslider->m_pSliderBar->m_pShape->m_cbData.vColor.w).data());
		InfoForm::Get()->SetDlgItemTextW(Info_SubSclX, std::to_wstring(pslider->m_pSliderHandle->m_vScl.x).data());
		InfoForm::Get()->SetDlgItemTextW(Info_SubSclY, std::to_wstring(pslider->m_pSliderHandle->m_vScl.y).data());
		InfoForm::Get()->SetDlgItemTextW(Info_SubSclZ, std::to_wstring(pslider->m_pSliderHandle->m_vScl.z).data());
		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == SPRITE)
	{
		JSpriteCtrl* pSprite = (JSpriteCtrl*)pCurCtrl;
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
		InfoForm::Get()->m_pSpriteLoop.SetCheck(pSprite->m_bLoop);
		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
		InfoForm::Get()->m_SpriteType.SetCurSel(InfoForm::Get()->m_SpriteType.FindString(0, FindSpriteType(pSprite->m_SpriteType).data()));
		InfoForm::Get()->SetDlgItemTextW(Info_SpriteRows, std::to_wstring(pSprite->m_iRows).data());
		InfoForm::Get()->SetDlgItemTextW(Info_SpriteCols, std::to_wstring(pSprite->m_iCols).data());
		for (int iSprite = 0; iSprite < pSprite->m_pIndexList.size(); iSprite++)
		{
			InfoForm::Get()->m_pSpriteList.AddString(I_TexMgr.GetPtr(pSprite->m_pIndexList[iSprite])->m_szName.data());
			InfoForm::Get()->m_pSpritePath.push_back(I_TexMgr.GetPtr(pSprite->m_pIndexList[iSprite])->m_szFullPath);
		}
		InfoForm::Get()->SetDlgItemTextW(Info_SpriteAnimTime, std::to_wstring(pSprite->m_fAnimTime).data());

		InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pSprite->m_pShape->m_cbData.vColor.x).data());
		InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pSprite->m_pShape->m_cbData.vColor.y).data());
		InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pSprite->m_pShape->m_cbData.vColor.z).data());
		InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pSprite->m_pShape->m_cbData.vColor.w).data());
																		 
	}
	else if (pCurCtrl->m_Type == TEXT)
	{
		JTextCtrl* pText = (JTextCtrl*)pCurCtrl;
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pCurCtrl->m_pIndexList[UI::txNORMAL])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, I_TexMgr.GetPtr(pCurCtrl->m_pIndexList[UI::txHOVER])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, I_TexMgr.GetPtr(pCurCtrl->m_pIndexList[UI::txPRESS])->m_szName.data());

		InfoForm::Get()->SetDlgItemTextW(Info_TextString, pText->m_Text.data());
		InfoForm::Get()->SetDlgItemTextW(Info_TextSize, std::to_wstring(pText->m_fSize).data());
		InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pText->m_pShape->m_cbData.vColor.x).data());
		InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pText->m_pShape->m_cbData.vColor.y).data());
		InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pText->m_pShape->m_cbData.vColor.z).data());
		InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pText->m_pShape->m_cbData.vColor.w).data());

		InfoForm::Get()->m_Align.SetCurSel(InfoForm::Get()->m_Align.FindString(0, FindAlign(pText->m_Align).data()));
		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == PARTICLE)
	{
		JParticleSystem* pParticle = (JParticleSystem*)pCurCtrl;
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
		InfoForm::Get()->m_pSpriteLoop.SetCheck(pParticle->m_pSprite->m_bLoop);
		InfoForm::Get()->m_SpriteType.SetCurSel(InfoForm::Get()->m_SpriteType.FindString(0, FindSpriteType(pParticle->m_pSprite->m_SpriteType).data()));
		InfoForm::Get()->SetDlgItemTextW(Info_SpriteRows, std::to_wstring(pParticle->m_pSprite->m_iRows).data());
		InfoForm::Get()->SetDlgItemTextW(Info_SpriteCols, std::to_wstring(pParticle->m_pSprite->m_iCols).data());
		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
		for (int iSprite = 0; iSprite < pParticle->m_pSprite->m_pIndexList.size(); iSprite++)
		{
			InfoForm::Get()->m_pSpriteList.AddString(I_TexMgr.GetPtr(pParticle->m_pSprite->m_pIndexList[iSprite])->m_szName.data());
			InfoForm::Get()->m_pSpritePath.push_back(I_TexMgr.GetPtr(pParticle->m_pSprite->m_pIndexList[iSprite])->m_szFullPath);
		}
		InfoForm::Get()->SetDlgItemTextW(Info_SpriteAnimTime, std::to_wstring(pParticle->m_pSprite->m_fAnimTime).data());
		UpdateParticleInfo();
	}
	else if (pCurCtrl->m_Type == LIST)
	{
		JListCtrl* pList = (JListCtrl*)pCurCtrl;
		InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pList->m_pIndexList[UI::txNORMAL])->m_szName.data());
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
		InfoForm::Get()->SetDlgItemTextW(Info_Value, std::to_wstring(*pList->m_fValue).data());
		InfoForm::Get()->SetDlgItemTextW(Info_TextSize, std::to_wstring(pList->m_fSize).data());
		InfoForm::Get()->SetDlgItemTextW(Info_ListColumn, std::to_wstring(pList->m_iCols).data());
		InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pList->m_pShape->m_cbData.vColor.x).data());
		InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pList->m_pShape->m_cbData.vColor.y).data());
		InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pList->m_pShape->m_cbData.vColor.z).data());
		InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pList->m_pShape->m_cbData.vColor.w).data());

		InfoForm::Get()->m_Align.SetCurSel(InfoForm::Get()->m_Align.FindString(0, FindAlign(pList->m_Align).data()));

		InfoForm::Get()->m_pSpriteList.ResetContent();
		InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == EDIT)
	{
	JEditCtrl* pEdit = (JEditCtrl*)pCurCtrl;
	InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pEdit->m_pIndexList[UI::txNORMAL])->m_szName.data());
	InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, L"");
	InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
	InfoForm::Get()->SetDlgItemTextW(Info_TextSize, std::to_wstring(pEdit->m_fSize).data());
	InfoForm::Get()->SetDlgItemTextW(Info_MaxLength, std::to_wstring(pEdit->m_iMaxLength).data());
	InfoForm::Get()->m_PassWord.SetCheck(pEdit->m_bPrivate);
	InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pEdit->m_pShape->m_cbData.vColor.x).data());
	InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pEdit->m_pShape->m_cbData.vColor.y).data());
	InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pEdit->m_pShape->m_cbData.vColor.z).data());
	InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pEdit->m_pShape->m_cbData.vColor.w).data());

	InfoForm::Get()->m_Align.SetCurSel(InfoForm::Get()->m_Align.FindString(0, FindAlign(pEdit->m_Align).data()));

	InfoForm::Get()->m_pSpriteList.ResetContent();
	InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == IMAGE)
	{
	JImageCtrl* pImage = (JImageCtrl*)pCurCtrl;
	InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pImage->m_pIndexList[UI::txNORMAL])->m_szName.data());
	InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, L"");
	InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
	InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pImage->m_pShape->m_cbData.vColor.x).data());
	InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pImage->m_pShape->m_cbData.vColor.y).data());
	InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pImage->m_pShape->m_cbData.vColor.z).data());
	InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pImage->m_pShape->m_cbData.vColor.w).data());
	InfoForm::Get()->m_pSpriteList.ResetContent();
	InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == SLOT)
	{
	JSlot* pSlot = (JSlot*)pCurCtrl;
	InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pSlot->m_pBack->m_pIndexList[UI::txNORMAL])->m_szName.data());
	InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, L"");
	InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
	InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pSlot->m_pBack->m_pShape->m_cbData.vColor.x).data());
	InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pSlot->m_pBack->m_pShape->m_cbData.vColor.y).data());
	InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pSlot->m_pBack->m_pShape->m_cbData.vColor.z).data());
	InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pSlot->m_pBack->m_pShape->m_cbData.vColor.w).data());
	InfoForm::Get()->m_pSpriteList.ResetContent();
	InfoForm::Get()->m_pSpritePath.clear();
	}
	else if (pCurCtrl->m_Type == INVENTORY)
	{
	JInventory* pInven = (JInventory*)pCurCtrl;
	//pInven->m_bUpdate = true;
	InfoForm::Get()->SetDlgItemTextW(Info_txNORMAL, I_TexMgr.GetPtr(pInven->m_pBack->m_pIndexList[UI::txNORMAL])->m_szName.data());
	if(pInven->m_pItemList[0] != nullptr)
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, I_TexMgr.GetPtr(pInven->m_pItemList[0]->m_pBack->m_pIndexList[UI::txNORMAL])->m_szName.data());
	else
		InfoForm::Get()->SetDlgItemTextW(Info_txHOVER, L"");
	InfoForm::Get()->SetDlgItemTextW(Info_txPRESS, L"");
	InfoForm::Get()->SetDlgItemTextW(Info_InvenRow, std::to_wstring(pInven->m_iRows).data());
	InfoForm::Get()->SetDlgItemTextW(Info_InvenCol, std::to_wstring(pInven->m_iCols).data());
	InfoForm::Get()->SetDlgItemTextW(ColorX, std::to_wstring(pInven->m_pBack->m_pShape->m_cbData.vColor.x).data());
	InfoForm::Get()->SetDlgItemTextW(ColorY, std::to_wstring(pInven->m_pBack->m_pShape->m_cbData.vColor.y).data());
	InfoForm::Get()->SetDlgItemTextW(ColorZ, std::to_wstring(pInven->m_pBack->m_pShape->m_cbData.vColor.z).data());
	InfoForm::Get()->SetDlgItemTextW(ColorW, std::to_wstring(pInven->m_pBack->m_pShape->m_cbData.vColor.w).data());
	InfoForm::Get()->m_pSpriteList.ResetContent();
	InfoForm::Get()->m_pSpritePath.clear();
	}
}
void Sample::UpdateParticleInfo()
{
	if (pCurCtrl->m_Type == PARTICLE)
	{
		JParticleSystem* pParticle = (JParticleSystem*)pCurCtrl;
		ParticleForm::Get()->SetDlgItemTextW(P_MAXSIZE, std::to_wstring(pParticle->m_iMaxParticle).data());
		// Min StartPos
		ParticleForm::Get()->SetDlgItemTextW(P_MinScale, std::to_wstring(pParticle->m_fMinScale).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxScale, std::to_wstring(pParticle->m_fMaxScale).data());
		// Min StartPos
		ParticleForm::Get()->SetDlgItemTextW(P_MINSTARTPOSX, std::to_wstring(pParticle->m_vMinStartPos.x).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MINSTARTPOSY, std::to_wstring(pParticle->m_vMinStartPos.y).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MINSTARTPOSZ, std::to_wstring(pParticle->m_vMinStartPos.z).data());
		// Max StartPos
		ParticleForm::Get()->SetDlgItemTextW(P_MAXSTARTPOSX, std::to_wstring(pParticle->m_vMaxStartPos.x).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MAXSTARTPOSY, std::to_wstring(pParticle->m_vMaxStartPos.y).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MAXSTARTPOSZ, std::to_wstring(pParticle->m_vMaxStartPos.z).data());
		//Turn Direction & bRandStartPos
		ParticleForm::Get()->m_pTurnX.SetCheck(pParticle->m_bTurnX);
		ParticleForm::Get()->m_pTurnY.SetCheck(pParticle->m_bTurnY);
		ParticleForm::Get()->m_pTurnZ.SetCheck(pParticle->m_bTurnZ);
		//Min Color
		ParticleForm::Get()->SetDlgItemTextW(P_MinColorX, std::to_wstring(pParticle->m_vMinColor.x).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MinColorY, std::to_wstring(pParticle->m_vMinColor.y).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MinColorZ, std::to_wstring(pParticle->m_vMinColor.z).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MinColorW, std::to_wstring(pParticle->m_vMinColor.w).data());
		// Max Color
		ParticleForm::Get()->SetDlgItemTextW(P_MaxColorX, std::to_wstring(pParticle->m_vMaxColor.x).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxColorY, std::to_wstring(pParticle->m_vMaxColor.y).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxColorZ, std::to_wstring(pParticle->m_vMaxColor.z).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxColorW, std::to_wstring(pParticle->m_vMaxColor.w).data());
		// LifeTime
		ParticleForm::Get()->SetDlgItemTextW(P_MinLifeTime, std::to_wstring(pParticle->m_fMinLifeTime).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxLifeTime, std::to_wstring(pParticle->m_fMaxLifeTime).data());
		// Min Direction
		ParticleForm::Get()->SetDlgItemTextW(P_MinDirectionX, std::to_wstring(pParticle->m_vMinDirection.x).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MinDirectionY, std::to_wstring(pParticle->m_vMinDirection.y).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MinDirectionZ, std::to_wstring(pParticle->m_vMinDirection.z).data());
		// Max Direction
		ParticleForm::Get()->SetDlgItemTextW(P_MaxDirectionX, std::to_wstring(pParticle->m_vMaxDirection.x).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxDirectionY, std::to_wstring(pParticle->m_vMaxDirection.y).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxDirectionZ, std::to_wstring(pParticle->m_vMaxDirection.z).data());
		// Min Direction Angle
		ParticleForm::Get()->SetDlgItemTextW(P_MinDirectionAngleX, std::to_wstring(pParticle->m_qMinDirAngle.x).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MinDirectionAngleY, std::to_wstring(pParticle->m_qMinDirAngle.y).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MinDirectionAngleZ, std::to_wstring(pParticle->m_qMinDirAngle.z).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MinDirectionAngleW, std::to_wstring(pParticle->m_qMinDirAngle.w).data());
		// Max Direction Angle
		ParticleForm::Get()->SetDlgItemTextW(P_MaxDirectionAngleX, std::to_wstring(pParticle->m_qMaxDirAngle.x).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxDirectionAngleY, std::to_wstring(pParticle->m_qMaxDirAngle.y).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxDirectionAngleZ, std::to_wstring(pParticle->m_qMaxDirAngle.z).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxDirectionAngleW, std::to_wstring(pParticle->m_qMaxDirAngle.w).data());
		// MoveSpeed
		ParticleForm::Get()->SetDlgItemTextW(P_MinMoveSpeed, std::to_wstring(pParticle->m_fMinMoveSpeed).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxMoveSpeed, std::to_wstring(pParticle->m_fMaxMoveSpeed).data());
		// RotateSpeed
		ParticleForm::Get()->SetDlgItemTextW(P_MinRotSpeed, std::to_wstring(pParticle->m_fMinRotateSpeed).data());
		ParticleForm::Get()->SetDlgItemTextW(P_MaxRotSpeed, std::to_wstring(pParticle->m_fMaxRotateSpeed).data());
	}
}
void Sample::ptTransition()
{
	if (pCurCtrl == nullptr) return;
	if (m_Type == TRANS)
		//&& Input::GetKeyState(EMouseButton::Left) == EKeyState::DOWN))
		//|| (m_Type == TRANS && Input::GetKeyState(EMouseButton::Left) == EKeyState::HOLD))
	{
		static float fDX = 0.0f;
		static float fDY = 0.0f;
		D3DXVECTOR3 vPos;
		if (JDxHelper::RectInPt(pCurCtrl->m_rt, pCurCtrl->m_ptMouse.Getpt()))
		{
			/* 처음 MOUSE PUSH를 하게되면 아래의 PUSH 조건이 걸림 */
			/* 그 이후의 MouseState는 HOLD가 되기때문에 아래의 PUSH 조건은 안걸림 */
			/* HOLD조건에 걸리기때문에 Mouse UP이 되기전까진 Rect와 Mouse의 Distance만큼 떨어지게 된다 */
			if (Input::GetKeyState(EMouseButton::Left) == EKeyState::DOWN)
			{
				fDX = 0.0f;
				fDY = 0.0f;
				vPos = pCurCtrl->m_vPos;
				D3DXVECTOR3 v0 = D3DXVECTOR3((float)vPos.x, (float)vPos.y, (float)vPos.z);
				D3DXVECTOR3 v1 = D3DXVECTOR3((float)pCurCtrl->m_ptMouse.Getpt().x, (float)pCurCtrl->m_ptMouse.Getpt().y, 0.0f);
				fDX = v0.x - v1.x;
				fDY = v0.y - v1.y;
				bClick = true;
			}
		}
		if (!bClick) return;
		if (Input::GetKeyState(EMouseButton::Left) == EKeyState::HOLD)
		{
			pCurCtrl->m_vPos.x = pCurCtrl->m_ptMouse.Getpt().x + fDX;
			pCurCtrl->m_vPos.y = pCurCtrl->m_ptMouse.Getpt().y + fDY;
			InfoForm::Get()->SetDlgItemTextW(Info_PosX, std::to_wstring(pCurCtrl->m_vPos.x).data());
			InfoForm::Get()->SetDlgItemTextW(Info_PosY, std::to_wstring(pCurCtrl->m_vPos.y).data());
			InfoForm::Get()->SetDlgItemTextW(Info_PosZ, std::to_wstring(pCurCtrl->m_vPos.z).data());
		}
		if (Input::GetKeyState(EMouseButton::Left) == EKeyState::UP)
		{
			fDX = 0.0f;
			fDY = 0.0f;
			bClick = false;
		}
	}
}
void Sample::ptRotation()
{
	if (pCurCtrl == nullptr) return;
	if (m_Type == ROTATE && Input::GetKeyState(EMouseButton::Left) == EKeyState::HOLD)
	{
		if (bCheck == false)
		{
			vpt0 = D3DXVECTOR3(0.0f, (float)pCurCtrl->m_ptMouse.Getpt().y, 0.0f);
			bCheck = true;
		}
		else
		{
			vpt1 = D3DXVECTOR3(0.0f, (float)pCurCtrl->m_ptMouse.Getpt().y, 0.0f);

			pCurCtrl->m_vRot.z += (vpt1.y - vpt0.y) * Timer::SPF;
			InfoForm::Get()->SetDlgItemTextW(Info_RotX, std::to_wstring(D3DXToDegree(pCurCtrl->m_vRot.x)).data());
			InfoForm::Get()->SetDlgItemTextW(Info_RotY, std::to_wstring(D3DXToDegree(pCurCtrl->m_vRot.y)).data());
			InfoForm::Get()->SetDlgItemTextW(Info_RotZ, std::to_wstring(D3DXToDegree(pCurCtrl->m_vRot.z)).data());
			bCheck = false;
		}
	}
	if (m_Type == ROTATE && Input::GetKeyState(EMouseButton::Left) == EKeyState::UP)
	{
		vpt0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vpt1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bCheck = false;
	}
}
void Sample::ptScaling()
{
	if (pCurCtrl == nullptr) return;
	if (m_Type == SCALE && Input::GetKeyState(EMouseButton::Left) == EKeyState::HOLD)
	{
		if (bCheck == false)
		{
			vpt0 = D3DXVECTOR3((float)pCurCtrl->m_ptMouse.Getpt().x, (float)pCurCtrl->m_ptMouse.Getpt().y, 0.0f);
			bCheck = true;
		}
		else
		{
			vpt1 = D3DXVECTOR3((float)pCurCtrl->m_ptMouse.Getpt().x, (float)pCurCtrl->m_ptMouse.Getpt().y, 0.0f);

			pCurCtrl->m_vScl.x += (vpt1.x - vpt0.x) * Timer::SPF * 10;
			pCurCtrl->m_vScl.y += (vpt1.y - vpt0.y) * Timer::SPF * 10;
			InfoForm::Get()->SetDlgItemTextW(Info_SclX, std::to_wstring(pCurCtrl->m_vScl.x).data());
			InfoForm::Get()->SetDlgItemTextW(Info_SclY, std::to_wstring(pCurCtrl->m_vScl.y).data());
			InfoForm::Get()->SetDlgItemTextW(Info_SclZ, std::to_wstring(pCurCtrl->m_vScl.z).data());
			bCheck = false;
		}
	}
	if (m_Type == SCALE && Input::GetKeyState(EMouseButton::Left) == EKeyState::UP)
	{
		vpt0 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vpt1 = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		bCheck = false;
	}
}
void Sample::KeyTransition()
{
	if (m_Type == TRANS && pCurCtrl != nullptr)
	{
		if (Input::Get().GetKeyState(VK_UP) == EKeyState::HOLD)
		{
			pCurCtrl->m_vPos.y += Timer::SPF * 10.0f;
			UpdateInfo();
		}
		if (Input::Get().GetKeyState(VK_DOWN) == EKeyState::HOLD)
		{
			pCurCtrl->m_vPos.y -= Timer::SPF * 10.0f;
			UpdateInfo();
		}
		if (Input::Get().GetKeyState(VK_RIGHT) == EKeyState::HOLD)
		{
			pCurCtrl->m_vPos.x += Timer::SPF * 10.0f;
			UpdateInfo();
		}
		if (Input::Get().GetKeyState(VK_LEFT) == EKeyState::HOLD)
		{
			pCurCtrl->m_vPos.x -= Timer::SPF * 10.0f;
			UpdateInfo();
		}
	}
}
void Sample::KeyRotation()
{
	if (m_Type == ROTATE && pCurCtrl != nullptr)
	{
		if (Input::Get().GetKeyState(VK_UP) == EKeyState::HOLD)
		{
			pCurCtrl->m_vRot.z += Timer::SPF * 2.0f;
			UpdateInfo();
		}
		if (Input::Get().GetKeyState(VK_DOWN) == EKeyState::HOLD)
		{
			pCurCtrl->m_vRot.z -= Timer::SPF * 2.0f;
			UpdateInfo();
		}
	}
}
void Sample::KeyScaling()
{
	if (m_Type == SCALE && pCurCtrl != nullptr)
	{
		if (Input::Get().GetKeyState(VK_UP) == EKeyState::HOLD)
		{
			pCurCtrl->m_vScl.y += Timer::SPF * 10.0f;
			UpdateInfo();
		}
		if (Input::Get().GetKeyState(VK_DOWN) == EKeyState::HOLD)
		{
			pCurCtrl->m_vScl.y -= Timer::SPF * 10.0f;
			UpdateInfo();
		}
		if (Input::Get().GetKeyState(VK_RIGHT) == EKeyState::HOLD)
		{
			pCurCtrl->m_vScl.x += Timer::SPF * 10.0f;
			UpdateInfo();
		}
		if (Input::Get().GetKeyState(VK_LEFT) == EKeyState::HOLD)
		{
			pCurCtrl->m_vScl.x -= Timer::SPF * 10.0f;
			UpdateInfo();
		}
	}
}
/* ====================================================================== */
/* INIT FRAME RENDER RELEASE */
/* ====================================================================== */
EVENT_LIST Sample::FindPointerFunc(wstring Event)
{
	if (Event == L"EVENT_NONE")
	{
		return EVENT_LIST::EVENT_NONE;
	}
	if (Event == L"EVENT_SHOW")
	{
		return EVENT_LIST::EVENT_SHOW;
	}
	if (Event == L"EVENT_NOT_SHOW")
	{
		return EVENT_LIST::EVENT_NOT_SHOW;
	}
	if (Event == L"EVENT_REVERCE_SHOW")
	{
		return EVENT_LIST::EVENT_REVERSE_SHOW;
	}
	if (Event == L"EVENT_ROTATEZ")
	{
		return EVENT_ROTATEZ;
	}
	if (Event == L"EVENT_SHOW_SCL")
	{
		return EVENT_SHOW_SCL;
	}
	if (Event == L"EVENT_NOTSHOW_SCL")
	{
		return EVENT_NOTSHOW_SCL;
	}
	AfxMessageBox(L"Event가 없어영");
	return EVENT_NONE;
}
wstring Sample::FindPointerFunc(EVENT_LIST Event)
{
	if (Event == EVENT_NONE)
	{
		return L"EVENT_NONE";
	}
	if (Event == EVENT_SHOW)
	{
		return L"EVENT_SHOW";
	}
	if (Event == EVENT_NOT_SHOW)
	{
		return L"EVENT_NOT_SHOW";
	}
	if (Event == EVENT_REVERSE_SHOW)
	{
		return L"EVENT_REVERCE_SHOW";
	}	
	if (Event == EVENT_ROTATEZ)
	{
		return L"EVENT_ROTATEZ";
	}
	if (Event == EVENT_SHOW_SCL)
	{
		return L"EVENT_SHOW_SCL";
	}
	if (Event == EVENT_NOTSHOW_SCL)
	{
		return L"EVENT_NOTSHOW_SCL";
	}
	AfxMessageBox(L"Event가 없어영");
	return L"EVENT_NONE";
}
void Sample::InfoEventInit()
{
	CWnd* wndhover = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_pfEvnetHover);
	InfoForm::Get()->m_pfHover.m_hWnd = wndhover->m_hWnd;
	CWnd* wndpress = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_pfEvnetPress);
	InfoForm::Get()->m_pfPress.m_hWnd = wndpress->m_hWnd;
	CWnd* wndclick = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_pfEvnetClick);
	InfoForm::Get()->m_pfClick.m_hWnd = wndclick->m_hWnd;

	InfoForm::Get()->m_pfHover.AddString(L"EVENT_NONE");
	InfoForm::Get()->m_pfPress.AddString(L"EVENT_NONE");
	InfoForm::Get()->m_pfClick.AddString(L"EVENT_NONE");
	//
	InfoForm::Get()->m_pfHover.AddString(L"EVENT_SHOW");
	InfoForm::Get()->m_pfPress.AddString(L"EVENT_SHOW");
	InfoForm::Get()->m_pfClick.AddString(L"EVENT_SHOW");
	//
	InfoForm::Get()->m_pfHover.AddString(L"EVENT_NOT_SHOW");
	InfoForm::Get()->m_pfPress.AddString(L"EVENT_NOT_SHOW");
	InfoForm::Get()->m_pfClick.AddString(L"EVENT_NOT_SHOW");
	//
	InfoForm::Get()->m_pfHover.AddString(L"EVENT_REVERCE_SHOW");
	InfoForm::Get()->m_pfPress.AddString(L"EVENT_REVERCE_SHOW");
	InfoForm::Get()->m_pfClick.AddString(L"EVENT_REVERCE_SHOW");
	//
	InfoForm::Get()->m_pfHover.AddString(L"EVENT_ROTATEZ");
	InfoForm::Get()->m_pfPress.AddString(L"EVENT_ROTATEZ");
	InfoForm::Get()->m_pfClick.AddString(L"EVENT_ROTATEZ");
	//
	InfoForm::Get()->m_pfHover.AddString(L"EVENT_SHOW_SCL");
	InfoForm::Get()->m_pfPress.AddString(L"EVENT_SHOW_SCL");
	InfoForm::Get()->m_pfClick.AddString(L"EVENT_SHOW_SCL");
	//
	InfoForm::Get()->m_pfHover.AddString(L"EVENT_NOTSHOW_SCL");
	InfoForm::Get()->m_pfPress.AddString(L"EVENT_NOTSHOW_SCL");
	InfoForm::Get()->m_pfClick.AddString(L"EVENT_NOTSHOW_SCL");

}
wstring Sample::FindKeyDownHold(int iKey)
{
	if (iKey == VK_TAB)
		return L"TAB";
	if (iKey == VK_SPACE)
		return L"SPACE";
	if (iKey == VK_RETURN)
		return L"ENTER";
	if (iKey == VK_ESCAPE)
		return L"ESC";

	// 0 - 10
	for (int i = 48; i <= 57; i++)
	{
		char temp = (char)i;
		string retdata;
		retdata.push_back(temp);
		if (iKey == i)
			return JDxHelper::mtow(retdata.data());
	}
	// A - Z
	for (int i = 65; i <= 90; i++)
	{
		char temp = (char)i;
		string retdata;
		retdata.push_back(temp);
		if (iKey == i)
			return JDxHelper::mtow(retdata.data());
	}
	return L"";
}
void Sample::SetKeyDownHold()
{
	// 이외것들
	InfoForm::Get()->m_KeyDown.AddString(L"TAB");
	InfoForm::Get()->m_KeyHold.AddString(L"TAB");
	InfoForm::Get()->m_KeyDown.AddString(L"SPACE");
	InfoForm::Get()->m_KeyHold.AddString(L"SPACE");
	InfoForm::Get()->m_KeyDown.AddString(L"ENTER");
	InfoForm::Get()->m_KeyHold.AddString(L"ENTER");
	InfoForm::Get()->m_KeyDown.AddString(L"ESC");
	InfoForm::Get()->m_KeyHold.AddString(L"ESC");

	// 0 - 10
	for (int i = 48; i <= 57; i++)
	{
		char temp = (char)i;
		string a;
		a.push_back(temp);
		InfoForm::Get()->m_KeyDown.AddString(JDxHelper::mtow(a.data()));
		InfoForm::Get()->m_KeyHold.AddString(JDxHelper::mtow(a.data()));
	}
	// A - Z
	for (int i = 65; i <= 90; i++)
	{
		char temp = (char)i;
		string a;
		a.push_back(temp);
		InfoForm::Get()->m_KeyDown.AddString(JDxHelper::mtow(a.data()));
		InfoForm::Get()->m_KeyHold.AddString(JDxHelper::mtow(a.data()));
	}
}
bool Sample::Init()		noexcept
{	
	// IME
	ime::Get()->Set(m_hWnd);
	// info Event Setting
	InfoEventInit();
	// 폰트 설정
	WriteManager::Get().SetText({ 0, 0 }, L"", D2D1::ColorF::Black, 50, L"휴먼둥근헤드라인");
	//WriteManager::Get().m_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	//WriteManager::Get().m_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	//JState::SetState(DxManager::GetDevice());
	/* 윈도핸들 지정안해주면 null임 왜인진모르겠음 */
	CWnd* wnd = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_SpriteListBox);
	InfoForm::Get()->m_pSpriteList.m_hWnd = wnd->m_hWnd;
	CWnd* turnX = (CWnd*)ParticleForm::Get()->GetDlgItem(P_TurnX);
	CWnd* turnY = (CWnd*)ParticleForm::Get()->GetDlgItem(P_TurnY);
	CWnd* turnZ = (CWnd*)ParticleForm::Get()->GetDlgItem(P_TurnZ);
	ParticleForm::Get()->m_pTurnX.m_hWnd = turnX->m_hWnd;
	ParticleForm::Get()->m_pTurnY.m_hWnd = turnY->m_hWnd;
	ParticleForm::Get()->m_pTurnZ.m_hWnd = turnZ->m_hWnd;
	////
	CWnd* Hierarchy = (CWnd*)HierarchyForm::Get()->GetDlgItem(IDC_HierarchyTree);
	HierarchyForm::Get()->m_HierarchyTree.m_hWnd = Hierarchy->m_hWnd;
	/////
	CWnd* infoRender = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_bRender);
	InfoForm::Get()->m_bRender.m_hWnd = infoRender->m_hWnd;
	/////
	CWnd* infoGameMode = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_GameMode);
	InfoForm::Get()->m_GameMode.m_hWnd = infoGameMode->m_hWnd;
	/////
	CWnd* infoVHType = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_VHType);
	InfoForm::Get()->m_VHType.m_hWnd = infoVHType->m_hWnd;
	InfoForm::Get()->m_VHType.AddString(L"Vertical");
	InfoForm::Get()->m_VHType.AddString(L"Horizontal");
	////
	CWnd* infoSpriteType = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_SpriteType);
	InfoForm::Get()->m_SpriteType.m_hWnd = infoSpriteType->m_hWnd;
	InfoForm::Get()->m_SpriteType.AddString(L"TEXSPRITE");
	InfoForm::Get()->m_SpriteType.AddString(L"UVSPRITE");
	////
	CWnd* SpriteLoop = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_SpriteLoop);
	InfoForm::Get()->m_pSpriteLoop.m_hWnd = SpriteLoop->m_hWnd;
	////
	CWnd* keydown = (CWnd*)InfoForm::Get()->GetDlgItem(Info_KeyDown);
	InfoForm::Get()->m_KeyDown.m_hWnd = keydown->m_hWnd;
	CWnd* keyhold = (CWnd*)InfoForm::Get()->GetDlgItem(Info_KeyHold);
	InfoForm::Get()->m_KeyHold.m_hWnd = keyhold->m_hWnd;
	////
	CWnd* PassWord = (CWnd*)InfoForm::Get()->GetDlgItem(IDC_PassWord);
	InfoForm::Get()->m_PassWord.m_hWnd = PassWord->m_hWnd;
	SetKeyDownHold();
	////
	CWnd* infoAlign = (CWnd*)InfoForm::Get()->GetDlgItem(Info_Align);
	InfoForm::Get()->m_Align.m_hWnd = infoAlign->m_hWnd;
	InfoForm::Get()->m_Align.AddString(L"LEFT");
	InfoForm::Get()->m_Align.AddString(L"CENTER");
	InfoForm::Get()->m_Align.AddString(L"RIGHT");

	pRoot->Init();
	pRoot->m_objType = EObjType::UI;
	hRoot = HierarchyForm::Get()->m_HierarchyTree.InsertItem(pRoot->m_NodeName.data(), 0, 1, TVI_ROOT, TVI_LAST);

	m_Circle.Create(DxManager::GetDevice());
	m_Line.Create(DxManager::GetDevice());
	return true;
}
bool Sample::Frame()	noexcept
{
	m_fSaveElapseTime += Timer::SPF;
	if (m_fSaveElapseTime >= 120.0f)
	{
		SaveData(L"temp");
		m_fSaveElapseTime = 0.0f;
		m_bSaveNotice = true;
	}

	if(InfoForm::Get() != NULL) 
		if(!InfoForm::Get()->m_GameMode.GetCheck())
			Update();
	pRoot->Frame(Timer::SPF, Timer::AccumulateTime);
	return true;
}
bool Sample::Render()	noexcept
{
	//static wstring temp;
	//temp = JIME::Get()->GetStringBuffer();
	//WriteManager::Get().Draw({ 400,300, 800,600 }, temp);
	if (m_bSaveNotice == true)
	{
		m_fSaveNoticeTime += Timer::SPF;
		WriteManager::Get().SetFontSize(50);
		WriteManager::Get().Draw({ 0,0,800, 600 }, L"자동 저장... FileName : temp");
		if (m_fSaveNoticeTime >= 5.0f)
		{
			m_bSaveNotice = false;
			m_fSaveNoticeTime = 0.0f;
		}
	}
	if (m_Type == ROTATE && InfoForm::Get() != nullptr && !InfoForm::Get()->m_GameMode.GetCheck())
	{
		if (pCurCtrl != nullptr)
		{
			D3DXMATRIX world, scl;
			float fValue = 1;
			if (pCurCtrl->m_vScl.x >= pCurCtrl->m_vScl.y)
			{
				fValue = (float)sqrt((pCurCtrl->m_vScl.x * pCurCtrl->m_vScl.x) + (pCurCtrl->m_vScl.x * pCurCtrl->m_vScl.x));
			}
			if (pCurCtrl->m_vScl.x <= pCurCtrl->m_vScl.y)
			{
				fValue = (float)sqrt((pCurCtrl->m_vScl.y * pCurCtrl->m_vScl.y) + (pCurCtrl->m_vScl.y * pCurCtrl->m_vScl.y));
			}
			D3DXMatrixScaling(&scl, fValue, fValue, pCurCtrl->m_vScl.z);
			world = scl * pCurCtrl->m_matRot;
			world._41 = pCurCtrl->m_vPos.x;
			world._42 = pCurCtrl->m_vPos.y;
			world._43 = pCurCtrl->m_vPos.z;
			m_Circle.SetMatrix(&world, &pCurCtrl->m_matView, &pCurCtrl->m_matProj);
			m_Circle.Render(DxManager::Get().GetDContext());
		}
	}
	pRoot->Render(DxManager::Get().GetDContext());
	//if (pCurCtrl != nullptr)
	//{
	//	WriteManager::Get().DrawTextW({ 0,0,800,600 }, to_wstring(pCurCtrl->m_ptMouse.Getpt().x));
	//	WriteManager::Get().DrawTextW({ 0,10,800,600 }, to_wstring(pCurCtrl->m_ptMouse.Getpt().y));
	//}
	if ((m_Type == TRANS || m_Type == SCALE || m_Type == FREE) && InfoForm::Get() != nullptr && !InfoForm::Get()->m_GameMode.GetCheck())
	{
		if (pCurCtrl != nullptr)
		{
			D3DXMATRIX world;
			D3DXMatrixIdentity(&world);
			m_Line.SetMatrix(&world, &pCurCtrl->m_matView, &pCurCtrl->m_matProj);
			m_Line.Draw(DxManager::Get().GetDContext(),
				D3DXVECTOR3(pCurCtrl->m_vPos.x - 5000, pCurCtrl->m_vPos.y, 0),
				D3DXVECTOR3(pCurCtrl->m_vPos.x + 5000, pCurCtrl->m_vPos.y, 0),
				D3DXVECTOR4(1, 0, 0, 1));
			m_Line.SetMatrix(&world, &pCurCtrl->m_matView, &pCurCtrl->m_matProj);
			m_Line.Draw(DxManager::Get().GetDContext(),
				D3DXVECTOR3(pCurCtrl->m_vPos.x, pCurCtrl->m_vPos.y - 5000, 0),
				D3DXVECTOR3(pCurCtrl->m_vPos.x, pCurCtrl->m_vPos.y + 5000, 0),
				D3DXVECTOR4(0, 0, 1, 1));
		}
	}
	return true;
}
bool Sample::Release()	noexcept
{
	Core::isPlaying = false;
	pRoot->Release();
	return true;
}
Sample::Sample()
{
	pRoot = new JPanel(L"Root");
}
Sample::~Sample()
{
}