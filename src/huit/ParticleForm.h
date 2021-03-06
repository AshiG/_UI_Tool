#pragma once


// ParticleForm 대화 상자

class ParticleForm : public CFormView
{
	DECLARE_DYNAMIC(ParticleForm)
public:
	static ParticleForm* m_pInstance;
	static ParticleForm* Get()
	{
		if (m_pInstance == nullptr) return nullptr;
		return m_pInstance;
	}
	static ParticleForm* CreateOne(CWnd* pParent);
public:
	ParticleForm();   // 표준 생성자입니다.
	virtual ~ParticleForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ParticleForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CButton m_pTurnX;
	CButton m_pTurnY;
	CButton m_pTurnZ;
	afx_msg void OnBnClickedChange();
};
