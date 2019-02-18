#include "JProgressBar.h"

namespace UI
{
	void* JProgressBar::uiclone()
	{
		return new JProgressBar(*this);
	}
	void JProgressBar::SetColor(const D3DXVECTOR4 vColor)
	{
		if (m_pBackGround->m_pShape == nullptr || m_pFrontGround->m_pShape == nullptr) return;
		m_pBackGround->m_pShape->m_cbData.vColor = vColor;
		m_pFrontGround->m_pShape->m_cbData.vColor = vColor;
		//m_pDisImg->m_pShape->m_cbData.vColor = vColor;
	}
	void JProgressBar::SetMiddleColor(D3DXVECTOR4 vColor)
	{
		if (m_pMiddleGround->m_pShape == nullptr) return;
		m_pMiddleGround->m_pShape->m_cbData.vColor = vColor;
	}
	bool JProgressBar::Create(ID3D11Device* pDevice, const TCHAR* szBack, const TCHAR* szFront,	const char* PSName, const TCHAR* szShaderName)
	{
		m_pBackGround->Create(pDevice, PSName, szShaderName);
		m_pFrontGround->Create(pDevice, PSName, szShaderName);
		m_pMiddleGround->Create(pDevice, PSName, szShaderName);
		//
		m_pBackGround->SetTexture(pDevice, szBack);
		m_pFrontGround->SetTexture(pDevice, szFront);
		m_pMiddleGround->SetTexture(pDevice, szFront);
		//
		m_pBackGround->m_pShape->m_cbData.vColor = D3DXVECTOR4 (1.0f, 1.0f, 1.0f, 1.0f);
		m_pFrontGround->m_pShape->m_cbData.vColor = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		m_pMiddleGround->m_pShape->m_cbData.vColor = D3DXVECTOR4(1.0f, 0.7f, 0.5f, 1.0f);
		//
		m_pBackGround->m_pTexture = I_TexMgr.GetPtr(m_pBackGround->m_pIndexList[txNORMAL]);
		m_pMiddleGround->m_pTexture = I_TexMgr.GetPtr(m_pMiddleGround->m_pIndexList[txNORMAL]);
		m_pFrontGround->m_pTexture = I_TexMgr.GetPtr(m_pFrontGround->m_pIndexList[txNORMAL]);

		m_fCur = &m_fTemp;
		m_fDis = &m_fTemp;
		return true;
	}
	void JProgressBar::CheckDis(const float& spf)
	{
		if (m_bEngineDecrease)
		{
			m_fDisValue = (*m_fDis) / m_fMaxValue;
		}
		else
		{
			if (m_fDisValue > m_fCurValue)
			{
				m_fDisValue -= spf * 0.5f;
			}
			if (m_fDisValue <= m_fCurValue)
			{
				m_fDisValue = m_fCurValue;
			}
		}
	}
	void JProgressBar::SetValue(const float& fValue, float fMaxValue, float& fDisValue)
	{
		m_fMaxValue = fMaxValue;
		m_fCur = &fValue;
		m_fDis = &fDisValue;
		m_bEngineDecrease = true;
	}
	void JProgressBar::UpdateTexture(JImageCtrl* pImage, float fValue)
	{
		if (m_VHType == Vertical)
		{
			pImage->m_pShape->m_pVertices[0].t = D3DXVECTOR2(0.0f, fValue);
			pImage->m_pShape->m_pVertices[1].t = D3DXVECTOR2(1.0f, fValue);
			pImage->m_pShape->m_pVertices[0].p = D3DXVECTOR3(-1.0f, fValue * 2.0f - 1.0f, 0.0f);
			pImage->m_pShape->m_pVertices[1].p = D3DXVECTOR3(1.0f, fValue * 2.0f - 1.0f, 0.0f);
			
			pImage->m_pShape->m_pVertices[2].p = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
			pImage->m_pShape->m_pVertices[3].p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			pImage->m_pShape->m_pVertices[2].t = D3DXVECTOR2(1.0f, 1.0f);
			pImage->m_pShape->m_pVertices[3].t = D3DXVECTOR2(0.0f, 1.0f);
		}
		else if (m_VHType == Horizontal)
		{
			pImage->m_pShape->m_pVertices[1].t = D3DXVECTOR2(fValue, 0.0f);
			pImage->m_pShape->m_pVertices[2].t = D3DXVECTOR2(fValue, 1.0f);
			pImage->m_pShape->m_pVertices[1].p = D3DXVECTOR3(fValue * 2.0f - 1.0f, 1.0f, 0.0f);
			pImage->m_pShape->m_pVertices[2].p = D3DXVECTOR3(fValue * 2.0f - 1.0f, -1.0f, 0.0f);
			
			pImage->m_pShape->m_pVertices[0].p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
			pImage->m_pShape->m_pVertices[0].t = D3DXVECTOR2(0.0f, 0.0f);
			pImage->m_pShape->m_pVertices[3].p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
			pImage->m_pShape->m_pVertices[3].t = D3DXVECTOR2(0.0f, 1.0f);
		}
	}
	void JProgressBar::Update(const float& spf)
	{
		/* ============= */
		m_pBackGround->m_pTexture = I_TexMgr.GetPtr(m_pBackGround->m_pIndexList[txNORMAL]);
		m_pMiddleGround->m_pTexture = I_TexMgr.GetPtr(m_pMiddleGround->m_pIndexList[txNORMAL]);
		m_pFrontGround->m_pTexture = I_TexMgr.GetPtr(m_pFrontGround->m_pIndexList[txNORMAL]);

		m_fCurValue = (*m_fCur) / m_fMaxValue;
		UpdateTexture(m_pFrontGround, m_fCurValue);
		if (m_bDecrease)
		{
			CheckDis(spf);
			UpdateTexture(m_pMiddleGround, m_fDisValue);
		}

		/* 기준 = Back */
		m_pBackGround->m_vScl = this->m_vScl;
		m_pBackGround->m_vPos = this->m_vPos;
		m_pBackGround->m_vRot = this->m_vRot;

		/* Front는 항상 Back따라다님 */
		m_pMiddleGround->m_vPos = m_pFrontGround->m_vPos = m_pBackGround->m_vPos;
		m_pMiddleGround->m_vRot = m_pFrontGround->m_vRot = m_pBackGround->m_vRot;
		m_pMiddleGround->m_vScl = m_pFrontGround->m_vScl;
		JPanel::Update();
	}
	bool JProgressBar::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
		if (!m_bRender) return false;
			this->Update(spf);
			m_pBackGround->Frame(spf, accTime);
			if (m_bDecrease)
			{
				m_pMiddleGround->Frame(spf, accTime);
			}
			m_pFrontGround->Frame(spf, accTime);
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JProgressBar::Render(ID3D11DeviceContext* pContext)noexcept
	{
		if (!m_bRender) return false;
		m_pBackGround->Render(pContext);
		if (m_bDecrease)
		{
			m_pMiddleGround->Render(pContext);
		}
		m_pFrontGround->Render(pContext);
		JPanel::Render(pContext);
		return true;
	}
	bool JProgressBar::Release()noexcept
	{
		SAFE_DELETE(m_pBackGround);
		SAFE_DELETE(m_pMiddleGround);
		SAFE_DELETE(m_pFrontGround);
		JPanel::Release();
		return true;
	}
}