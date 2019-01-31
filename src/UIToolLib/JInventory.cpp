#include "JInventory.h"
#include "JSlotManager.h"
#include "JItem.h"
namespace UI
{
	bool JInventory::Create(ID3D11Device* pDevice, int iRow, int iCol, const TCHAR* szBack, const TCHAR* szSlotBack, const char* PSName, const TCHAR* szShaderName)
	{
		m_pBack->Create(pDevice, PSName, szShaderName);
		m_pBack->SetTexture(pDevice, szBack);
		m_pBack->m_pShape->m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		m_pBack->m_pTexture = I_TexMgr.GetPtr(m_pBack->m_pIndexList[txNORMAL]);

		m_strSlotBack = I_TexMgr.GetPtr(I_TexMgr.Add(pDevice, szSlotBack))->m_szName;

		m_iRows = iRow;
		m_iCols = iCol;

		JSlotManager::Get()->AddSlot(this);

		CreateItemSlot(pDevice, iRow, iCol, szSlotBack);
		return true;
	}
	bool JInventory::CreateItemSlot(ID3D11Device* pDevice, int iRow, int iCol, const TCHAR* szSlotBack)
	{
		m_iRows = iRow;
		m_iCols = iCol;
		m_iMaxItem = iRow * iCol;
		for (auto& pItem : m_pItemList)
			SAFE_RELEASE(pItem);
		m_pItemList.clear();
		for (int iColSize = 0; iColSize < iCol; iColSize++)
		{
			for (int iRowSize = 0; iRowSize < iRow; iRowSize++)
			{
				JSlot* AddSlot = new JSlot(L"_Slot_");
				AddSlot->m_Type = INVENTORYSLOT;
				AddSlot->Create(pDevice, szSlotBack, szSlotBack);
				AddSlot->m_pInven = this;
				m_pItemList.push_back(AddSlot);
			}
		}
		return true;
	}
	bool JInventory::AddItem(wstring strItem)
	{
		for (auto& pItem : m_pItemList)
		{
			if (pItem->m_bEmpty)
			{
				int iKey = JItem::Get()->GetKey(strItem);
				if (iKey < 0) return false;
				pItem->m_pItem->m_pIndexList[txNORMAL] = iKey;
				pItem->m_bEmpty = false;
				//m_iNumItem += 1;
				return true;
			}
		}
		return true;
	}
	void JInventory::ClearItem()
	{
		for (auto& pSlot : m_pItemList)
		{
			pSlot->DelItem();
		}
		//m_iNumItem = 0;
		JSlotManager::Get()->DelSlot(this->m_NodeName);
	}
	void JInventory::DelItem()
	{
		if (m_pSelectSlot != nullptr)
		{
			m_pSelectSlot->DelItem();
			m_pSelectSlot = nullptr;
			//m_iNumItem -= 1;
		}
	}
	void JInventory::SortItem()
	{		
		//if (m_bSort) return;

		bool bSort = false;
		for (auto& pSlot : m_pItemList)
		{
			if (!pSlot->m_bEmpty)
			{
				bSort = true;
				break;
			}
		}

		if (!bSort) return;

		for (auto& pFrontSlot : m_pItemList)
		{
			if (!pFrontSlot->m_bEmpty)
				continue;
			for (size_t iBackSlot = m_pItemList.size() - 1; iBackSlot >= 0; iBackSlot--)
			{
				JSlot* pBackSlot = m_pItemList[iBackSlot];
				if (!pBackSlot->m_bEmpty)
				{
					if (iBackSlot + 1 != m_pItemList.size())
					{
						if (pFrontSlot == m_pItemList[iBackSlot + 1])
							return;
					}
					pFrontSlot->AddItem(pBackSlot->m_pItem->m_pIndexList[txNORMAL]);
					pBackSlot->DelItem();
					break;
				}
			}
		}
	}
	void JInventory::UpdateInventoryPos()
	{
		float fOffsetX = ((m_pBack->m_vScl.x * 2.0f) - 2.0f) / m_iRows;
		float fOffsetY = ((m_pBack->m_vScl.y * 2.0f) - 2.0f) / m_iCols;
		float fPosX = m_pBack->m_vPos.x - (fOffsetX * (m_iRows / 2.0f));
		float fPosY = m_pBack->m_vPos.y + (fOffsetY * (m_iCols / 2.0f));
		float fX = fPosX + (fOffsetX / 2.0f);
		float fY = fPosY - (fOffsetY / 2.0f);
		for (int iCol = 0; iCol < m_iCols; iCol++)
		{
			fX = fPosX + (fOffsetX / 2.0f);
			for (int iRow = 0; iRow < m_iRows; iRow++)
			{
				m_pItemList[(iCol * m_iRows) + iRow]->m_vScl.x = (m_pBack->m_vScl.x / m_iRows) - 2.0f;
				m_pItemList[(iCol * m_iRows) + iRow]->m_vScl.y = (m_pBack->m_vScl.y / m_iCols) - 2.0f;

				m_pItemList[(iCol * m_iRows) + iRow]->m_vPos.x = fX;// fX;
				m_pItemList[(iCol * m_iRows) + iRow]->m_vPos.y = fY;//fY;

				fX += fOffsetX;
			}
			fY -= fOffsetY;
		}
		/*for (auto& pItem : m_pItemList)
		{
			pItem->m_vScl.x = m_pBack->m_vScl.x / m_iRows;
			pItem->m_vScl.y = m_pBack->m_vScl.y / m_iCols;
		}*/
	}
	void JInventory::Update()
	{
		if (m_bUpdate)
		{
			UpdateInventoryPos();
			//m_bUpdate = false;
		}
		m_pBack->m_vPos = this->m_vPos;
		m_pBack->m_vScl = this->m_vScl;
		m_pBack->m_vRot = this->m_vRot;

		if (Input::GetKeyState(EMouseButton::Left) == EKeyState::DOWN)
		{
			for (auto& pSlot : m_pItemList)
			{
				if (JDxHelper::RectInPt(pSlot->m_rt, pSlot->m_ptMouse.Getpt()))
				{
					m_pSelectSlot = pSlot;
					break;
				}
			}
		}
	}
	bool JInventory::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
			if (!m_bRender) return false;
			this->Update();
			m_pBack->Frame(spf, accTime);
			for(auto& pItem : m_pItemList)
				pItem->Frame(spf, accTime);
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JInventory::Render(ID3D11DeviceContext* pContext)noexcept
	{
		if (!m_bRender) return false;
		m_pBack->Render(pContext);
		for(auto& pItem : m_pItemList)
			pItem->Render(pContext);
		JPanel::Render(pContext);
		return true;
	}
	bool JInventory::Release()noexcept
	{
		m_pBack->Release();
		for (auto& pItem : m_pItemList)
		{
			pItem->Release();
			SAFE_DELETE(pItem);
		}
		SAFE_DELETE(m_pBack)
		JPanel::Release();
		return true;
	}
}