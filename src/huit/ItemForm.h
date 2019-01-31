#pragma once


// ItemForm 대화 상자

class ItemForm : public CFormView
{
	DECLARE_DYNAMIC(ItemForm)
public:
	static ItemForm* m_pInstance;
	static ItemForm* Get()
	{
		if (m_pInstance == nullptr) return nullptr;
		return m_pInstance;
	}
	static ItemForm* CreateOne(CWnd* pParent);
public:
	ItemForm();   // 표준 생성자입니다.
	virtual ~ItemForm();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ItemForm };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
