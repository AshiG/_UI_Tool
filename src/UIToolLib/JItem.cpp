#include "JItem.h"
JItem* JItem::m_pInst = nullptr;
namespace UI
{
	bool JItem::Load(ID3D11Device* pDevice, const TCHAR* FileName)
	{
		FILE* fp = _wfopen(FileName, _T("rt"));
		int iMax = 0;
		TCHAR temp[256] = { 0, };
		TCHAR temp2[256] = { 0, };
		if (fp == nullptr) return false;
		_ftscanf(fp, _T("%s %d"), temp, &iMax);
		for(int i = 0; i < iMax; i++)
		{
			_ftscanf(fp, _T("%s %s"), temp, temp2);
			int iIndex = I_TexMgr.Add(pDevice, temp);
			if (iIndex > -1)
			{
				m_pItemList.insert(pair<wstring, int>(temp2, iIndex));
			}
		}
		fclose(fp);
		return true;
	}
	int JItem::GetKey(wstring ItemName)
	{
		auto ITOR = m_pItemList.find(ItemName);
		if (ITOR == m_pItemList.end()) return -1;
		int iData = (*ITOR).second;
		return iData;
	}
}