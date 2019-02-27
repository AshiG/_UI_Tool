#include "JSpriteCtrl.h"
#include "Timer.h"
namespace UI
{
	void* JSpriteCtrl::uiclone()
	{
		return new JSpriteCtrl(*this);
	}
	void JSpriteCtrl::Play()
	{
		m_bPlay = true;
	}
	bool JSpriteCtrl::Create(ID3D11Device* pDevice, float fAnimTime, vector<T_STR> FileList, const char* PSName, const TCHAR* szShaderName)
	{
		JImageCtrl::Create(pDevice, PSName, szShaderName);
		/* ====================  Texture Setting ====================*/
		for (int iList = 0; iList < FileList.size(); iList++)
		{
			// Texture index를 배열로 가지고있음
			INT iIndex = I_TexMgr.Add(pDevice, FileList[iList].c_str());
			if (iIndex < 0)	return false;
			if (!SetTexture(pDevice, FileList[iList].c_str()))
				return false;
		}
		m_iNumTexture = (int)m_pIndexList.size();
		m_fAnimTime = fAnimTime;
		m_fChangeTime = fAnimTime / m_iNumTexture;
		/* =========================================================== */
		return true;
	}
	bool JSpriteCtrl::SetSpriteType(SpriteType type, int row, int col)
	{
		m_SpriteType = type;
		if (m_SpriteType == TEXSPRITE)
		{
			return true;
		}
		else if (m_SpriteType == UVSPRITE)
		{
			m_iRows = row;
			m_iCols = col;
			m_iNumTexture = m_iRows * m_iCols;
			m_fChangeTime = m_fAnimTime / m_iNumTexture;
			m_fUVRows = 1.0f / (float)row;
			m_fUVCols = 1.0f / (float)col;
		}
		return true;
	}
	void JSpriteCtrl::SetAnimTime(float fAnim)
	{
		m_fAnimTime = fAnim;
		if (m_SpriteType == TEXSPRITE)
		{
			m_iNumTexture = (int)m_pIndexList.size();
			m_fChangeTime = m_fAnimTime / m_iNumTexture;
		}
		else if (m_SpriteType == UVSPRITE)
		{
			m_iNumTexture = m_iRows * m_iCols;
			m_fChangeTime = m_fAnimTime / m_iNumTexture;
		}
	}
	void JSpriteCtrl::SetUV(int row, int col)
	{
		m_iRows = row;
		m_iCols = col;
		m_iNumTexture = m_iRows * m_iCols;
		m_fChangeTime = m_fAnimTime / m_iNumTexture;
		m_fUVRows = 1.0f / (float)row;
		m_fUVCols = 1.0f / (float)col;
	}
	void JSpriteCtrl::Update()
	{
		m_fTime += Timer::SPF;
		if (!m_bPlay)
		{
			m_iCurrentIndex = 0;
			m_iCurrentCols = 1;
			m_iCurrentRows = 1;
			m_fTime = 0.0f;
			return;
		}
		if (m_SpriteType == TEXSPRITE)
		{
			if (m_fTime >= m_fChangeTime)
			{
				if (++m_iCurrentIndex >= m_iNumTexture)
				{
					m_iCurrentIndex = 0;
					if (m_bLoop) 
						m_bPlay = true;
					else 
						m_bPlay = false;
				}
				m_fTime = 0.0f;
			}
			if (m_pIndexList.size())
			{
				m_pTexture = I_TexMgr.GetPtr(m_pIndexList[m_iCurrentIndex]);
				m_pShape->m_pVertices[0].t = D3DXVECTOR2(0.0f, 0.0f);
				m_pShape->m_pVertices[1].t = D3DXVECTOR2(1.0f, 0.0f);
				m_pShape->m_pVertices[2].t = D3DXVECTOR2(1.0f, 1.0f);
				m_pShape->m_pVertices[3].t = D3DXVECTOR2(0.0f, 1.0f);
			}
		}
		else if (m_SpriteType == UVSPRITE)
		{
			if (m_fTime >= m_fChangeTime)
			{
				if (++m_iCurrentRows >= m_iRows + 1)
				{
					m_iCurrentRows = 1;
					if (++m_iCurrentCols >= m_iCols + 1)
					{
						m_iCurrentCols = 1;
						m_iCurrentRows = 1;
						if (m_bLoop) 
							m_bPlay = true;
						else 
							m_bPlay = false;
					}
				}
				m_fTime = 0.0f;
			}
			D3DXVECTOR4 rt;
			rt.x = m_fUVRows * m_iCurrentRows; // right (x)
			rt.y = rt.x - m_fUVRows; // left (x)
			rt.z = m_fUVCols * m_iCurrentCols; // bottom (y)
			rt.w = rt.z - m_fUVCols; // top (y)
		
			m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
			m_pShape->m_pVertices[0].t = D3DXVECTOR2(rt.y, rt.w); 
			m_pShape->m_pVertices[1].t = D3DXVECTOR2(rt.x, rt.w); 
			m_pShape->m_pVertices[2].t = D3DXVECTOR2(rt.x, rt.z); 
			m_pShape->m_pVertices[3].t = D3DXVECTOR2(rt.y, rt.z); 
		}
	}
	bool JSpriteCtrl::Frame(const float& spf, const float& accTime)noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
			if (!m_bRender) return false;
			this->Update();
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JSpriteCtrl::Render(ID3D11DeviceContext* pContext)noexcept
	{
		if (!m_bRender) return false;
		if (!m_bPlay) return false;
		return JImageCtrl::Render(pContext);
	}
	bool JSpriteCtrl::Release()noexcept
	{
		JImageCtrl::Release();
		return true;
	}
}