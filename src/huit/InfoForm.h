#pragma once
#include "stdui.h"

// InfoForm 대화 상자

class InfoForm : public CFormView
{
	DECLARE_DYNAMIC(InfoForm)
public:
	static InfoForm* m_pInstance;
	static InfoForm* Get()
	{
		if (m_pInstance == nullptr) return nullptr;
		return m_pInstance;
	}
	static InfoForm* CreateOne(CWnd* pParent);
public:
	InfoForm();   // 표준 생성자입니다.
	virtual ~InfoForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_InfoForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_pSpriteList;
	T_STR_VECTOR m_pSpritePath;
	afx_msg void OnEnChangePosz();
	afx_msg void OnEnChangePosx();
	afx_msg void OnEnChangePosy();
	afx_msg void OnEnChangeRotx();
	afx_msg void OnEnChangeRoty();
	afx_msg void OnEnChangeRotz();
	afx_msg void OnEnChangeSclx();
	afx_msg void OnEnChangeScly();
	afx_msg void OnEnChangeSclz();
	afx_msg void OnBnClickedNormalChange();
	afx_msg void OnBnClickedHoverChange();
	afx_msg void OnBnClickedPressChange();
	afx_msg void OnBnClickedNameChange();
	afx_msg void OnEnChangeFindtxnormal();
	afx_msg void OnEnChangeFindtxhover();
	afx_msg void OnEnChangeFindtxpress();
	afx_msg void OnEnChangeFindSprite();
	afx_msg void OnBnClickedSpriteChange();
	afx_msg void OnBnClickedSpriteClear();
	afx_msg void OnBnClickedSpriteanimChange();
	afx_msg void OnBnClickedTextstringChange();
	CButton m_bRender;
	afx_msg void OnBnClickedCheck1();
	afx_msg void OnBnClickedNumrenderChange();
	CComboBox m_pfClick;
	afx_msg void OnBnClickedClickChange();
	CComboBox m_pfPress;
	CComboBox m_pfHover;
	afx_msg void OnBnClickedEventpressChange();
	afx_msg void OnBnClickedEventhoverChange();
	CButton m_GameMode;
	afx_msg void OnBnClickedEventon();
	afx_msg void OnBnClickedEventoff();
	CComboBox m_VHType;
	afx_msg void OnBnClickedVhtypeChange();
	afx_msg void OnEnChangeValue();
	afx_msg void OnBnClickedListcolumnChange();
	CComboBox m_SpriteType;
	afx_msg void OnBnClickedSpritetypeChange();
	afx_msg void OnBnClickedSpriterowcolChange();
	CButton m_pSpriteLoop;
	afx_msg void OnBnClickedSpriteplay();
	afx_msg void OnBnClickedKeyChange();
	CComboBox m_KeyHold;
	CComboBox m_KeyDown;
	afx_msg void OnEnChangeColorx();
	afx_msg void OnEnChangeColory();
	afx_msg void OnEnChangeColorz();
	afx_msg void OnEnChangeColorw();
	CButton m_PassWord;
	afx_msg void OnBnClickedPassword();
	CComboBox m_Align;
	afx_msg void OnBnClickedInvenrowcolChange();
	afx_msg void OnBnClickedAddslot();
	afx_msg void OnEnChangeFindtxitem();
	afx_msg void OnBnClickedSlotclear();
	afx_msg void OnBnClickedSlotdelete();
	afx_msg void OnBnClickedSlotsort();
	afx_msg void OnEnChangeSubsclx();
	afx_msg void OnEnChangeSubscly();
	afx_msg void OnEnChangeSubsclz();
	CButton m_Decrease;
};
