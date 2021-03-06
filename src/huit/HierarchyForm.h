#pragma once


// HierarchyForm 대화 상자

class HierarchyForm : public CFormView
{
	DECLARE_DYNAMIC(HierarchyForm)
public:
	static HierarchyForm* m_pInstance;
	static HierarchyForm* Get()
	{
		if (m_pInstance == nullptr) return nullptr;
		return m_pInstance;
	}
	static HierarchyForm* CreateOne(CWnd* pParent);
public:
	HierarchyForm();   // 표준 생성자입니다.
	virtual ~HierarchyForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HierarchyForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTreeCtrl m_HierarchyTree;
	afx_msg void OnNMDblclkHierarchytree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickHierarchytree(NMHDR *pNMHDR, LRESULT *pResult);
};
