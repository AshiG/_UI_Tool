#include "JCheckCtrl.h"
#include "Writemanager.h"
namespace UI
{
	void* JCheckCtrl::uiclone()
	{
		return new JCheckCtrl(*this);
	}
	bool JCheckCtrl::Create(ID3D11Device* pDevice, const TCHAR* szENABLE, const TCHAR* szDISABLE,
		const char* PSName, const TCHAR* szShaderName)
	{
		JImageCtrl::Create(pDevice, PSName, szShaderName);
		/* ====================  Texture Setting ====================*/
		if (!SetTexture(pDevice, szENABLE)) return false;
		if (!SetTexture(pDevice, szDISABLE))  return false;
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txDISABLE]);
		/* =========================================================== */
		return true;
	}
	void JCheckCtrl::SetCheck(bool Check)
	{
		m_bCheck = Check;
	}
	bool JCheckCtrl::GetCheck()
	{
		return m_bCheck;
	}
	void JCheckCtrl::Update()
	{
		//if (m_pShape->Hovered(m_rt, m_ptMouse.Getpt()))
		//{
		//	if (EventHover.first != nullptr && m_bEvent)
		//		EventHover.first(EventHover.second);
		//}
		//if (m_pShape->Pressed(m_rt, m_ptMouse.Getpt()) ||
		//	Input::Get().GetKeyState(m_pKeyHold) == EKeyState::HOLD)
		//{
		//	if (EventPress.first != nullptr && m_bEvent)
		//		EventPress.first(EventPress.second);
		//}
		//if (m_pShape->Clicked(m_rt, m_ptMouse.Getpt()) ||
		//	Input::Get().GetKeyState(m_pKeyDown) == EKeyState::UP)
		//{
		//	if (EventClick.first != nullptr && m_bEvent)
		//		EventClick.first(EventClick.second);
		//	m_bCheck = !m_bCheck;
		//}
		if (CheckClicked())
		{
			m_bCheck = !m_bCheck;
		}

		if (m_bCheck)
		{
			m_pTexture = I_TexMgr.GetPtr(JImageCtrl::m_pIndexList[txENABLE]);
		}
		else
		{
			m_pTexture = I_TexMgr.GetPtr(JImageCtrl::m_pIndexList[txDISABLE]);
		}
	}
	bool JCheckCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
		if (!m_bRender) return false;
			this->Update();
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JCheckCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		if (!m_bRender) return false;
		JImageCtrl::Render(pContext);
		return true;
	}
	bool JCheckCtrl::Release()noexcept
	{
		JImageCtrl::Release();
		return true;
	}
}