#include "JImageCtrl.h"
#include "DxManager.h"
namespace UI
{
	bool JImageCtrl::Create(ID3D11Device* pDevice,const char* psName, const TCHAR* psShaderName)
	{
		m_pShape->Create(pDevice, psName, psShaderName);
		return true;
	}
	bool JImageCtrl::SetTexture(ID3D11Device* pDevice, const TCHAR* txName)
	{
		int iIndex = UI::I_TexMgr.Add(pDevice, txName);
		if (iIndex < 0) return false;
		m_pIndexList.push_back(iIndex);
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
		return true;
	}
	void JImageCtrl::Update()
	{
#ifdef _DEBUG
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
#endif
	}
	bool JImageCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
			if (!m_bRender) return false;
			this->Update();
		}
		JPanel::PostFrame(spf, accTime); // child 순회
		return true;
	}
	bool JImageCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		if (!m_bRender) return false;
		DxManager::Get().SetBlendState(EBlendS::Basic);
		DxManager::Get().SetDepthStencilState(EDepthS::Basic);

		m_pShape->SetMatrix(&m_matWorld, &m_matView, &m_matProj);
		m_pShape->Render(pContext, m_pTexture);
		JPanel::Render(pContext); // Child 순회

		DxManager::Get().SetBlendState(EBlendS::Current);
		DxManager::Get().SetDepthStencilState(EDepthS::Current);
		return true;
	}
	bool JImageCtrl::Release()noexcept
	{
		JPanel::Release();
		return true;
	}
}