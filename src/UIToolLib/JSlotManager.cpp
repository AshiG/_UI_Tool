#include "JSlotManager.h"
JSlotManager* JSlotManager::m_pInst = nullptr;
namespace UI
{
	bool JSlotManager::AddSlot(JSlot* pSlot)
	{
		if (pSlot == nullptr) return false;
		m_pSlotList.push_back(pSlot);
		return true;
	}
	bool JSlotManager::AddSlot(JInventory* pInven)
	{
		if (pInven == nullptr) return false;
		m_pSlotList.push_back(pInven);
		return true;
	}
	bool JSlotManager::DelSlot(wstring NodeName)
	{
		for (auto pList = m_pSlotList.begin(); pList != m_pSlotList.end(); pList++)
		{
			if (NodeName == (*pList)->m_NodeName)
			{
				m_pSlotList.erase(pList);
				return true;
			}
		}
		return false;
	}
	list<JPanel*>* JSlotManager::GetList()
	{
		return &m_pSlotList;
	}
}