#include "JParticleSystem.h"
#include "Timer.h"
namespace UI
{
	void JParticleSystem::Play()
	{
		m_pSprite->m_bPlay = true;
	}
	bool JParticleSystem::Create(ID3D11Device* pDevice, int iMaxParticle, float fAnimTime, 
		vector<T_STR> FileList, const char* PSName, const TCHAR* szShaderName)
	{
		m_iMaxParticle = iMaxParticle;
		m_pSprite->Create(pDevice, fAnimTime, FileList, PSName, szShaderName);
		for (int i = 0; i < iMaxParticle; i++)
		{
			JParticle* particle = new JParticle();
			m_pParticle.push_back(particle);			
		}
		return true;
	}

	bool JParticleSystem::Frame(const float& spf, const float& accTime)noexcept
	{
		JPanel::PreFrame(spf, accTime);
		if (!m_bRender)
		{
			for (int iParticle = 0; iParticle < m_iMaxParticle; iParticle++)
			{
				m_pParticle[iParticle]->fStartTime = JDxHelper::fRand(0.0f, 10.0f);
				m_pParticle[iParticle]->bRender = false;
				m_pParticle[iParticle]->fElapseTime = 0.0f;
				m_pParticle[iParticle]->m_qRot = D3DXQUATERNION(0, 0, 0, 0);
				m_pParticle[iParticle]->SetColor(m_vMinColor, m_vMaxColor);
				m_pParticle[iParticle]->SetScale(m_fMinScale, m_fMaxScale);
				m_pParticle[iParticle]->SetTurnDirection(m_bTurnX, m_bTurnY, m_bTurnZ);
				m_pParticle[iParticle]->SetLifeTime(m_fMinLifeTime, m_fMaxLifeTime);
				m_pParticle[iParticle]->SetDirection(m_vMinDirection, m_vMaxDirection);
				m_pParticle[iParticle]->SetDirectionAngle(m_qMinDirAngle, m_qMaxDirAngle);
				m_pParticle[iParticle]->SetMoveSpeed(m_fMinMoveSpeed, m_fMaxMoveSpeed);
				m_pParticle[iParticle]->SetRotateSpeed(m_fMinRotateSpeed, m_fMaxRotateSpeed);
				m_pParticle[iParticle]->SetStartPos(this->m_vPos + m_vMinStartPos, this->m_vPos + m_vMaxStartPos);
			}
			return false;
		}
		m_pSprite->Frame(spf, accTime);


		m_pSprite->m_vScl = this->m_vScl;
		m_pSprite->m_vPos = this->m_vPos;
		m_pSprite->m_vRot = this->m_vRot;
		for (int iParticle = 0; iParticle < m_iMaxParticle; iParticle++)
		{
			m_pParticle[iParticle]->Frame(Timer::SPF);
			if (m_pParticle[iParticle]->fElapseTime >= m_pParticle[iParticle]->fLifeTime)
			{
				m_pParticle[iParticle]->bRender = false;
				m_pParticle[iParticle]->fElapseTime = 0.0f;
				m_pParticle[iParticle]->m_qRot = D3DXQUATERNION(0, 0, 0, 0);
				m_pParticle[iParticle]->SetColor(m_vMinColor, m_vMaxColor);
				m_pParticle[iParticle]->SetScale(m_fMinScale, m_fMaxScale);
				m_pParticle[iParticle]->SetTurnDirection(m_bTurnX, m_bTurnY, m_bTurnZ);
				m_pParticle[iParticle]->SetLifeTime(m_fMinLifeTime, m_fMaxLifeTime);
				m_pParticle[iParticle]->SetDirection(m_vMinDirection, m_vMaxDirection);
				m_pParticle[iParticle]->SetDirectionAngle(m_qMinDirAngle, m_qMaxDirAngle);
				m_pParticle[iParticle]->SetMoveSpeed(m_fMinMoveSpeed, m_fMaxMoveSpeed);
				m_pParticle[iParticle]->SetRotateSpeed(m_fMinRotateSpeed, m_fMaxRotateSpeed);
				m_pParticle[iParticle]->SetStartPos(this->m_vPos + m_vMinStartPos, this->m_vPos + m_vMaxStartPos);
			}
			if (m_pParticle[iParticle]->bRender == false)
			{
				m_pParticle[iParticle]->SetStartPos(this->m_vPos + m_vMinStartPos, this->m_vPos + m_vMaxStartPos);
			}
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JParticleSystem::Render(ID3D11DeviceContext* pContext)noexcept
	{
		if (!m_bRender) return false;
		for (int iParticle = 0; iParticle < m_pParticle.size(); iParticle++)
		{
			if (m_pParticle[iParticle]->bRender == false) continue;
			m_pSprite->m_pShape->m_cbData.vColor = m_pParticle[iParticle]->vColor;
			m_pSprite->m_matWorld = m_pParticle[iParticle]->m_matWorld;
			m_pSprite->Render(pContext);
		}

		JPanel::Render(pContext);
		return true;
	}
	bool JParticleSystem::Release()noexcept
	{
		SAFE_RELEASE(m_pSprite);
		for (int iC = 0; iC < m_pParticle.size(); iC++)
		{
			SAFE_DELETE(m_pParticle[iC]);
		}
		return true;
	}
	bool JParticleSystem::ParticleRelease()
	{
		for (auto& iC : m_pParticle)
		{
			SAFE_DELETE(iC);
		}
		return true;
	}
	void JParticleSystem::SetScale(const float fMin, const float fMax)
	{
		m_fMinScale = fMin;
		m_fMaxScale = fMax;
	}
	void JParticleSystem::SetTurnDirection(const bool bX, const bool bY, const bool bZ)
	{
		m_bTurnX = bX;
		m_bTurnY = bY;
		m_bTurnZ = bZ;
	}
	void JParticleSystem::SetStartPos(const D3DXVECTOR3 vMin, const D3DXVECTOR3 vMax)
	{
		m_vMinStartPos = vMin;
		m_vMaxStartPos = vMax;
	}
	void JParticleSystem::SetLifeTime(float fMin, float fMax)
	{
		m_fMinLifeTime = fMin;
		m_fMaxLifeTime = fMax;
	}
	void JParticleSystem::SetDirection(const D3DXVECTOR3 vMin, const D3DXVECTOR3 vMax)
	{
		m_vMinDirection = vMin;
		m_vMaxDirection = vMax;
	}
	void JParticleSystem::SetDirectionAngle(const D3DXQUATERNION qMin, const D3DXQUATERNION qMax)
	{
		m_qMinDirAngle = qMin;
		m_qMaxDirAngle = qMax;
	}
	void JParticleSystem::SetMoveSpeed(const float fMin, const float fMax)
	{
		m_fMinMoveSpeed = fMin;
		m_fMaxMoveSpeed = fMax;
	}
	void JParticleSystem::SetRotateSpeed(const float fMin, const float fMax)
	{
		m_fMinRotateSpeed = fMin;
		m_fMaxRotateSpeed = fMax;
	}
	void JParticleSystem::SetColor(const D3DXVECTOR4 vMin, const D3DXVECTOR4 vMax)
	{
		m_vMinColor = vMin;
		m_vMaxColor = vMax;
	}
}