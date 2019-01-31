#include "JUIReader.h"
#include "DxManager.h"
#include "JSlotManager.h"
namespace UI
{
	bool JUIReader::RunBinaryRead(JPanel* pRoot, wstring ReadFileName)
	{
		//wstring FileName = ReadFileName;
		//FileName += L"_b";

		//JSlotManager::Get()->GetList()->clear();
		//JItem::Get()->m_pItemList.clear();
		//JItem::Get()->Load(DxManager::GetDevice());

		////m_pStream = _wfopen(FileName.data(), _T("rb"));
		//m_pStream = fopen(JDxHelper::wtom(FileName.data()), "rb");

		//fread(&pRoot, sizeof(JPanel), 1, m_pStream);
		//
		//fclose(m_pStream);
		return true;
	}
}