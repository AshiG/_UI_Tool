#include "JButtonCtrl.h"
#include "WriteManager.h"
namespace UI
{
	void* JButtonCtrl::uiclone()
	{
		return new JButtonCtrl(*this);
	}
	bool JButtonCtrl::Create(ID3D11Device* pDevice, const TCHAR* szNORMAL, const TCHAR* szHOVER, const TCHAR* szPRESS,
		const char* PSName, const TCHAR* szShaderName)
	{
		JImageCtrl::Create(pDevice, PSName, szShaderName);
		/* ====================  Texture Setting ====================*/
		if (!SetTexture(pDevice, szNORMAL)) return false;
		if (!SetTexture(pDevice, szHOVER))  return false;
		if (!SetTexture(pDevice, szPRESS))  return false;
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
		/* =========================================================== */
		return true;
	}
	void JButtonCtrl::Update()
	{
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);

		if (m_pShape->Hovered(m_rt, m_ptMouse.Getpt()))
		{
			m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txHOVER]);
			if(EventHover.first != nullptr && m_bEvent)
				EventHover.first(EventHover.second);
		}
		if (m_pShape->Pressed(m_rt, m_ptMouse.Getpt()) || 
			Input::Get().GetKeyState(m_pKeyHold) == EKeyState::HOLD)
		{
			m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txPRESS]);
			if (EventPress.first != nullptr && m_bEvent)
				EventPress.first(EventPress.second);
		}
		if (m_pShape->Clicked(m_rt, m_ptMouse.Getpt()) || 
			Input::Get().GetKeyState(m_pKeyDown) == EKeyState::UP)
		{
			if (EventClick.first != nullptr && m_bEvent)
				EventClick.first(EventClick.second);
		}
	}
	bool JButtonCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
		if (!m_bRender) return false;
			this->Update();
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JButtonCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		if (!m_bRender) return false;
		JImageCtrl::Render(pContext);	
		return true;
	}
	bool JButtonCtrl::Release()noexcept
	{
		JImageCtrl::Release();
		return true;
	}
}