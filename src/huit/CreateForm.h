#pragma once


// CreateForm 대화 상자
#include "huit.h"
class CreateForm : public CFormView
{
	DECLARE_DYNAMIC(CreateForm)
public:
	static CreateForm* m_pInstance;
	static CreateForm* Get()
	{
		if (m_pInstance == nullptr) return nullptr;
		return m_pInstance;
	}
	static CreateForm* CreateOne(CWnd* pParent);
public:
	CreateForm();   // 표준 생성자입니다.
	virtual ~CreateForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CreateForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedCbutton();
	afx_msg void OnBnClickedCcheck();
	afx_msg void OnBnClickedCprogress();
	afx_msg void OnBnClickedCslider();
	afx_msg void OnBnClickedCsprite();
	afx_msg void OnBnClickedCtext();
	afx_msg void OnBnClickedCparticle();
	afx_msg void OnBnClickedCpanel();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedLoad();
	afx_msg void OnBnClickedCtrlDelete();
	afx_msg void OnBnClickedClist();
	afx_msg void OnBnClickedEdit();
	afx_msg void OnBnClickedImage();
	afx_msg void OnBnClickedCslot();
	afx_msg void OnBnClickedCinventory();
};
