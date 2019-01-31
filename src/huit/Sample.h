#pragma once
#ifdef _DEBUG
#pragma comment( lib, "_CoreLib D3D_d.lib")
#pragma comment(lib,"UIToolLib_d.lib")
#else
#pragma comment( lib, "_CoreLib D3D.lib")
#pragma comment(lib,"UIToolLib.lib")
#endif

#include "CoreDX.h"
#include "JUIWriter.h"
#include "JUIReader.h"
/* ======================= */
#include "JLine.h"
#include "JSphere.h"
#include "JParser.h"
#include "uiheader.h"
#include "WriteManager.h"
#include "JSlotManager.h"
enum Type
{
	TRANS = 0,
	ROTATE,
	SCALE,
	FREE,
};
struct Hierarchy
{
	HTREEITEM hChild;
	wstring   strName;
};
class Sample : public Core
{
public:
	JUIWriter m_Write;
	JUIReader m_Read;
	JParser par;
public:
	JPanel* pRoot;
	JPanel* pCurCtrl;
	vector<JPanel*> pSelectList;
	//POINT m_ptMouse;
	Type m_Type = TRANS;
	Type m_BeforeType = TRANS;
	HTREEITEM hRoot;
	vector<Hierarchy> hChildList;
public:
	float m_fSaveElapseTime = 0.0f;
	float m_fSaveNoticeTime = 0.0f;
	bool  m_bSaveNotice = false;
public:
	D3DXVECTOR3 vpt0, vpt1;
	bool bCheck = false;
	bool bClick = false;
	JLine m_Line;
	JSphere m_Circle;
public:
	EVENT_LIST FindPointerFunc(wstring Event);
	wstring FindPointerFunc(EVENT_LIST Event);
	EAlign FindAlign(wstring type);
	wstring FindAlign(EAlign type);
	void InfoEventInit();
public:
	void SortCircuit(JPanel* pPanel);
	void SaveData(wstring SaveFileName);
	void LoadData(wstring LoadFileName);
	void EventCircuit(JPanel* pPanel, bool bValue);
	void TreeInitialization(JPanel* Panel);
	void TreeCircuit(JPanel* Panel);
	void ParentNameCircuit(JPanel* pParent);
public:
	void CreateButton(wstring NodeName, wstring ParentName);
	void CreateCheck(wstring NodeName, wstring ParentName);
	void CreateProgress(wstring NodeName, wstring ParentName);
	void CreateSlider(wstring NodeName, wstring ParentName);
	void CreateSprite(wstring NodeName, wstring ParentName);
	void CreateText(wstring NodeName, wstring ParentName);
	void CreateParticle(wstring NodeName, wstring ParentName);
	void CreatePanel(wstring NodeName, wstring ParentName);
	void CreateList(wstring NodeName, wstring ParentName);
	void CreateEdit(wstring NodeName, wstring ParentName);
	void CreateImage(wstring NodeName, wstring ParentName);
	void CreateSlot(wstring NodeName, wstring ParentName);
	void CreateInventory(wstring NodeName, wstring ParentName);
public:
	void SetKeyDownHold();
	wstring FindKeyDownHold(int iKey);
	wstring FindType();
	wstring FindVHType(VHType type);
	VHType FindVHType(wstring type);
	SpriteType FindSpriteType(wstring type);
	wstring FindSpriteType(SpriteType type);
	void pushSelect(JPanel* pPanel);
	void Update();
	void UpdateParticleInfo();
	void UpdateInfo();
	void ptTransition();
	void ptRotation();
	void ptScaling();
	void KeyTransition();
	void KeyRotation();
	void KeyScaling();
public:
	void IntroEvent();
	void LobbyEvent();
	void InGameEvent();
	void MsgEvent(const MSG& _message) noexcept;
	virtual bool Init()		noexcept override;
	virtual bool Frame()	noexcept override;
	virtual bool Render()	noexcept override;
	virtual bool Release()	noexcept override;
public:
	static Sample* m_pInstance;
	static Sample* Get()
	{
		if (m_pInstance == nullptr)
		{
			Sample* pInst = new Sample();
			m_pInstance = pInst;
		}
		return m_pInstance;
	}
private:
	Sample();
public:
	virtual ~Sample();
};

