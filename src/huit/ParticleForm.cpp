// ParticleForm.cpp: 구현 파일
//

#include "stdafx.h"
#include "huit.h"
#include "ParticleForm.h"
#include "afxdialogex.h"


// ParticleForm 대화 상자
ParticleForm* ParticleForm::m_pInstance = nullptr;

IMPLEMENT_DYNAMIC(ParticleForm, CFormView)

ParticleForm* ParticleForm::CreateOne(CWnd* pParent)
{
	ParticleForm* pForm = new ParticleForm();
	pForm->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(0, 0, 500, 500), pParent, 0, NULL);
	return pForm;
}

ParticleForm::ParticleForm()
	: CFormView(IDD_ParticleForm)
{
	m_pInstance = this;
}

ParticleForm::~ParticleForm()
{
	m_pInstance = nullptr;
	m_pInstance = NULL;
}

void ParticleForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, P_TurnX, m_pTurnX);
	DDX_Control(pDX, P_TurnY, m_pTurnY);
	DDX_Control(pDX, P_TurnZ, m_pTurnZ);
}


BEGIN_MESSAGE_MAP(ParticleForm, CFormView)
	ON_BN_CLICKED(P_Change, &ParticleForm::OnBnClickedChange)
END_MESSAGE_MAP()


// ParticleForm 메시지 처리기


void ParticleForm::OnBnClickedChange()
{
	CString temp;
	if (Sample::Get()->pCurCtrl == nullptr)
	{
		AfxMessageBox(L"선택된 Ctrl이 없습네다.");
		return;
	}
	JPanel* pCtrl = Sample::Get()->pCurCtrl;
	if (pCtrl->m_Type == PARTICLE)
	{
		JParticleSystem* pParticle = (JParticleSystem*)pCtrl;
		CString strTemp;
		// Min StartPos
		GetDlgItemText(P_MinScale, strTemp);
		pParticle->m_fMinScale = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxScale, strTemp);
		pParticle->m_fMaxScale = (float)_wtof(strTemp.GetString());
		// Min StartPos
		GetDlgItemText(P_MINSTARTPOSX, strTemp);
		pParticle->m_vMinStartPos.x = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MINSTARTPOSY, strTemp);
		pParticle->m_vMinStartPos.y = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MINSTARTPOSZ, strTemp);
		pParticle->m_vMinStartPos.z = (float)_wtof(strTemp.GetString());
		// Max StartPos
		GetDlgItemText(P_MAXSTARTPOSX, strTemp);
		pParticle->m_vMaxStartPos.x = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MAXSTARTPOSY, strTemp);
		pParticle->m_vMaxStartPos.y = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MAXSTARTPOSZ, strTemp);
		pParticle->m_vMaxStartPos.z = (float)_wtof(strTemp.GetString());		
		//Turn Direction
		pParticle->m_bTurnX = m_pTurnX.GetCheck();
		pParticle->m_bTurnY = m_pTurnY.GetCheck();
		pParticle->m_bTurnZ = m_pTurnZ.GetCheck();
		//Min Color
		GetDlgItemText(P_MinColorX, strTemp);
		pParticle->m_vMinColor.x = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MinColorY, strTemp);
		pParticle->m_vMinColor.y = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MinColorZ, strTemp);
		pParticle->m_vMinColor.z = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MinColorW, strTemp);
		pParticle->m_vMinColor.w = (float)_wtof(strTemp.GetString());
		// Max Color
		GetDlgItemText(P_MaxColorX, strTemp);
		pParticle->m_vMaxColor.x = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxColorY, strTemp);
		pParticle->m_vMaxColor.y = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxColorZ, strTemp);
		pParticle->m_vMaxColor.z = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxColorW, strTemp);
		pParticle->m_vMaxColor.w = (float)_wtof(strTemp.GetString());
		// LifeTime
		GetDlgItemText(P_MinLifeTime, strTemp);
		pParticle->m_fMinLifeTime = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxLifeTime, strTemp);
		pParticle->m_fMaxLifeTime = (float)_wtof(strTemp.GetString());
		// Min Direction
		GetDlgItemText(P_MinDirectionX, strTemp);
		pParticle->m_vMinDirection.x = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MinDirectionY, strTemp);
		pParticle->m_vMinDirection.y = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MinDirectionZ, strTemp);
		pParticle->m_vMinDirection.z = (float)_wtof(strTemp.GetString());
		// Max Direction
		GetDlgItemText(P_MaxDirectionX, strTemp);
		pParticle->m_vMaxDirection.x = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxDirectionY, strTemp);
		pParticle->m_vMaxDirection.y = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxDirectionZ, strTemp);
		pParticle->m_vMaxDirection.z = (float)_wtof(strTemp.GetString());
		// Min Direction Angle
		GetDlgItemText(P_MinDirectionAngleX, strTemp);
		pParticle->m_qMinDirAngle.x = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MinDirectionAngleY, strTemp);
		pParticle->m_qMinDirAngle.y = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MinDirectionAngleZ, strTemp);
		pParticle->m_qMinDirAngle.z = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MinDirectionAngleW, strTemp);
		pParticle->m_qMinDirAngle.w = (float)_wtof(strTemp.GetString());
		// Max Direction Angle
		GetDlgItemText(P_MaxDirectionAngleX, strTemp);
		pParticle->m_qMaxDirAngle.x = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxDirectionAngleY, strTemp);
		pParticle->m_qMaxDirAngle.y = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxDirectionAngleZ, strTemp);
		pParticle->m_qMaxDirAngle.z = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxDirectionAngleW, strTemp);
		pParticle->m_qMaxDirAngle.w = (float)_wtof(strTemp.GetString());
		// MoveSpeed
		GetDlgItemText(P_MinMoveSpeed, strTemp);
		pParticle->m_fMinMoveSpeed = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxMoveSpeed, strTemp);
		pParticle->m_fMaxMoveSpeed = (float)_wtof(strTemp.GetString());
		// RotateSpeed
		GetDlgItemText(P_MinRotSpeed, strTemp);
		pParticle->m_fMinRotateSpeed = (float)_wtof(strTemp.GetString());
		GetDlgItemText(P_MaxRotSpeed, strTemp);
		pParticle->m_fMaxRotateSpeed = (float)_wtof(strTemp.GetString());
		// Max Particle Size
		// Max Particle가 전이랑 같으면 그냥 있고 다르면 다시계산.
		GetDlgItemText(P_MAXSIZE, strTemp);
		if (pParticle->m_pParticle.size() == (int)_wtoi(strTemp.GetString()))
		{
			return;
		}
		if (pParticle->m_pParticle.size() != (int)_wtoi(strTemp.GetString()))
		{
			pParticle->m_bRender = false;
			pParticle->m_iMaxParticle = (int)_wtoi(strTemp.GetString());
			pParticle->m_pParticle.clear();
			for (int iP = 0; iP < pParticle->m_iMaxParticle; iP++)
			{
				JParticle* pPar = new JParticle();
				pParticle->m_pParticle.push_back(pPar);
			}
			pParticle->m_bRender = true;
		}
		return;
	}
	AfxMessageBox(L"선택된 Ctrl은 이 기능 사용안해연");
}
