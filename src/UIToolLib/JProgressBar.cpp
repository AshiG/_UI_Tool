#include "JProgressBar.h"

namespace UI
{
	void* JProgressBar::uiclone()
	{
		return new JProgressBar(*this);
	}
	bool JProgressBar::Create(ID3D11Device* pDevice, const TCHAR* szBack, const TCHAR* szFront,	const char* PSName, const TCHAR* szShaderName)
	{
		m_pBackGround->Create(pDevice, PSName, szShaderName);
		m_pFrontGround->Create(pDevice, PSName, szShaderName);
		m_pBackGround->SetTexture(pDevice, szBack);
		m_pFrontGround->SetTexture(pDevice, szFront);
		m_pBackGround->m_pShape->m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		m_pFrontGround->m_pShape->m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		m_pBackGround->m_pTexture = I_TexMgr.GetPtr(m_pBackGround->m_pIndexList[txNORMAL]);
		m_pFrontGround->m_pTexture = I_TexMgr.GetPtr(m_pFrontGround->m_pIndexList[txNORMAL]);
		m_fCurValue = &m_fTemp;
		return true;
	}
	void JProgressBar::SetValue(const float& fValue, float fMaxValue)
	{
		m_fMaxValue = fMaxValue;
		m_fCurValue = &fValue;
	}
	void JProgressBar::Update()
	{
		/* m_fValue 계산 */
		m_fValue = (*m_fCurValue) / m_fMaxValue;
		/* ============= */
		m_pBackGround->m_pTexture = I_TexMgr.GetPtr(m_pBackGround->m_pIndexList[txNORMAL]);
		m_pFrontGround->m_pTexture = I_TexMgr.GetPtr(m_pFrontGround->m_pIndexList[txNORMAL]);
		if(m_VHType == Vertical)
		{
			m_pFrontGround->m_pShape->m_pVertices[0].t = D3DXVECTOR2(0.0f, m_fValue);
			m_pFrontGround->m_pShape->m_pVertices[1].t = D3DXVECTOR2(1.0f, m_fValue);
			m_pFrontGround->m_pShape->m_pVertices[0].p = D3DXVECTOR3(-1.0f, m_fValue * 2.0f - 1.0f, 0.0f);
			m_pFrontGround->m_pShape->m_pVertices[1].p = D3DXVECTOR3(1.0f,  m_fValue * 2.0f - 1.0f, 0.0f);

			m_pFrontGround->m_pShape->m_pVertices[2].p = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
			m_pFrontGround->m_pShape->m_pVertices[3].p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			m_pFrontGround->m_pShape->m_pVertices[2].t = D3DXVECTOR2(1.0f, 1.0f);
			m_pFrontGround->m_pShape->m_pVertices[3].t = D3DXVECTOR2(0.0f, 1.0f);
		}
		else if (m_VHType == Horizontal)
		{
			m_pFrontGround->m_pShape->m_pVertices[1].t = D3DXVECTOR2(m_fValue, 0.0f);
			m_pFrontGround->m_pShape->m_pVertices[2].t = D3DXVECTOR2(m_fValue, 1.0f);
			m_pFrontGround->m_pShape->m_pVertices[1].p = D3DXVECTOR3(m_fValue * 2.0f - 1.0f, 1.0f, 0.0f);
			m_pFrontGround->m_pShape->m_pVertices[2].p = D3DXVECTOR3(m_fValue * 2.0f - 1.0f, -1.0f, 0.0f);

			// uv 원래대로 0,1 번
			m_pFrontGround->m_pShape->m_pVertices[0].p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
			m_pFrontGround->m_pShape->m_pVertices[0].t = D3DXVECTOR2(0.0f, 0.0f);
			m_pFrontGround->m_pShape->m_pVertices[3].p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			m_pFrontGround->m_pShape->m_pVertices[3].t = D3DXVECTOR2(0.0f, 1.0f);
		}
		/* 기준 = Back */
		m_pBackGround->m_vScl = this->m_vScl;
		m_pBackGround->m_vPos = this->m_vPos;
		m_pBackGround->m_vRot = this->m_vRot;

		/* Front는 항상 Back따라다님 */
		m_pFrontGround->m_vPos = m_pBackGround->m_vPos;
		m_pFrontGround->m_vRot = m_pBackGround->m_vRot;
		JPanel::Update();
	}
	bool JProgressBar::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
		if (!m_bRender) return false;
			this->Update();
			m_pBackGround->Frame(spf, accTime);
			m_pFrontGround->Frame(spf, accTime);
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JProgressBar::Render(ID3D11DeviceContext* pContext)noexcept
	{
		if (!m_bRender) return false;
		m_pBackGround->Render(pContext);
		m_pFrontGround->Render(pContext);
		JPanel::Render(pContext);
		return true;
	}
	bool JProgressBar::Release()noexcept
	{
		m_pBackGround->Release();
		m_pFrontGround->Release();
		SAFE_DELETE(m_pBackGround);
		SAFE_DELETE(m_pFrontGround);
		JPanel::Release();
		return true;
	}
}