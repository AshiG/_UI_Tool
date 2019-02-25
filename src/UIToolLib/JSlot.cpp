#include "JSlot.h"
#include "JInventory.h"
#include "JSlotManager.h"
#include "JItem.h"
namespace UI
{
	bool JSlot::Create(ID3D11Device* pDevice, const TCHAR* szBack, const TCHAR* szFront, const char* PSName, const TCHAR* szShaderName)
	{
		m_pBack->Create(pDevice, PSName, szShaderName);
		m_pItem->Create(pDevice, PSName, szShaderName);
		m_pBack->SetTexture(pDevice, szBack);
		m_pItem->SetTexture(pDevice, szFront);
		m_pBack->m_pShape->m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		m_pItem->m_pShape->m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		m_pBack->m_pTexture = I_TexMgr.GetPtr(m_pBack->m_pIndexList[txNORMAL]);
		m_pItem->m_pTexture = I_TexMgr.GetPtr(m_pItem->m_pIndexList[txNORMAL]);

		//m_pItem->m_pShape->m_cbData.vColor = JDxHelper::vRand(D3DXVECTOR4(0, 0, 0, 1), D3DXVECTOR4(1, 1, 1, 1));
		if (m_Type == SLOT)
			JSlotManager::Get()->AddSlot(this);
		//m_bEmpty = JDxHelper::bRand();
		return true;
	}
	bool JSlot::Empty()
	{
		return m_bEmpty;
	}
	bool JSlot::AddItem(wstring strItem)
	{
		if (m_bEmpty)
		{
			int iKey = JItem::Get()->GetKey(strItem);
			if (iKey < 0) return false;
			m_pItem->m_pIndexList[txNORMAL] = iKey;
			m_bEmpty = false;
			
			return true;
		}
		return false;
	}
	bool JSlot::AddItem(const int itxItem)
	{
		if (m_bEmpty)
		{		
			m_pItem->m_pIndexList[txNORMAL] = itxItem;
			m_bEmpty = false;
			return true;
		}
		return false;
	}
	bool JSlot::DelItem()
	{
		if (!m_bEmpty)
		{
			m_pItem->m_pIndexList[txNORMAL] = -1;
			m_bEmpty = true;
			//JSlotManager::Get()->DelSlot(this->m_NodeName);
			return true;
		}
		return false;
	}
	JPanel* JSlot::FindSlot(list<JPanel*> pSlotList)
	{
		for (auto& pSlot : pSlotList)
		{
			if (pSlot->m_Type == SLOT)
			{
				if (JDxHelper::RectInPt(pSlot->m_rt, pSlot->m_ptMouse.Getpt()))
				{
					return pSlot;
				}
			}
			else if (pSlot->m_Type == INVENTORY)
			{
				JInventory* pInven = (JInventory*)pSlot;
				for (auto& pInvenList : pInven->m_pItemList)
				{
					if (JDxHelper::RectInPt(pInvenList->m_rt, pInvenList->m_ptMouse.Getpt()))
					{
						return pInvenList;
					}
				}
			}
		}
		return nullptr;
	}
	void JSlot::Update()
	{
		m_pBack->m_pTexture = I_TexMgr.GetPtr(m_pBack->m_pIndexList[txNORMAL]);
		if (m_pItem->m_pIndexList[txNORMAL] < 0)
		{
			m_pItem->m_bRender = false;
		}
		else
		{
			m_pItem->m_bRender = true;
			m_pItem->m_pTexture = I_TexMgr.GetPtr(m_pItem->m_pIndexList[txNORMAL]);
		}
		// Item이 있을때
		if (!m_bEmpty)
		{
			m_pItem->m_bRender = true;

			if (Input::GetKeyState(EMouseButton::Left) == EKeyState::DOWN)
			{
				if (JDxHelper::RectInPt(m_pItem->m_rt, m_pItem->m_ptMouse.Getpt()))
				{
					m_bDrag = true;
				}
			}
			if (Input::GetKeyState(EMouseButton::Left) == EKeyState::HOLD)
			{
				if (m_bDrag)
				{
					m_pItem->m_vPos.z = -10;
					m_pItem->m_vPos.x = m_ptMouse.Getpt().x;
					m_pItem->m_vPos.y = m_ptMouse.Getpt().y;
				}
			}
			else
			{
				m_pItem->m_vPos.z = 0;
				m_pItem->m_vPos = m_pBack->m_vPos = this->m_vPos;
			}
			if (Input::GetKeyState(EMouseButton::Left) == EKeyState::UP)
			{
				if (m_bDrag)
				{
					m_bDrag = false;
					JSlot* pCarry = nullptr;
					pCarry = (JSlot*)FindSlot(*(JSlotManager::Get()->GetList()));
					if (pCarry != nullptr)
					{
						if (pCarry->m_bEmpty)
						{
							//if (pCarry->m_Type == INVENTORYSLOT)
							//	pCarry->m_pInven->m_bSort = false;
							
							pCarry->m_bEmpty = false;
							pCarry->m_pItem->m_pIndexList[txNORMAL] = this->m_pItem->m_pIndexList[txNORMAL];
							//pCarry->m_pItem->m_pShape->m_cbData.vColor = this->m_pItem->m_pShape->m_cbData.vColor;

							this->m_pItem->m_pIndexList[txNORMAL] = -1;
							this->m_pItem->m_pTexture = nullptr;
							this->m_bEmpty = true;
						}
						else
						{
							int pSwap = pCarry->m_pItem->m_pIndexList[txNORMAL];
							pCarry->m_pItem->m_pIndexList[txNORMAL] = this->m_pItem->m_pIndexList[txNORMAL];
							this->m_pItem->m_pIndexList[txNORMAL] = pSwap;

							//D3DXVECTOR4 vSwap = pCarry->m_pItem->m_pShape->m_cbData.vColor;
							//pCarry->m_pItem->m_pShape->m_cbData.vColor = this->m_pItem->m_pShape->m_cbData.vColor;
							//this->m_pItem->m_pShape->m_cbData.vColor = vSwap;
						}
					}
				}
			}
			m_pBack->m_vScl = this->m_vScl;
			m_pItem->m_vScl.x = m_pBack->m_vScl.x - 3.0f;
			m_pItem->m_vScl.y = m_pBack->m_vScl.y - 3.0f;
			m_pItem->m_vRot = m_pBack->m_vRot = this->m_vRot;
		}
		else
		{
			m_pItem->m_bRender = false;
			m_pItem->m_vPos = m_pBack->m_vPos = this->m_vPos;
			m_pBack->m_vScl = this->m_vScl;
			m_pItem->m_vScl.x = m_pBack->m_vScl.x - 3.0f;
			m_pItem->m_vScl.y = m_pBack->m_vScl.y - 3.0f;
			m_pItem->m_vRot = m_pBack->m_vRot = this->m_vRot;
		}
		//if (m_pShape->Hovered(m_rt, m_ptMouse.Getpt()))
		//{
		//	if (EventHover.first != nullptr && m_bEvent)
		//		EventHover.first(EventHover.second);
		//}
		//if (m_pShape->Pressed(m_rt, m_ptMouse.Getpt()))
		//{
		//	if (EventPress.first != nullptr && m_bEvent)
		//		EventPress.first(EventPress.second);
		//}
		//if (m_pShape->Clicked(m_rt, m_ptMouse.Getpt()))
		//{
		//	if (EventClick.first != nullptr && m_bEvent)
		//		EventClick.first(EventClick.second);
		//}
		//JPanel::Update();
	}
	bool JSlot::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
			if (!m_bRender) return false;
			this->Update();
			m_pBack->Frame(spf, accTime);
			m_pItem->Frame(spf, accTime);
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JSlot::Render(ID3D11DeviceContext* pContext)noexcept
	{
		if (!m_bRender) return false;
		m_pBack->Render(pContext);
		m_pItem->Render(pContext);
		JPanel::Render(pContext);
		return true;
	}
	bool JSlot::Release()noexcept
	{
		m_pBack->Release();
		m_pItem->Release();
		SAFE_DELETE(m_pBack);
		SAFE_DELETE(m_pItem);
		JPanel::Release();
		return true;
	}
}