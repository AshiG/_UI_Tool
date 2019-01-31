#include "JSliderCtrl.h"
#include "Window.h"
#include "Input.h"
namespace UI
{
	void* JSliderCtrl::uiclone()
	{
		return new JSliderCtrl(*this);
	}
	bool JSliderCtrl::Create(ID3D11Device* pDevice, const TCHAR* szBar, const TCHAR* szHandle, const char* PSName, const TCHAR* szShaderName)
	{
		if (!m_pSliderBar->Create(pDevice, PSName, szShaderName)) return false;
		if (!m_pSliderHandle->Create(pDevice, PSName, szShaderName)) return false;
		m_pSliderBar->SetTexture(pDevice, szBar);
		m_pSliderHandle->SetTexture(pDevice, szHandle);
		return true;
	}
	bool JSliderCtrl::SetTexture(ID3D11Device* pDevice, const TCHAR* szBar, const TCHAR* szHandle)
	{
		if (!m_pSliderBar->SetTexture(pDevice, szBar)) return false;
		if (!m_pSliderHandle->SetTexture(pDevice, szHandle)) return false;

		m_pSliderBar->m_pTexture = I_TexMgr.GetPtr(m_pSliderBar->m_pIndexList[txNORMAL]);
		m_pSliderHandle->m_pTexture = I_TexMgr.GetPtr(m_pSliderHandle->m_pIndexList[txNORMAL]);
		return true;
	}
	const float* JSliderCtrl::GetValue()
	{
		return &m_fValue;
	}
	void JSliderCtrl::SetValue(float fValue)
	{
		m_fValue = fValue;
	}
	void JSliderCtrl::Update()
	{
		m_pSliderBar->m_pTexture = I_TexMgr.GetPtr(m_pSliderBar->m_pIndexList[txNORMAL]);
		m_pSliderHandle->m_pTexture = I_TexMgr.GetPtr(m_pSliderHandle->m_pIndexList[txNORMAL]);
		if (m_VHType == Vertical)
		{
			m_pSliderHandle->m_vPos.x = m_pSliderBar->m_vPos.x;
			m_pSliderHandle->m_vPos.y = ((m_fValue * (m_pSliderBar->m_vScl.y * 2.0f)) - m_pSliderBar->m_vScl.y) + m_pSliderBar->m_vPos.y;
			if (m_bClick)
			{
				m_pSliderHandle->m_vPos.y = (float)m_pSliderHandle->m_ptMouse.Getpt().y;
				if (m_pSliderHandle->m_vPos.y <= m_pSliderBar->m_vPos.y - m_pSliderBar->m_vScl.y)
				{
					m_pSliderHandle->m_vPos.y = m_pSliderBar->m_vPos.y - m_pSliderBar->m_vScl.y;
				}

				if (m_pSliderHandle->m_vPos.y >= m_pSliderBar->m_vPos.y + m_pSliderBar->m_vScl.y)
				{
					m_pSliderHandle->m_vPos.y = m_pSliderBar->m_vPos.y + m_pSliderBar->m_vScl.y;
				}
				m_fValue = ((m_pSliderHandle->m_vPos.y - m_pSliderBar->m_vPos.y) / m_pSliderBar->m_vScl.y) * 0.5f + 0.5f;
			}
			/* 기준 = Bar */
			m_pSliderBar->m_vScl = this->m_vScl;
			m_pSliderBar->m_vPos = this->m_vPos;
			m_pSliderBar->m_vRot = this->m_vRot;
			/* SliderHandle Scl = SliderBar Scl.y * 2.0f */
			//m_pSliderHandle->m_vScl.x = m_pSliderBar->m_vScl.x * 4.0f;
			//m_pSliderHandle->m_vScl.y = m_pSliderBar->m_vScl.x * 4.0f;
			m_pSliderHandle->m_vRot = m_pSliderBar->m_vRot;
		}
		else if (m_VHType == Horizontal)
		{
			m_pSliderHandle->m_vPos.y = m_pSliderBar->m_vPos.y;
			m_pSliderHandle->m_vPos.x = ((m_fValue * (m_pSliderBar->m_vScl.x * 2.0f)) - m_pSliderBar->m_vScl.x) + m_pSliderBar->m_vPos.x;
			if (m_bClick)
			{
				m_pSliderHandle->m_vPos.x = (float)m_pSliderHandle->m_ptMouse.Getpt().x;
				if (m_pSliderHandle->m_vPos.x <= m_pSliderBar->m_vPos.x - m_pSliderBar->m_vScl.x)
				{
					m_pSliderHandle->m_vPos.x = m_pSliderBar->m_vPos.x - m_pSliderBar->m_vScl.x;
				}

				if (m_pSliderHandle->m_vPos.x >= m_pSliderBar->m_vPos.x + m_pSliderBar->m_vScl.x)
				{
					m_pSliderHandle->m_vPos.x = m_pSliderBar->m_vPos.x + m_pSliderBar->m_vScl.x;
				}
				m_fValue = ((m_pSliderHandle->m_vPos.x - m_pSliderBar->m_vPos.x) / m_pSliderBar->m_vScl.x) * 0.5f + 0.5f;
			}
			/* 기준 = Bar */
			m_pSliderBar->m_vScl = this->m_vScl;
			m_pSliderBar->m_vPos = this->m_vPos;
			m_pSliderBar->m_vRot = this->m_vRot;
			/* SliderHandle Scl = SliderBar Scl.y * 2.0f */
			m_pSliderHandle->m_vRot = m_pSliderBar->m_vRot;
		}

		if (Input::GetKeyState(EMouseButton::Left) == EKeyState::DOWN)
		{
			if (JDxHelper::RectInPt(m_pSliderHandle->m_rt, m_pSliderHandle->m_ptMouse.Getpt()))
			{
				m_bClick = true;
			}
		}

		if (Input::GetKeyState(EMouseButton::Left) == EKeyState::UP)
		{
			m_bClick = false;
		}

		JPanel::Update();
	}
	bool JSliderCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
		if (!m_bRender) return false;
			this->Update();
			m_pSliderBar->Frame(spf, accTime);
			m_pSliderHandle->Frame(spf, accTime);
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JSliderCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		if (!m_bRender) return false;
		JPanel::Render(pContext);
		m_pSliderBar->Render(pContext);
		m_pSliderHandle->Render(pContext);
		return true;
	}
	bool JSliderCtrl::Release()noexcept
	{
		m_pSliderBar->Release();
		m_pSliderHandle->Release();
		SAFE_DELETE(m_pSliderBar);
		SAFE_DELETE(m_pSliderHandle);
		JPanel::Release();
		return true;
	}
}