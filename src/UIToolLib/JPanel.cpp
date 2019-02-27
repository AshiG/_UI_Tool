#include "JPanel.h"
#include "ObjectManager.h"
namespace UI
{
	void JPanel::UpdateButtonState()
	{
		if (m_pShape == nullptr) return;

		m_bHovered = m_pShape->Hovered(m_rt, m_ptMouse.Getpt());
		m_bPressed = m_pShape->Pressed(m_rt, m_ptMouse.Getpt());
		m_bClicked = m_pShape->Clicked(m_rt, m_ptMouse.Getpt());

		if (CheckHovered())
		{
			if (EventHover.first != nullptr && m_bEvent)
				EventHover.first(EventHover.second);
		}
		if (CheckPressed() || Input::Get().GetKeyState(m_pKeyHold) == EKeyState::HOLD)
		{
			if (EventPress.first != nullptr && m_bEvent)
				EventPress.first(EventPress.second);
		}
		if (CheckClicked() || Input::Get().GetKeyState(m_pKeyDown) == EKeyState::UP)
		{
			if (EventClick.first != nullptr && m_bEvent)
				EventClick.first(EventClick.second);
		}
	}
	bool JPanel::CheckHovered()
	{
		if (m_pShape == nullptr) return false;
		return m_bHovered;
	}
	bool JPanel::CheckPressed()
	{
		if (m_pShape == nullptr) return false;
		return m_bPressed;
	}
	bool JPanel::CheckClicked()
	{
		if (m_pShape == nullptr) return false;
		return m_bClicked;
	}
	void JPanel::SetColor(const D3DXVECTOR4 vColor)
	{
		if (m_pShape != nullptr)
			m_pShape->m_cbData.vColor = vColor;
	}
	void JPanel::SetEventTime(const float fTime)
	{
		m_fEventTime = fTime;
	}
	float JPanel::GetEventTime()
	{
		return m_fEventTime;
	}
	void JPanel::EffectPlay()
	{
		m_bEffect = true;
	}
	void* JPanel::uiclone()
	{
		return new JPanel(*this);
	}
	void JPanel::rtUpdate()
	{
		m_rt.left   = (LONG)(m_matWorld._41 - m_matWorld._11);
		m_rt.right  = (LONG)(m_matWorld._41 + m_matWorld._11);
		m_rt.top    = (LONG)(m_matWorld._42 - m_matWorld._22);
		m_rt.bottom = (LONG)(m_matWorld._42 + m_matWorld._22);

		/* Rect가 LR로 뒤집어졌을 경우 */
		if (m_rt.right < m_rt.left)
		{
			LONG Temp = m_rt.right;
			m_rt.right = m_rt.left;
			m_rt.left = Temp;
		}
		/* Rect가 LR로 뒤집어졌을 경우 */
		if (m_rt.top < m_rt.bottom)
		{
			LONG Temp = m_rt.top;
			m_rt.top = m_rt.bottom;
			m_rt.bottom = Temp;
		}
	}
	void JPanel::Update()
	{
		rtUpdate();
		// 부모 행렬 곱
		//D3DXMATRIX matParent;
		//D3DXMatrixIdentity(&matParent);
		D3DXMATRIX matParentTrans;
		D3DXMatrixIdentity(&matParentTrans);
		if (m_pParent != nullptr)
		{
			//matParent = m_pParent->m_matWorld;
			matParentTrans = m_pParent->m_matTrans;
			//matParent._43 = 0.0f;
		}

		// matWorld 갱신
		D3DXMatrixScaling(&m_matScl, m_vScl.x, m_vScl.y, m_vScl.z);
		D3DXMatrixRotationYawPitchRoll(&m_matRot, m_vRot.x, m_vRot.y, m_vRot.z);
		D3DXMatrixTranslation(&m_matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

		m_matTrans *= matParentTrans;

		m_matWorld = m_matScl * m_matRot * m_matTrans;

		//m_matWorld = matParent * m_matWorld;
	}
	bool JPanel::SetParent(JPanel* pParent)
	{
		if (pParent == nullptr) return false;

		m_pParent = pParent;
		m_ParentName = pParent->m_NodeName;
		pParent->m_pChildList.push_back(this);
		return true;
	}
	void JPanel::push_child(JPanel* pChild)
	{
		if (pChild == nullptr) return;
		pChild->m_pParent = this;
		pChild->m_ParentName = this->m_NodeName;
		m_pChildList.push_back(pChild);
		pChild->m_iNumRender = (int)m_pChildList.size() - 1;
	}
	JPanel* JPanel::find_root()
	{
		JPanel* pRoot = this;
		while (TRUE)
		{
			if (pRoot->m_pParent == nullptr)
				return pRoot;
			pRoot = pRoot->m_pParent;
		}
	}
	JPanel* JPanel::find_child(wstring childname)
	{
		if (m_NodeName == childname) 
			return this;

		for (auto iC = m_pChildList.begin(); iC != m_pChildList.end(); iC++)
		{
			JPanel* pChild = (*iC)->find_child(childname);
			if (pChild != nullptr) 
				return pChild;
		}
		return nullptr;
	}
	bool JPanel::Init() noexcept
	{
		GameObject::Init();
		return true;
	}
	bool JPanel::PreFrame(const float& spf, const float& accTime)
	{
		m_ptMouse.Update(m_fWidth, m_fHeight);
		if (PreEvent.first != nullptr && m_bEvent)
			PreEvent.first(PreEvent.second);

		if (!m_bRender) return false;
		GameObject::Frame(spf, accTime);
		Update();

		return true;
	}
	bool JPanel::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JPanel::PostFrame(const float& spf, const float& accTime)
	{
		if (!m_bRender) return false;

		UpdateButtonState();

		if (PostEvent.first != nullptr && m_bEvent)
			PostEvent.first(PostEvent.second);

		for (auto iC = m_pChildList.begin(); iC != m_pChildList.end(); iC++)
		{
			(*iC)->Frame(spf, accTime);
		}
		return true;
	}
	bool JPanel::Render(ID3D11DeviceContext* pContext)noexcept
	{
		if (!m_bRender) return false;
		GameObject::Render(pContext);
		for (auto iC = m_pChildList.begin(); iC != m_pChildList.end(); iC++)
		{
			(*iC)->Render(pContext);
		}
		return true;
	}
	bool JPanel::Release() noexcept
	{
		for (auto iC = m_pChildList.begin(); iC != m_pChildList.end(); iC++)
		{
			(*iC)->Release();
		}
		return true;
	}
	JPanel::JPanel(wstring NodeName)
	{
		m_Type = UI::PANEL;
		m_objType = EObjType::UI;
		m_NodeName = NodeName;
		UI::JTransform::m_pCurTransform = new JTransform();
		D3DXMatrixIdentity(&m_matScl);
		D3DXMatrixIdentity(&m_matRot);
		D3DXMatrixIdentity(&m_matTrans);
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixIdentity(&m_matView);
		D3DXMatrixIdentity(&m_matProj);

		/* UI 전용 view proj create */
		D3DXVECTOR3 vPos = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		D3DXVECTOR3 vTarget = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 vUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		m_fWidth = 800.0f;
		m_fHeight = 600.0f;
		D3DXMatrixLookAtLH(&m_matView, &vPos, &vTarget, &vUp);
		D3DXMatrixOrthoOffCenterLH(&m_matProj, -m_fWidth / 2.0f, m_fWidth / 2.0f, -m_fHeight / 2.0f, m_fHeight / 2.0f, -10, 1000);

		///* Default Event */
		//EventHover.first   = E_DEFAULT;
		//EventHover.second  = this;
		//EventPress.first   = E_DEFAULT;
		//EventPress.second = this;
		//EventClick.first   = E_DEFAULT;
		//EventClick.second = this;
		//PreEvent.first     = E_DEFAULT;
		//PreEvent.second = this;
		//PostEvent.first    = E_DEFAULT;
		//PostEvent.second = this;
	}
	JPanel::~JPanel()
	{
	}
}