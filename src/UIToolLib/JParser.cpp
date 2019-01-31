#include "JParser.h"
#include "JSlotManager.h"
#include "JItem.h"
#include "DxManager.h"
namespace UI
{
	bool JParser::FileLoad(ID3D11Device* pDevice, const TCHAR* szFileName, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		wstring FileName = szFileName;
		FileName += L"_t";
		JToken::LoadFile(FileName.data());
		//JToken::LoadFile(szFileName);
		m_pRoot = &pRoot;

		JSlotManager::Get()->GetList()->clear();
		JItem::Get()->m_pItemList.clear();
		JItem::Get()->Load(DxManager::GetDevice());

		if ((iLine = FindToken("Type")) >= 0)
		{
			string szTemp;
			if ((iLine = FindToken("NodeName")) > 0)
			{
				string nodename;
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", szTemp.c_str(), nodename.c_str());
				pRoot.m_NodeName = UI::JDxHelper::mtow(nodename.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				string parentname;
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", szTemp.c_str(), parentname.c_str());
				pRoot.m_ParentName = UI::JDxHelper::mtow(parentname.data());

			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", szTemp.c_str(), &pRoot.m_vPos.x, &pRoot.m_vPos.y, &pRoot.m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", szTemp.c_str(), &pRoot.m_vRot.x, &pRoot.m_vRot.y, &pRoot.m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", szTemp.c_str(), &pRoot.m_vScl.x, &pRoot.m_vScl.y, &pRoot.m_vScl.z);
			}
		}

		while ((iLine = FindToken("Type")) > 0)
		{
			char szTemp[256] = { 0, };
			int iType = 0;
			sscanf(m_pTokenList[iLine].c_str(), "%s %d", szTemp, &iType);
			switch (iType)
			{
			case UI::PANEL:
			{
				PanelRead(pRoot);
			}break;
			case UI::BUTTON:
			{
				ButtonRead(pDevice, pRoot, plusPath);
			}break;
			case UI::CHECK:
			{
				CheckRead(pDevice, pRoot, plusPath);
			}break;
			case UI::PROGRESS:
			{
				ProgressRead(pDevice, pRoot, plusPath);
			}break;
			case UI::SLIDER:
			{
				SliderRead(pDevice, pRoot, plusPath);
			}break;
			case UI::SPRITE:
			{
				SpriteRead(pDevice, pRoot, plusPath);
			}break;
			case UI::TEXT:
			{
				TextRead(pDevice, pRoot, plusPath);
			}break;
			case UI::PARTICLE:
			{
				ParticleRead(pDevice, pRoot, plusPath);
			}break;
			case UI::LIST:
			{
				ListRead(pDevice, pRoot, plusPath);
			}break;
			case UI::EDIT:
			{
				EditRead(pDevice, pRoot, plusPath);
			}break;
			case UI::IMAGE:
			{
				ImageRead(pDevice, pRoot, plusPath);
			}break;
			case UI::SLOT:
			{
				SlotRead(pDevice, pRoot, plusPath);
			}break;
			case UI::INVENTORY:
			{
				InventoryRead(pDevice, pRoot, plusPath);
			}break;
			}
		}
		EventLoad(pRoot);
		return true;
	}
	bool JParser::EventLoad(JPanel& pRoot)
	{
		EventBind(pRoot);

		for (auto iC = pRoot.m_pChildList.begin(); iC != pRoot.m_pChildList.end(); iC++)
		{
			EventLoad(*(*iC));
		}
		return true;
	}
	bool JParser::EventBind(JPanel& pRoot)
	{
		// == EVENT_SHOW
		if (pRoot.m_pfHover == EVENT_SHOW)
		{
			pRoot.EventHover.first = UI::E_SHOW;
			if (pRoot.m_vpHover == L"")
				pRoot.EventHover.second = this;
			else
				pRoot.EventHover.second = m_pRoot->find_child(pRoot.m_vpHover);
		}
		if (pRoot.m_pfPress == EVENT_SHOW)
		{
			pRoot.EventPress.first = UI::E_SHOW;
			if (pRoot.m_vpPress == L"")
				pRoot.EventPress.second = this;
			else
				pRoot.EventPress.second = m_pRoot->find_child(pRoot.m_vpPress);
		}
		if (pRoot.m_pfClick == EVENT_SHOW)
		{
			pRoot.EventClick.first = UI::E_SHOW;
			if (pRoot.m_vpClick == L"")
				pRoot.EventClick.second = this;
			else
				pRoot.EventClick.second = m_pRoot->find_child(pRoot.m_vpClick);
		}
		// EVENT_NOT_SHOW
		if (pRoot.m_pfHover == EVENT_NOT_SHOW)
		{
			pRoot.EventHover.first = UI::E_NOTSHOW;
			if (pRoot.m_vpHover == L"")
				pRoot.EventHover.second = this;
			else
				pRoot.EventHover.second = m_pRoot->find_child(pRoot.m_vpHover);
		}
		if (pRoot.m_pfPress == EVENT_NOT_SHOW)
		{
			pRoot.EventPress.first = UI::E_NOTSHOW;
			if (pRoot.m_vpPress == L"")
				pRoot.EventPress.second = this;
			else
				pRoot.EventPress.second = m_pRoot->find_child(pRoot.m_vpPress);
		}
		if (pRoot.m_pfClick == EVENT_NOT_SHOW)
		{
			pRoot.EventClick.first = UI::E_NOTSHOW;
			if (pRoot.m_vpClick == L"")
				pRoot.EventClick.second = this;
			else
				pRoot.EventClick.second = m_pRoot->find_child(pRoot.m_vpClick);
		}
		// EVENT_REVERSE_SHOW
		if (pRoot.m_pfHover == EVENT_REVERSE_SHOW)
		{
			pRoot.EventHover.first = UI::E_REVERSE_SHOW;
			if (pRoot.m_vpHover == L"")
				pRoot.EventHover.second = this;
			else
				pRoot.EventHover.second = m_pRoot->find_child(pRoot.m_vpHover);
		}
		if (pRoot.m_pfPress == EVENT_REVERSE_SHOW)
		{
			pRoot.EventPress.first = UI::E_REVERSE_SHOW;
			if (pRoot.m_vpPress == L"")
				pRoot.EventPress.second = this;
			else
				pRoot.EventPress.second = m_pRoot->find_child(pRoot.m_vpPress);
		}
		if (pRoot.m_pfClick == EVENT_REVERSE_SHOW)
		{
			pRoot.EventClick.first = UI::E_REVERSE_SHOW;
			if (pRoot.m_vpClick == L"")
				pRoot.EventClick.second = this;
			else
				pRoot.EventClick.second = m_pRoot->find_child(pRoot.m_vpClick);
		}
		// EVENT_ROTATEZ
		if (pRoot.m_pfHover == EVENT_ROTATEZ)
		{
			pRoot.EventHover.first = UI::E_ROTATEZ;
			if (pRoot.m_vpHover == L"")
				pRoot.EventHover.second = this;
			else
				pRoot.EventHover.second = m_pRoot->find_child(pRoot.m_vpHover);
		}
		if (pRoot.m_pfPress == EVENT_ROTATEZ)
		{
			pRoot.EventPress.first = UI::E_ROTATEZ;
			if (pRoot.m_vpPress == L"")
				pRoot.EventPress.second = this;
			else
				pRoot.EventPress.second = m_pRoot->find_child(pRoot.m_vpPress);
		}
		if (pRoot.m_pfClick == EVENT_ROTATEZ)
		{
			pRoot.EventClick.first = UI::E_ROTATEZ;
			if (pRoot.m_vpClick == L"")
				pRoot.EventClick.second = this;
			else
				pRoot.EventClick.second = m_pRoot->find_child(pRoot.m_vpClick);
		}
		// EVENT_SHOW_SCL
		if (pRoot.m_pfHover == EVENT_SHOW_SCL)
		{
			pRoot.EventHover.first = UI::E_SHOW_SCL;
			if (pRoot.m_vpHover == L"")
				pRoot.EventHover.second = this;
			else
				pRoot.EventHover.second = m_pRoot->find_child(pRoot.m_vpHover);
		}
		if (pRoot.m_pfPress == EVENT_SHOW_SCL)
		{
			pRoot.EventPress.first = UI::E_SHOW_SCL;
			if (pRoot.m_vpPress == L"")
				pRoot.EventPress.second = this;
			else
				pRoot.EventPress.second = m_pRoot->find_child(pRoot.m_vpPress);
		}
		if (pRoot.m_pfClick == EVENT_SHOW_SCL)
		{
			pRoot.EventClick.first = UI::E_SHOW_SCL;
			if (pRoot.m_vpClick == L"")
				pRoot.EventClick.second = this;
			else
				pRoot.EventClick.second = m_pRoot->find_child(pRoot.m_vpClick);
		}
		// EVENT_NOTSHOW_SCL
		if (pRoot.m_pfHover == EVENT_NOTSHOW_SCL)
		{
			pRoot.EventHover.first = UI::E_NOTSHOW_SCL;
			if (pRoot.m_vpHover == L"")
				pRoot.EventHover.second = this;
			else
				pRoot.EventHover.second = m_pRoot->find_child(pRoot.m_vpHover);
		}
		if (pRoot.m_pfPress == EVENT_NOTSHOW_SCL)
		{
			pRoot.EventPress.first = UI::E_NOTSHOW_SCL;
			if (pRoot.m_vpPress == L"")
				pRoot.EventPress.second = this;
			else
				pRoot.EventPress.second = m_pRoot->find_child(pRoot.m_vpPress);
		}
		if (pRoot.m_pfClick == EVENT_NOTSHOW_SCL)
		{
			pRoot.EventClick.first = UI::E_NOTSHOW_SCL;
			if (pRoot.m_vpClick == L"")
				pRoot.EventClick.second = this;
			else
				pRoot.EventClick.second = m_pRoot->find_child(pRoot.m_vpClick);
		}
		return true;
	}
	void JParser::PanelRead(JPanel& pRoot)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		JPanel* pPanel = new JPanel(L"TempPanel");
		//if ((iLine = FindToken("Type")) > 0)
		{
			string szTemp;
			if ((iLine = FindToken("NodeName")) > 0)
			{
				string nodename;
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pPanel->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				string parentname;
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pPanel->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pPanel->m_pKeyDown, &pPanel->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pPanel->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pPanel->m_vPos.x, &pPanel->m_vPos.y, &pPanel->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pPanel->m_vRot.x, &pPanel->m_vRot.y, &pPanel->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pPanel->m_vScl.x, &pPanel->m_vScl.y, &pPanel->m_vScl.z);
			}
		}
		pRoot.find_child(pPanel->m_ParentName)->push_child(pPanel);
		pPanel->m_pRoot = m_pRoot;
		//pRoot.push_child(pPanel);
	}
	void JParser::ButtonRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szNormal, szHover, szPress;
		JButtonCtrl* pBtn = new JButtonCtrl(L"TempBtn");
		D3DXVECTOR4 vColor = D3DXVECTOR4(1,1,1,1);
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pBtn->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pBtn->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pBtn->m_pKeyDown, &pBtn->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pBtn->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pBtn->m_vPos.x, &pBtn->m_vPos.y, &pBtn->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pBtn->m_vRot.x, &pBtn->m_vRot.y, &pBtn->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pBtn->m_vScl.x, &pBtn->m_vScl.y, &pBtn->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(), 
					&vColor.x, 
					&vColor.y,
					&vColor.z, 
					&vColor.w);
			}
			if ((iLine = FindToken("tx_Normal")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szNormal = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("tx_Hover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szHover = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("tx_Press")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szPress = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pBtn->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pBtn->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pBtn->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pBtn->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pBtn->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pBtn->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pBtn->Create(pDevice, szNormal.data(), szHover.data(), szPress.data());
		pBtn->m_pShape->m_cbData.vColor = vColor;
		pRoot.find_child(pBtn->m_ParentName)->push_child(pBtn);
		pBtn->m_pRoot = m_pRoot;
		//pRoot.push_child(pBtn);
	}
	void JParser::CheckRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szDisable, szEnable;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JCheckCtrl* pChk = new JCheckCtrl(L"TempChk");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pChk->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pChk->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pChk->m_pKeyDown, &pChk->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pChk->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pChk->m_vPos.x, &pChk->m_vPos.y, &pChk->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pChk->m_vRot.x, &pChk->m_vRot.y, &pChk->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pChk->m_vScl.x, &pChk->m_vScl.y, &pChk->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("tx_Disable")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szDisable = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("tx_Enable")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szEnable = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pChk->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pChk->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pChk->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pChk->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pChk->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pChk->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pChk->Create(pDevice, szEnable.data(), szDisable.data());
		pChk->m_pShape->m_cbData.vColor = vColor;
		pRoot.find_child(pChk->m_ParentName)->push_child(pChk);
		pChk->m_pRoot = m_pRoot;
		//pRoot.push_child(pChk);
	}
	void JParser::ProgressRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szBack, szFront;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JProgressBar* pProg = new JProgressBar(L"TempProgress");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("VHType")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pProg->m_VHType);
			}
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pProg->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pProg->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pProg->m_pKeyDown, &pProg->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pProg->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pProg->m_vPos.x, &pProg->m_vPos.y, &pProg->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pProg->m_vRot.x, &pProg->m_vRot.y, &pProg->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pProg->m_vScl.x, &pProg->m_vScl.y, &pProg->m_vScl.z);
			}
			if ((iLine = FindToken("SubScale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), 
					&pProg->m_pFrontGround->m_vScl.x, 
					&pProg->m_pFrontGround->m_vScl.y, 
					&pProg->m_pFrontGround->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("tx_BackGround")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szBack = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("tx_FrontGround")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szFront = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pProg->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pProg->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pProg->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pProg->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pProg->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pProg->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pProg->Create(pDevice, szBack.data(), szFront.data());
		pProg->m_pFrontGround->m_pShape->m_cbData.vColor = vColor;
		pProg->m_pBackGround->m_pShape->m_cbData.vColor = vColor;
		pRoot.find_child(pProg->m_ParentName)->push_child(pProg);
		pProg->m_pRoot = m_pRoot;
		//pRoot.push_child(pProg);
	}
	void JParser::SliderRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szBar, szHandle;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JSliderCtrl* pSlider = new JSliderCtrl(L"TempSlider");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("VHType")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSlider->m_VHType);
			}
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSlider->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSlider->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pSlider->m_pKeyDown, &pSlider->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSlider->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSlider->m_vPos.x, &pSlider->m_vPos.y, &pSlider->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSlider->m_vRot.x, &pSlider->m_vRot.y, &pSlider->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSlider->m_vScl.x, &pSlider->m_vScl.y, &pSlider->m_vScl.z);
			}
			if ((iLine = FindToken("SubScale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(),
					&pSlider->m_pSliderHandle->m_vScl.x,
					&pSlider->m_pSliderHandle->m_vScl.y,
					&pSlider->m_pSliderHandle->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("tx_Bar")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szBar = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("tx_Handle")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szHandle = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSlider->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSlider->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSlider->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSlider->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSlider->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSlider->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pSlider->Create(pDevice, szBar.data(), szHandle.data());
		pSlider->m_pSliderBar->m_pShape->m_cbData.vColor = vColor;
		pSlider->m_pSliderHandle->m_pShape->m_cbData.vColor = vColor;
		pRoot.find_child(pSlider->m_ParentName)->push_child(pSlider);
		pSlider->m_pRoot = m_pRoot;
		//pRoot.push_child(pSlider);
	}
	void JParser::SpriteRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		T_STR_VECTOR strlist;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JSpriteCtrl* pSprite = new JSpriteCtrl(L"TempSprite");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("SpriteType")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSprite->m_SpriteType);
			}
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSprite->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSprite->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pSprite->m_pKeyDown, &pSprite->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSprite->m_bRender);
			}
			if ((iLine = FindToken("bLoop")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSprite->m_bLoop);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSprite->m_vPos.x, &pSprite->m_vPos.y, &pSprite->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSprite->m_vRot.x, &pSprite->m_vRot.y, &pSprite->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSprite->m_vScl.x, &pSprite->m_vScl.y, &pSprite->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("AnimTime")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f", temp0.c_str(), &pSprite->m_fAnimTime);
			}
			if ((iLine = FindToken("AnimUV")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pSprite->m_iRows, &pSprite->m_iCols);
			}
			if ((iLine = FindToken("SPRITESTART")) > 0)
			{
				int iTexList;
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &iTexList);
				for (int itxSize = 0; itxSize < iTexList; itxSize++)
				{
					sscanf(m_pTokenList[iLine + itxSize + 1].c_str(), "%s", temp0.c_str());
					strlist.push_back(plusPath + UI::JDxHelper::mtow(temp0.data()));
				}
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSprite->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSprite->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSprite->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSprite->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSprite->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSprite->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pSprite->Create(pDevice,pSprite->m_fAnimTime, strlist);
		pSprite->m_pShape->m_cbData.vColor = vColor;
		pSprite->SetSpriteType(pSprite->m_SpriteType, pSprite->m_iRows, pSprite->m_iCols);
		pRoot.find_child(pSprite->m_ParentName)->push_child(pSprite);
		pSprite->m_pRoot = m_pRoot;
		//pRoot.push_child(pSprite);
	}
	void JParser::TextRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		wstring txtdata;
		temp0.resize(256); temp1.resize(256);
		wstring szNormal, szHover, szPress, sztext;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JTextCtrl* pText = new JTextCtrl(L"TempText");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pText->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pText->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pText->m_pKeyDown, &pText->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pText->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pText->m_vPos.x, &pText->m_vPos.y, &pText->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pText->m_vRot.x, &pText->m_vRot.y, &pText->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pText->m_vScl.x, &pText->m_vScl.y, &pText->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("Align")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pText->m_Align);
			}
			if ((iLine = FindToken("strText")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				sztext = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("TextSize")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f", temp0.c_str(), &pText->m_fSize);
			}
			if ((iLine = FindToken("tx_Normal")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szNormal = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("tx_Hover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szHover = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("tx_Press")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szPress = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pText->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pText->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pText->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pText->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pText->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pText->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pText->Create(pDevice, sztext, pText->m_fSize, szNormal.data(), szHover.data(), szPress.data());
		pText->m_pShape->m_cbData.vColor = vColor;
		//pText->Create(pDevice, sztext, 15, szNormal.data(), szHover.data(), szPress.data());
		pRoot.find_child(pText->m_ParentName)->push_child(pText);
		pText->m_pRoot = m_pRoot;
		//pRoot.push_child(pText);
	}
	void JParser::ParticleRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		T_STR_VECTOR strlist;
		JParticleSystem* pParticle = new JParticleSystem(L"TempParticle");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("SpriteType")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pParticle->m_pSprite->m_SpriteType);
			}
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pParticle->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pParticle->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pParticle->m_pKeyDown, &pParticle->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pParticle->m_bRender);
			}
			if ((iLine = FindToken("bLoop")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pParticle->m_pSprite->m_bLoop);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pParticle->m_vPos.x, &pParticle->m_vPos.y, &pParticle->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pParticle->m_vRot.x, &pParticle->m_vRot.y, &pParticle->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pParticle->m_vScl.x, &pParticle->m_vScl.y, &pParticle->m_vScl.z);
			}
			if ((iLine = FindToken("AnimTime")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f", temp0.c_str(), &pParticle->m_pSprite->m_fAnimTime);
			}
			if ((iLine = FindToken("AnimUV")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pParticle->m_pSprite->m_iRows, 
					&pParticle->m_pSprite->m_iCols);
			}
			if ((iLine = FindToken("ParticleSize")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pParticle->m_iMaxParticle);
			}
			if ((iLine = FindToken("ParticleScale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f", temp0.c_str(), &pParticle->m_fMinScale, &pParticle->m_fMaxScale);
			}
			if ((iLine = FindToken("MinStartPos")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pParticle->m_vMinStartPos.x, &pParticle->m_vMinStartPos.y, &pParticle->m_vMinStartPos.z);
			}
			if ((iLine = FindToken("MaxStartPos")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pParticle->m_vMaxStartPos.x, &pParticle->m_vMaxStartPos.y, &pParticle->m_vMaxStartPos.z);
			}
			if ((iLine = FindToken("TurnDir")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d %d", temp0.c_str(), &pParticle->m_bTurnX, &pParticle->m_bTurnY, &pParticle->m_bTurnZ);
			}
			if ((iLine = FindToken("MinColor")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(), &pParticle->m_vMinColor.x, &pParticle->m_vMinColor.y, &pParticle->m_vMinColor.z, &pParticle->m_vMinColor.w);
			}
			if ((iLine = FindToken("MaxColor")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(), &pParticle->m_vMaxColor.x, &pParticle->m_vMaxColor.y, &pParticle->m_vMaxColor.z, &pParticle->m_vMaxColor.w);
			}
			if ((iLine = FindToken("LifeTime")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f", temp0.c_str(), &pParticle->m_fMinLifeTime, &pParticle->m_fMaxLifeTime);
			}
			if ((iLine = FindToken("MinDir")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pParticle->m_vMinDirection.x, &pParticle->m_vMinDirection.y, &pParticle->m_vMinDirection.z);
			}
			if ((iLine = FindToken("MaxDir")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pParticle->m_vMaxDirection.x, &pParticle->m_vMaxDirection.y, &pParticle->m_vMaxDirection.z);
			}
			if ((iLine = FindToken("MinDirAngle")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(), &pParticle->m_qMinDirAngle.x, &pParticle->m_qMinDirAngle.y, &pParticle->m_qMinDirAngle.z, &pParticle->m_qMinDirAngle.w);
			}
			if ((iLine = FindToken("MaxDirAngle")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(), &pParticle->m_qMaxDirAngle.x, &pParticle->m_qMaxDirAngle.y, &pParticle->m_qMaxDirAngle.z, &pParticle->m_qMaxDirAngle.w);
			}
			if ((iLine = FindToken("MoveSpeed")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f", temp0.c_str(), &pParticle->m_fMinMoveSpeed, &pParticle->m_fMaxMoveSpeed);
			}
			if ((iLine = FindToken("RotSpeed")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f", temp0.c_str(), &pParticle->m_fMinRotateSpeed, &pParticle->m_fMaxRotateSpeed);
			}
			if ((iLine = FindToken("SPRITESTART")) > 0)
			{
				int iTexList;
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &iTexList);
				for (int itxSize = 0; itxSize < iTexList; itxSize++)
				{
					sscanf(m_pTokenList[iLine + itxSize +1].c_str(), "%s", temp0.c_str());
					strlist.push_back(plusPath + UI::JDxHelper::mtow(temp0.data()));
				}
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pParticle->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pParticle->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pParticle->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pParticle->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pParticle->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pParticle->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pParticle->Create(pDevice, pParticle->m_iMaxParticle, pParticle->m_pSprite->m_fAnimTime, strlist);
		pRoot.find_child(pParticle->m_ParentName)->push_child(pParticle);
		pParticle->m_pRoot = m_pRoot;
		//pRoot.push_child(pParticle);
	}
	void JParser::ListRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szNormal;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JListCtrl* pList = new JListCtrl(L"ListCtrl");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pList->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pList->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pList->m_pKeyDown, &pList->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pList->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pList->m_vPos.x, &pList->m_vPos.y, &pList->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pList->m_vRot.x, &pList->m_vRot.y, &pList->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pList->m_vScl.x, &pList->m_vScl.y, &pList->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("Align")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pList->m_Align);
			}
			if ((iLine = FindToken("TextSize")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f", temp0.c_str(), &pList->m_fSize);
			}
			if ((iLine = FindToken("RectColumn")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pList->m_iCols);
			}
			if ((iLine = FindToken("tx_Normal")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szNormal = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pList->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pList->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pList->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pList->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pList->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pList->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pList->Create(pDevice, szNormal.data(), pList->m_fSize, pList->m_iCols);
		pList->m_pShape->m_cbData.vColor = vColor;
		pRoot.find_child(pList->m_ParentName)->push_child(pList);
		pList->m_pRoot = m_pRoot;
	}
	void JParser::EditRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szNormal;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JEditCtrl* pEdit = new JEditCtrl(L"EditCtrl");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pEdit->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pEdit->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pEdit->m_pKeyDown, &pEdit->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pEdit->m_bRender);
			}
			if ((iLine = FindToken("bPrivate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pEdit->m_bPrivate);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pEdit->m_vPos.x, &pEdit->m_vPos.y, &pEdit->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pEdit->m_vRot.x, &pEdit->m_vRot.y, &pEdit->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pEdit->m_vScl.x, &pEdit->m_vScl.y, &pEdit->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("Align")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pEdit->m_Align);
			}
			if ((iLine = FindToken("TextSize")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f", temp0.c_str(), &pEdit->m_fSize);
			}
			if ((iLine = FindToken("TextLength")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pEdit->m_iMaxLength);
			}
			if ((iLine = FindToken("tx_Normal")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szNormal = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pEdit->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pEdit->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pEdit->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pEdit->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pEdit->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pEdit->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pEdit->Create(pDevice, pEdit->m_fSize, szNormal.data());
		pEdit->m_pShape->m_cbData.vColor = vColor;
		pRoot.find_child(pEdit->m_ParentName)->push_child(pEdit);
		pEdit->m_pRoot = m_pRoot;
	}
	void JParser::ImageRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szNormal;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JImageCtrl* pImage = new JImageCtrl(L"JImageCtrl");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pImage->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pImage->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pImage->m_pKeyDown, &pImage->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pImage->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pImage->m_vPos.x, &pImage->m_vPos.y, &pImage->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pImage->m_vRot.x, &pImage->m_vRot.y, &pImage->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pImage->m_vScl.x, &pImage->m_vScl.y, &pImage->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("tx_Normal")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szNormal = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventHover")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pImage->m_pfHover);
			}
			if ((iLine = FindToken("vpEventHover")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pImage->m_vpHover = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventPress")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pImage->m_pfPress);
			}
			if ((iLine = FindToken("vpEventPress")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pImage->m_vpPress = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("pfEventClick")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pImage->m_pfClick);
			}
			if ((iLine = FindToken("vpEventClick")) > 0)
			{
				temp1 = "";
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pImage->m_vpClick = UI::JDxHelper::mtow(temp1.data());
			}
		}
		pImage->Create(pDevice);
		pImage->m_pShape->m_cbData.vColor = vColor;
		pImage->SetTexture(pDevice, szNormal.data());
		pRoot.find_child(pImage->m_ParentName)->push_child(pImage);
		pImage->m_pRoot = m_pRoot;
	}
	void JParser::SlotRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szNormal;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JSlot* pSlot = new JSlot(L"JSlot");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSlot->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pSlot->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pSlot->m_pKeyDown, &pSlot->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pSlot->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSlot->m_vPos.x, &pSlot->m_vPos.y, &pSlot->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSlot->m_vRot.x, &pSlot->m_vRot.y, &pSlot->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pSlot->m_vScl.x, &pSlot->m_vScl.y, &pSlot->m_vScl.z);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("tx_Normal")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szNormal = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
		}
		pSlot->Create(pDevice, szNormal.data(), szNormal.data());
		pSlot->m_pBack->m_pShape->m_cbData.vColor = vColor;
		pRoot.find_child(pSlot->m_ParentName)->push_child(pSlot);
		pSlot->m_pRoot = m_pRoot;
	}
	void JParser::InventoryRead(ID3D11Device* pDevice, JPanel& pRoot, wstring plusPath)
	{
		INT iLine = 0;
		string temp0, temp1;
		temp0.resize(256); temp1.resize(256);
		wstring szNormal, szHover;
		D3DXVECTOR4 vColor = D3DXVECTOR4(1, 1, 1, 1);
		JInventory* pInven = new JInventory(L"JInventory");
		//if ((iLine = FindToken("Type")) > 0)
		{
			if ((iLine = FindToken("NodeName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pInven->m_NodeName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("ParentName")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				pInven->m_ParentName = UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("KeyState")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pInven->m_pKeyDown, &pInven->m_pKeyHold);
			}
			if ((iLine = FindToken("bRender")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d", temp0.c_str(), &pInven->m_bRender);
			}
			if ((iLine = FindToken("Position")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pInven->m_vPos.x, &pInven->m_vPos.y, &pInven->m_vPos.z);
			}
			if ((iLine = FindToken("Rotate")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pInven->m_vRot.x, &pInven->m_vRot.y, &pInven->m_vRot.z);
			}
			if ((iLine = FindToken("Scale")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f", temp0.c_str(), &pInven->m_vScl.x, &pInven->m_vScl.y, &pInven->m_vScl.z);
			}
			if ((iLine = FindToken("RowCol")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %d %d", temp0.c_str(), &pInven->m_iRows, & pInven->m_iCols);
			}
			if ((iLine = FindToken("Color")) > 0)
			{
				sscanf(m_pTokenList[iLine].c_str(), "%s %f %f %f %f", temp0.c_str(),
					&vColor.x,
					&vColor.y,
					&vColor.z,
					&vColor.w);
			}
			if ((iLine = FindToken("tx_Normal")) > 0)
			{
				temp1.clear();
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szNormal = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
			if ((iLine = FindToken("tx_Hover")) > 0)
			{
				temp1.clear();
				sscanf(m_pTokenList[iLine].c_str(), "%s %s", temp0.c_str(), temp1.c_str());
				szHover = plusPath + UI::JDxHelper::mtow(temp1.data());
			}
		}
		pInven->Create(pDevice, pInven->m_iRows, pInven->m_iCols, szNormal.data(), szHover.data());
		pInven->m_pBack->m_pShape->m_cbData.vColor = vColor;
		pRoot.find_child(pInven->m_ParentName)->push_child(pInven);
		pInven->m_pRoot = m_pRoot;
	}
}