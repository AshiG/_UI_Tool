#include "JUIWriter.h"
namespace UI
{
	/* =========== */
	/* Binary File */
	/* =========== */
	bool JUIWriter::RunBinaryWrite(JPanel* pRoot, wstring SaveFileName)
	{
		//wstring FileName = SaveFileName;
		//FileName += L"_b";
		//_wsetlocale(LC_ALL, L"kor"); // 쓸때 한글 ?????로 나오는 현상 방지
		//m_pStream = _wfopen(FileName.data(), _T("wb"));
		//fwrite(&pRoot->m_Type, sizeof(UIType), 1, m_pStream);
		//fwrite(&pRoot->m_NodeName, sizeof(wstring), 1, m_pStream);
		//fwrite(&pRoot->m_ParentName, sizeof(wstring), 1, m_pStream);
		//fwrite(&pRoot->GetUITransform(), sizeof(JTransform), 1, m_pStream);
		//BinaryWriteCircuit(pRoot);
		//fclose(m_pStream);
		return true;
	}
	//bool JUIWriter::BinaryWriteCircuit(JPanel* pChild) 
	//{
	//	for (auto iC = pChild->m_pChildList.begin(); iC != pChild->m_pChildList.end(); iC++)
	//	{
	//		JPanel* pPanel = (*iC);
	//		switch (pPanel->m_Type)
	//		{
	//		case PANEL: {
	//			BinaryPanelWrite(pPanel);
	//		}break;
	//		case BUTTON: {
	//			BinaryButtonWrite(pPanel);
	//		}break;
	//		case CHECK: {
	//			BinaryCheckWrite(pPanel);
	//		}break;
	//		case PROGRESS: {
	//			BinaryProgressWrite(pPanel);
	//		}break;
	//		case SLIDER: {
	//			BinarySliderWrite(pPanel);
	//		}break;
	//		case SPRITE: {
	//			BinarySpriteWrite(pPanel);
	//		}break;
	//		case TEXT: {
	//			BinaryTextWrite(pPanel);
	//		}break;
	//		case PARTICLE: {
	//			BinaryParticleWrite(pPanel);
	//		}break;
	//		case LIST: {
	//			BinaryListWrite(pPanel);
	//		}break;
	//		case EDIT: {
	//			BinaryEditWrite(pPanel);
	//		}break;
	//		case IMAGE: {
	//			BinaryImageWrite(pPanel);
	//		}break;
	//		case SLOT: {
	//			BinarySlotWrite(pPanel);
	//		}break;
	//		case INVENTORY: {
	//			BinaryInventoryWrite(pPanel);
	//		}break;
	//		}
	//		WriteCircuit(pPanel); // 순회
	//	}
	//	return true;
	//}
	//void JUIWriter::BinaryPanelWrite(JPanel* pChild) 
	//{
	//	fwrite(&pChild->m_Type, sizeof(UIType), 1, m_pStream);
	//	fwrite(&pChild->m_NodeName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_ParentName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pKeyDown, sizeof(int), 1, m_pStream);
	//	fwrite(&pChild->m_pKeyHold, sizeof(int), 1, m_pStream);
	//	fwrite(&pChild->m_bRender, sizeof(bool), 1, m_pStream);
	//	fwrite(&pChild->GetUITransform(), sizeof(JTransform), 1, m_pStream);
	//}
	//void JUIWriter::BinaryButtonWrite(JPanel* pChild) 
	//{
	//	fwrite(&pChild->m_Type, sizeof(UIType), 1, m_pStream);
	//	fwrite(&pChild->m_NodeName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_ParentName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pKeyDown, sizeof(int), 1, m_pStream);
	//	fwrite(&pChild->m_pKeyHold, sizeof(int), 1, m_pStream);
	//	fwrite(&pChild->m_bRender, sizeof(bool), 1, m_pStream);
	//	fwrite(&pChild->GetUITransform(), sizeof(JTransform), 1, m_pStream);
	//	fwrite(&pChild->m_pShape->m_cbData.vColor, sizeof(D3DXVECTOR4), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pChild->m_pIndexList[txNORMAL])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pChild->m_pIndexList[txHOVER])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pChild->m_pIndexList[txPRESS])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pfHover, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pChild->m_vpHover, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pfPress, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pChild->m_vpPress, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pfClick, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pChild->m_vpClick, sizeof(wstring), 1, m_pStream);
	//}
	//void JUIWriter::BinaryCheckWrite(JPanel* pChild) 
	//{
	//	fwrite(&pChild->m_Type, sizeof(UIType), 1, m_pStream);
	//	fwrite(&pChild->m_NodeName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_ParentName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pKeyDown, sizeof(int), 1, m_pStream);
	//	fwrite(&pChild->m_pKeyHold, sizeof(int), 1, m_pStream);
	//	fwrite(&pChild->m_bRender, sizeof(bool), 1, m_pStream);
	//	fwrite(&pChild->GetUITransform(), sizeof(JTransform), 1, m_pStream);
	//	fwrite(&pChild->m_pShape->m_cbData.vColor, sizeof(D3DXVECTOR4), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pChild->m_pIndexList[txDISABLE])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pChild->m_pIndexList[txENABLE])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pfHover, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pChild->m_vpHover, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pfPress, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pChild->m_vpPress, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pChild->m_pfClick, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pChild->m_vpClick, sizeof(wstring), 1, m_pStream);
	//}
	//void JUIWriter::BinaryProgressWrite(JPanel* pChild) 
	//{
	//	JProgressBar* pProgress = (JProgressBar*)pChild;
	//	fwrite(&pProgress->m_Type, sizeof(UIType), 1, m_pStream);
	//	fwrite(&pProgress->m_VHType, sizeof(VHType), 1, m_pStream);
	//	fwrite(&pProgress->m_NodeName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pProgress->m_ParentName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pProgress->m_pKeyDown, sizeof(int), 1, m_pStream);
	//	fwrite(&pProgress->m_pKeyHold, sizeof(int), 1, m_pStream);
	//	fwrite(&pProgress->m_bRender, sizeof(bool), 1, m_pStream);
	//	fwrite(&pProgress->GetUITransform(), sizeof(JTransform), 1, m_pStream);
	//	fwrite(&pProgress->m_pShape->m_cbData.vColor, sizeof(D3DXVECTOR4), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pProgress->m_pBackGround->m_pIndexList[txNORMAL])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pProgress->m_pFrontGround->m_pIndexList[txNORMAL])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pProgress->m_pfHover, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pProgress->m_vpHover, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pProgress->m_pfPress, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pProgress->m_vpPress, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pProgress->m_pfClick, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pProgress->m_vpClick, sizeof(wstring), 1, m_pStream);
	//}
	//void JUIWriter::BinarySliderWrite(JPanel* pChild) 
	//{
	//	JSliderCtrl* pSlider = (JSliderCtrl*)pChild;
	//	fwrite(&pSlider->m_Type, sizeof(UIType), 1, m_pStream);
	//	fwrite(&pSlider->m_VHType, sizeof(VHType), 1, m_pStream);
	//	fwrite(&pSlider->m_NodeName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pSlider->m_ParentName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pSlider->m_pKeyDown, sizeof(int), 1, m_pStream);
	//	fwrite(&pSlider->m_pKeyHold, sizeof(int), 1, m_pStream);
	//	fwrite(&pSlider->m_bRender, sizeof(bool), 1, m_pStream);
	//	fwrite(&pSlider->GetUITransform(), sizeof(JTransform), 1, m_pStream);
	//	fwrite(&pSlider->m_pShape->m_cbData.vColor, sizeof(D3DXVECTOR4), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pSlider->m_pSliderBar->m_pIndexList[txNORMAL])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&I_TexMgr.GetPtr(pSlider->m_pSliderHandle->m_pIndexList[txNORMAL])->m_szName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pSlider->m_pfHover, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pSlider->m_vpHover, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pSlider->m_pfPress, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pSlider->m_vpPress, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pSlider->m_pfClick, sizeof(EVENT_LIST), 1, m_pStream);
	//	fwrite(&pSlider->m_vpClick, sizeof(wstring), 1, m_pStream);
	//}
	//void JUIWriter::BinarySpriteWrite(JPanel* pChild) 
	//{
	//	JSpriteCtrl* pSprite = (JSpriteCtrl*)pChild;
	//	fwrite(&pSprite->m_Type, sizeof(UIType), 1, m_pStream);
	//	fwrite(&pSprite->m_SpriteType, sizeof(SpriteType), 1, m_pStream);
	//	fwrite(&pSprite->m_NodeName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pSprite->m_ParentName, sizeof(wstring), 1, m_pStream);
	//	fwrite(&pSprite->m_pKeyDown, sizeof(int), 1, m_pStream);
	//	fwrite(&pSprite->m_pKeyHold, sizeof(int), 1, m_pStream);
	//	fwrite(&pSprite->m_bRender, sizeof(bool), 1, m_pStream);
	//	fwrite(&pSprite->m_bLoop, sizeof(bool), 1, m_pStream);
	//	fwrite(&pSprite->GetUITransform(), sizeof(JTransform), 1, m_pStream);
	//	fwrite(&pSprite->m_pShape->m_cbData.vColor, sizeof(D3DXVECTOR4), 1, m_pStream);

	//}
	//void JUIWriter::BinaryTextWrite(JPanel* pChild) {}
	//void JUIWriter::BinaryParticleWrite(JPanel* pChild) {}
	//void JUIWriter::BinaryListWrite(JPanel* pChild) {}
	//void JUIWriter::BinaryEditWrite(JPanel* pChild) {}
	//void JUIWriter::BinaryImageWrite(JPanel* pChild) {}
	//void JUIWriter::BinarySlotWrite(JPanel* pChild) {}
	//void JUIWriter::BinaryInventoryWrite(JPanel* pChild) {}
	/* ========= */
	/* Text File */
	/* ========= */
	bool JUIWriter::RunWrite(JPanel* pRoot, wstring SaveFileName)
	{
		wstring FileName = SaveFileName;
		FileName += L"_t";

		_wsetlocale(LC_ALL, L"kor"); // 쓸때 한글 ?????로 나오는 현상 방지
		m_pStream = _wfopen(FileName.data(), _T("wt"));

		_ftprintf(m_pStream, _T("^Type %s\n"), std::to_wstring(pRoot->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pRoot->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pRoot->m_ParentName.data());

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pRoot->m_vPos.x, pRoot->m_vPos.y, pRoot->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pRoot->m_vRot.x, pRoot->m_vRot.y, pRoot->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pRoot->m_vScl.x, pRoot->m_vScl.y, pRoot->m_vScl.z);

		WriteCircuit(pRoot);

		fclose(m_pStream);
		return true;
	}
	bool JUIWriter::WriteCircuit(JPanel* pChild)
	{
		for (auto iC = pChild->m_pChildList.begin(); iC != pChild->m_pChildList.end(); iC++)
		{
			JPanel* pPanel = (*iC);
			switch (pPanel->m_Type)
			{
			case PANEL:	{
				PanelWrite(pPanel);
			}break;
			case BUTTON:{
				ButtonWrite(pPanel);
			}break;
			case CHECK: {
				CheckWrite(pPanel);
			}break;
			case PROGRESS: {
				ProgressWrite(pPanel);
			}break;
			case SLIDER:			{
				SliderWrite(pPanel);
			}break;
			case SPRITE:			{
				SpriteWrite(pPanel);
			}break;
			case TEXT:			{
				TextWrite(pPanel);
			}break;
			case PARTICLE:			{
				ParticleWrite(pPanel);
			}break;
			case LIST:			{
				ListWrite(pPanel);
			}break;
			case EDIT:			{
				EditWrite(pPanel);
			}break;
			case IMAGE:			{
				ImageWrite(pPanel);
			}break;
			case SLOT:			{
				SlotWrite(pPanel);
			}break;
			case INVENTORY:			{
				InventoryWrite(pPanel);
			}break;
			}

			WriteCircuit(pPanel); // 순회
		}
		return true;
	}
	void JUIWriter::PanelWrite(JPanel* pChild)
	{
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pChild->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pChild->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pChild->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pChild->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pChild->m_vPos.x, pChild->m_vPos.y, pChild->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pChild->m_vRot.x, pChild->m_vRot.y, pChild->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pChild->m_vScl.x, pChild->m_vScl.y, pChild->m_vScl.z);
	}
	void JUIWriter::ButtonWrite(JPanel* pChild)
	{
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pChild->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pChild->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pChild->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pChild->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pChild->m_vPos.x, pChild->m_vPos.y, pChild->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pChild->m_vRot.x, pChild->m_vRot.y, pChild->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pChild->m_vScl.x, pChild->m_vScl.y, pChild->m_vScl.z);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"), 
			pChild->m_pShape->m_cbData.vColor.x,
			pChild->m_pShape->m_cbData.vColor.y,
			pChild->m_pShape->m_cbData.vColor.z,
			pChild->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^tx_Normal %s\n"), I_TexMgr.GetPtr(pChild->m_pIndexList[txNORMAL])->m_szName.data());
		_ftprintf(m_pStream, _T("^tx_Hover %s\n"), I_TexMgr.GetPtr(pChild->m_pIndexList[txHOVER])->m_szName.data());
		_ftprintf(m_pStream, _T("^tx_Press %s\n"), I_TexMgr.GetPtr(pChild->m_pIndexList[txPRESS])->m_szName.data());

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pChild->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pChild->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pChild->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pChild->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pChild->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pChild->m_vpClick.data());
	}
	void JUIWriter::CheckWrite(JPanel* pChild)
	{
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pChild->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pChild->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pChild->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pChild->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pChild->m_vPos.x, pChild->m_vPos.y, pChild->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pChild->m_vRot.x, pChild->m_vRot.y, pChild->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pChild->m_vScl.x, pChild->m_vScl.y, pChild->m_vScl.z);
		
		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pChild->m_pShape->m_cbData.vColor.x,
			pChild->m_pShape->m_cbData.vColor.y,
			pChild->m_pShape->m_cbData.vColor.z,
			pChild->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^tx_Disable %s\n"), I_TexMgr.GetPtr(pChild->m_pIndexList[txDISABLE])->m_szName.data());
		_ftprintf(m_pStream, _T("^tx_Enable %s\n"), I_TexMgr.GetPtr(pChild->m_pIndexList[txENABLE])->m_szName.data());
		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pChild->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pChild->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pChild->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pChild->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pChild->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pChild->m_vpClick.data());
	}
	void JUIWriter::ProgressWrite(JPanel* pChild)
	{
		JProgressBar* pProgress = (JProgressBar*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pChild->m_Type).data());
		_ftprintf(m_pStream, _T("^VHType %s\n"), std::to_wstring(pProgress->m_VHType).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pChild->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pChild->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pChild->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pChild->m_vPos.x, pChild->m_vPos.y, pChild->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pChild->m_vRot.x, pChild->m_vRot.y, pChild->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pChild->m_vScl.x, pChild->m_vScl.y, pChild->m_vScl.z);
		_ftprintf(m_pStream, _T("^SubScale %f %f %f\n"), 
			pProgress->m_pFrontGround->m_vScl.x, 
			pProgress->m_pFrontGround->m_vScl.y, 
			pProgress->m_pFrontGround->m_vScl.z);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pProgress->m_pBackGround->m_pShape->m_cbData.vColor.x,
			pProgress->m_pBackGround->m_pShape->m_cbData.vColor.y,
			pProgress->m_pBackGround->m_pShape->m_cbData.vColor.z,
			pProgress->m_pBackGround->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^tx_BackGround %s\n"), I_TexMgr.GetPtr(pProgress->m_pBackGround->m_pIndexList[txNORMAL])->m_szName.data());
		_ftprintf(m_pStream, _T("^tx_FrontGround %s\n"), I_TexMgr.GetPtr(pProgress->m_pFrontGround->m_pIndexList[txNORMAL])->m_szName.data());

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pChild->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pChild->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pChild->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pChild->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pChild->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pChild->m_vpClick.data());
	}
	void JUIWriter::SpriteWrite(JPanel* pChild)
	{
		JSpriteCtrl* pSprite = (JSpriteCtrl*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pSprite->m_Type).data());
		_ftprintf(m_pStream, _T("\n^SpriteType %s\n"), std::to_wstring(pSprite->m_SpriteType).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pSprite->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pSprite->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pChild->m_bRender);
		_ftprintf(m_pStream, _T("^bLoop %d\n"), pSprite->m_bLoop);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pSprite->m_vPos.x, pSprite->m_vPos.y, pSprite->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pSprite->m_vRot.x, pSprite->m_vRot.y, pSprite->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pSprite->m_vScl.x, pSprite->m_vScl.y, pSprite->m_vScl.z);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pChild->m_pShape->m_cbData.vColor.x,
			pChild->m_pShape->m_cbData.vColor.y,
			pChild->m_pShape->m_cbData.vColor.z,
			pChild->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^AnimTime %f\n"), pSprite->m_fAnimTime);
		_ftprintf(m_pStream, _T("^AnimUV %d %d \n"), pSprite->m_iRows, pSprite->m_iCols);

		_ftprintf(m_pStream, _T("^SPRITESTART %d \n"), pSprite->m_pIndexList.size());
		for (int iSprite = 0; iSprite < pChild->m_pIndexList.size(); iSprite++)
		{
			_ftprintf(m_pStream, _T("^%s\n"), I_TexMgr.GetPtr(pChild->m_pIndexList[iSprite])->m_szName.data());
		}
		_ftprintf(m_pStream, _T("^SPRITEEND\n"));

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pChild->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pChild->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pChild->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pChild->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pChild->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pChild->m_vpClick.data());
	}
	void JUIWriter::SliderWrite(JPanel* pChild)
	{
		JSliderCtrl* pSlider = (JSliderCtrl*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pSlider->m_Type).data());
		_ftprintf(m_pStream, _T("\n^VHType %s\n"), std::to_wstring(pSlider->m_VHType).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pSlider->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pSlider->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pChild->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pSlider->m_vPos.x, pSlider->m_vPos.y, pSlider->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pSlider->m_vRot.x, pSlider->m_vRot.y, pSlider->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pSlider->m_vScl.x, pSlider->m_vScl.y, pSlider->m_vScl.z);
		_ftprintf(m_pStream, _T("^SubScale %f %f %f\n"),
			pSlider->m_pSliderHandle->m_vScl.x,
			pSlider->m_pSliderHandle->m_vScl.y,
			pSlider->m_pSliderHandle->m_vScl.z);
		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pSlider->m_pSliderBar->m_pShape->m_cbData.vColor.x,
			pSlider->m_pSliderBar->m_pShape->m_cbData.vColor.y,
			pSlider->m_pSliderBar->m_pShape->m_cbData.vColor.z,
			pSlider->m_pSliderBar->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^tx_Bar %s\n"), I_TexMgr.GetPtr(pSlider->m_pSliderBar->m_pIndexList[txNORMAL])->m_szName.data());
		_ftprintf(m_pStream, _T("^tx_Handle %s\n"), I_TexMgr.GetPtr(pSlider->m_pSliderHandle->m_pIndexList[txNORMAL])->m_szName.data());

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pChild->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pChild->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pChild->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pChild->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pChild->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pChild->m_vpClick.data());
	}
	void JUIWriter::TextWrite(JPanel* pChild)
	{
		JTextCtrl* pText = (JTextCtrl*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pText->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pText->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pText->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pChild->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pText->m_vPos.x, pText->m_vPos.y, pText->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pText->m_vRot.x, pText->m_vRot.y, pText->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pText->m_vScl.x, pText->m_vScl.y, pText->m_vScl.z);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pChild->m_pShape->m_cbData.vColor.x,
			pChild->m_pShape->m_cbData.vColor.y,
			pChild->m_pShape->m_cbData.vColor.z,
			pChild->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^Align %d\n"), pText->m_Align);
		_ftprintf(m_pStream, _T("^strText %ws\n"), pText->m_Text.data());
		_ftprintf(m_pStream, _T("^TextSize %f\n"), pText->m_fSize);

		_ftprintf(m_pStream, _T("^tx_Normal %s\n"), I_TexMgr.GetPtr(pText->m_pIndexList[txNORMAL])->m_szName.data());
		_ftprintf(m_pStream, _T("^tx_Hover %s\n"), I_TexMgr.GetPtr(pText->m_pIndexList[txHOVER])->m_szName.data());
		_ftprintf(m_pStream, _T("^tx_Press %s\n"), I_TexMgr.GetPtr(pText->m_pIndexList[txPRESS])->m_szName.data());

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pChild->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pChild->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pChild->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pChild->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pChild->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pChild->m_vpClick.data());
	}
	void JUIWriter::ParticleWrite(JPanel* pChild)
	{
		JParticleSystem* pParticle = (JParticleSystem*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pParticle->m_Type).data());
		_ftprintf(m_pStream, _T("\n^SpriteType %s\n"), std::to_wstring(pParticle->m_pSprite->m_SpriteType).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pParticle->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pParticle->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pChild->m_bRender);
		_ftprintf(m_pStream, _T("^bLoop %d\n"), pParticle->m_pSprite->m_bLoop);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pParticle->m_vPos.x, pParticle->m_vPos.y, pParticle->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pParticle->m_vRot.x, pParticle->m_vRot.y, pParticle->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pParticle->m_vScl.x, pParticle->m_vScl.y, pParticle->m_vScl.z);

		_ftprintf(m_pStream, _T("^AnimTime %f\n"), pParticle->m_pSprite->m_fAnimTime);
		_ftprintf(m_pStream, _T("^AnimUV %d %d \n"), pParticle->m_pSprite->m_iRows, pParticle->m_pSprite->m_iCols);

		_ftprintf(m_pStream, _T("^ParticleSize %d\n"), pParticle->m_iMaxParticle);
		_ftprintf(m_pStream, _T("^ParticleScale %f %f\n"), pParticle->m_fMinScale, pParticle->m_fMaxScale);
		_ftprintf(m_pStream, _T("^MinStartPos %f %f %f\n"), pParticle->m_vMinStartPos.x, pParticle->m_vMinStartPos.y, pParticle->m_vMinStartPos.z);
		_ftprintf(m_pStream, _T("^MaxStartPos %f %f %f\n"), pParticle->m_vMaxStartPos.x, pParticle->m_vMaxStartPos.y, pParticle->m_vMaxStartPos.z);
		_ftprintf(m_pStream, _T("^TurnDir %d %d %d\n"), pParticle->m_bTurnX, pParticle->m_bTurnY, pParticle->m_bTurnZ);
		_ftprintf(m_pStream, _T("^MinColor %f %f %f %f\n"), pParticle->m_vMinColor.x, pParticle->m_vMinColor.y, pParticle->m_vMinColor.z, pParticle->m_vMinColor.w);
		_ftprintf(m_pStream, _T("^MaxColor %f %f %f %f\n"), pParticle->m_vMaxColor.x, pParticle->m_vMaxColor.y, pParticle->m_vMaxColor.z, pParticle->m_vMaxColor.w);
		_ftprintf(m_pStream, _T("^LifeTime %f %f\n"), pParticle->m_fMinLifeTime, pParticle->m_fMaxLifeTime);
		_ftprintf(m_pStream, _T("^MinDir %f %f %f\n"), pParticle->m_vMinDirection.x, pParticle->m_vMinDirection.y, pParticle->m_vMinDirection.z);
		_ftprintf(m_pStream, _T("^MaxDir %f %f %f\n"), pParticle->m_vMaxDirection.x, pParticle->m_vMaxDirection.y, pParticle->m_vMaxDirection.z);
		_ftprintf(m_pStream, _T("^MinDirAngle %f %f %f %f\n"), pParticle->m_qMinDirAngle.x, pParticle->m_qMinDirAngle.y, pParticle->m_qMinDirAngle.z, pParticle->m_qMinDirAngle.w);
		_ftprintf(m_pStream, _T("^MaxDirAngle %f %f %f %f\n"), pParticle->m_qMaxDirAngle.x, pParticle->m_qMaxDirAngle.y, pParticle->m_qMaxDirAngle.z, pParticle->m_qMaxDirAngle.w);
		_ftprintf(m_pStream, _T("^MoveSpeed %f %f\n"), pParticle->m_fMinMoveSpeed, pParticle->m_fMaxMoveSpeed);
		_ftprintf(m_pStream, _T("^RotSpeed %f %f\n"), pParticle->m_fMinRotateSpeed, pParticle->m_fMaxRotateSpeed);


		_ftprintf(m_pStream, _T("^SPRITESTART %d\n"), pParticle->m_pSprite->m_pIndexList.size());
		for (int iSprite = 0; iSprite < pParticle->m_pSprite->m_pIndexList.size(); iSprite++)
		{
			_ftprintf(m_pStream, _T("^%s\n"), I_TexMgr.GetPtr(pParticle->m_pSprite->m_pIndexList[iSprite])->m_szName.data());
		}
		_ftprintf(m_pStream, _T("^SPRITEEND\n"));

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pChild->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pChild->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pChild->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pChild->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pChild->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pChild->m_vpClick.data());
	}
	void JUIWriter::ListWrite(JPanel* pChild)
	{
		JListCtrl* pList = (JListCtrl*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pList->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pList->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pList->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pChild->m_pKeyDown, pChild->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pList->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pList->m_vPos.x, pList->m_vPos.y, pList->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pList->m_vRot.x, pList->m_vRot.y, pList->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pList->m_vScl.x, pList->m_vScl.y, pList->m_vScl.z);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pChild->m_pShape->m_cbData.vColor.x,
			pChild->m_pShape->m_cbData.vColor.y,
			pChild->m_pShape->m_cbData.vColor.z,
			pChild->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^Align %d\n"), pList->m_Align);
		_ftprintf(m_pStream, _T("^TextSize %f\n"), pList->m_fSize);
		_ftprintf(m_pStream, _T("^RectColumn %d\n"), pList->m_iCols);

		_ftprintf(m_pStream, _T("^tx_Normal %s\n"), I_TexMgr.GetPtr(pList->m_pIndexList[txNORMAL])->m_szName.data());

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pChild->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pChild->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pChild->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pChild->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pChild->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pChild->m_vpClick.data());
	}
	void JUIWriter::EditWrite(JPanel* pChild)
	{
		JEditCtrl* pEdit = (JEditCtrl*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pEdit->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pEdit->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pEdit->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pEdit->m_pKeyDown, pEdit->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pEdit->m_bRender);
		_ftprintf(m_pStream, _T("^bPrivate %d\n"), pEdit->m_bPrivate);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pEdit->m_vPos.x, pEdit->m_vPos.y, pEdit->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pEdit->m_vRot.x, pEdit->m_vRot.y, pEdit->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pEdit->m_vScl.x, pEdit->m_vScl.y, pEdit->m_vScl.z);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pChild->m_pShape->m_cbData.vColor.x,
			pChild->m_pShape->m_cbData.vColor.y,
			pChild->m_pShape->m_cbData.vColor.z,
			pChild->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^Align %d\n"), pEdit->m_Align);
		_ftprintf(m_pStream, _T("^TextSize %f\n"), pEdit->m_fSize);
		_ftprintf(m_pStream, _T("^TextLength %d\n"), pEdit->m_iMaxLength);

		_ftprintf(m_pStream, _T("^tx_Normal %s\n"), I_TexMgr.GetPtr(pEdit->m_pIndexList[txNORMAL])->m_szName.data());

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pEdit->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pEdit->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pEdit->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pEdit->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pEdit->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pEdit->m_vpClick.data());
	}
	void JUIWriter::ImageWrite(JPanel* pChild)
	{
		JImageCtrl* pEdit = (JImageCtrl*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pEdit->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pEdit->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pEdit->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pEdit->m_pKeyDown, pEdit->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pEdit->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pEdit->m_vPos.x, pEdit->m_vPos.y, pEdit->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pEdit->m_vRot.x, pEdit->m_vRot.y, pEdit->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pEdit->m_vScl.x, pEdit->m_vScl.y, pEdit->m_vScl.z);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pChild->m_pShape->m_cbData.vColor.x,
			pChild->m_pShape->m_cbData.vColor.y,
			pChild->m_pShape->m_cbData.vColor.z,
			pChild->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^tx_Normal %s\n"), I_TexMgr.GetPtr(pEdit->m_pIndexList[txNORMAL])->m_szName.data());

		_ftprintf(m_pStream, _T("^pfEventHover %s\n"), std::to_wstring(pEdit->m_pfHover).data());
		_ftprintf(m_pStream, _T("^vpEventHover %s\n"), pEdit->m_vpHover.data());
		_ftprintf(m_pStream, _T("^pfEventPress %s\n"), std::to_wstring(pEdit->m_pfPress).data());
		_ftprintf(m_pStream, _T("^vpEventPress %s\n"), pEdit->m_vpPress.data());
		_ftprintf(m_pStream, _T("^pfEventClick %s\n"), std::to_wstring(pEdit->m_pfClick).data());
		_ftprintf(m_pStream, _T("^vpEventClick %s\n"), pEdit->m_vpClick.data());
	}
	void JUIWriter::SlotWrite(JPanel* pChild)
	{
		JSlot* pSlot = (JSlot*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pSlot->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pSlot->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pSlot->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pSlot->m_pKeyDown, pSlot->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pSlot->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pSlot->m_vPos.x, pSlot->m_vPos.y, pSlot->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pSlot->m_vRot.x, pSlot->m_vRot.y, pSlot->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pSlot->m_vScl.x, pSlot->m_vScl.y, pSlot->m_vScl.z);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pSlot->m_pBack->m_pShape->m_cbData.vColor.x,
			pSlot->m_pBack->m_pShape->m_cbData.vColor.y,
			pSlot->m_pBack->m_pShape->m_cbData.vColor.z,
			pSlot->m_pBack->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^tx_Normal %s\n"), I_TexMgr.GetPtr(pSlot->m_pBack->m_pIndexList[txNORMAL])->m_szName.data());
	}
	void JUIWriter::InventoryWrite(JPanel* pChild)
	{
		JInventory* pInven = (JInventory*)pChild;
		_ftprintf(m_pStream, _T("\n^Type %s\n"), std::to_wstring(pInven->m_Type).data());
		_ftprintf(m_pStream, _T("^NodeName %s\n"), pInven->m_NodeName.data());
		_ftprintf(m_pStream, _T("^ParentName %s\n"), pInven->m_ParentName.data());
		_ftprintf(m_pStream, _T("^KeyState %d %d\n"), pInven->m_pKeyDown, pInven->m_pKeyHold);

		_ftprintf(m_pStream, _T("^bRender %d\n"), pInven->m_bRender);

		_ftprintf(m_pStream, _T("^Position %f %f %f\n"), pInven->m_vPos.x, pInven->m_vPos.y, pInven->m_vPos.z);
		_ftprintf(m_pStream, _T("^Rotate %f %f %f\n"), pInven->m_vRot.x, pInven->m_vRot.y, pInven->m_vRot.z);
		_ftprintf(m_pStream, _T("^Scale %f %f %f\n"), pInven->m_vScl.x, pInven->m_vScl.y, pInven->m_vScl.z);

		_ftprintf(m_pStream, _T("^RowCol %d %d \n"), pInven->m_iRows, pInven->m_iCols);

		_ftprintf(m_pStream, _T("^Color %f %f %f %f\n"),
			pInven->m_pBack->m_pShape->m_cbData.vColor.x,
			pInven->m_pBack->m_pShape->m_cbData.vColor.y,
			pInven->m_pBack->m_pShape->m_cbData.vColor.z,
			pInven->m_pBack->m_pShape->m_cbData.vColor.w);

		_ftprintf(m_pStream, _T("^tx_Normal %s\n"), I_TexMgr.GetPtr(pInven->m_pBack->m_pIndexList[txNORMAL])->m_szName.data());
		_ftprintf(m_pStream, _T("^tx_Hover %s\n"), pInven->m_strSlotBack.data());
	}
}