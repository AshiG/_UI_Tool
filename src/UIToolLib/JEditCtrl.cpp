#include "JEditCtrl.h"
#include "Input.h"
#include "WriteManager.h"
#include "Window.h"
#include "ime.h"
namespace UI
{
	bool JEditCtrl::Create(ID3D11Device* pDevice, float TextSize, const TCHAR* szNORMAL, const char* PSName, const TCHAR* szShaderName)
	{
		JImageCtrl::Create(pDevice, PSName, szShaderName);
		
		if (!JImageCtrl::SetTexture(pDevice, szNORMAL)) return false;

		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
		m_fSize = TextSize;
		return true;
	}
	void JEditCtrl::Play()
	{
		ime::Get()->imeEnd();

		m_bFocus = true;
		ime::Get()->imeStart();
		ime::Get()->SetLength(m_iMaxLength);
	}
	void JEditCtrl::End()
	{
		m_bFocus = false;
		ime::Get()->imeEnd();
	}
	void JEditCtrl::Clear()
	{
		m_Text.clear();
	}
	wstring JEditCtrl::GetString()
	{
		return m_Text;
	}
	void JEditCtrl::SetString(wstring strText)
	{
		m_Text = strText;
	}
	void JEditCtrl::Update()
	{
		#ifdef _DEBUG
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
		#endif

		if (Input::Get().GetKeyState(EMouseButton::Left) == EKeyState::DOWN)
		{
			this->End();
		}

		//if (m_pShape->Hovered(m_rt, m_ptMouse.Getpt()))
		//{
		//	if (EventHover.first != nullptr && m_bEvent)
		//		EventHover.first(EventHover.second);
		//}
		//if (m_pShape->Pressed(m_rt, m_ptMouse.Getpt()))
		//{
		//	this->Play();
		//	if (EventPress.first != nullptr && m_bEvent)
		//		EventPress.first(EventPress.second);
		//}
		//if (m_pShape->Clicked(m_rt, m_ptMouse.Getpt()))
		//{
		//	if (EventClick.first != nullptr && m_bEvent)
		//		EventClick.first(EventClick.second);
		//}
		if (CheckPressed())
		{
			this->Play();
		}
		/* 버튼 rect 안에서 write 출력 */
		RECT rt = Window::getClientRect();
		float width = ((rt.right / 2.0f) / (m_fWidth / 2.0f));
		float height = ((rt.bottom / 2.0f) / (m_fHeight / 2.0f));

		m_rtText.x = (m_vPos.x - m_vScl.x + (m_fWidth / 2.0f)) * width + 5.0f;
		m_rtText.y = (-m_vPos.y - m_vScl.y + (m_fHeight / 2.0f)) * height;
		m_rtText.z = (m_vPos.x + m_vScl.x + (m_fWidth / 2.0f)) * width;
		m_rtText.w = (-m_vPos.y + m_vScl.y + (m_fHeight / 2.0f)) * height;
		/* ime string save */
		if (m_bFocus)
		{
			m_Text = ime::Get()->GetString();
			//if (ime::Get()->GetString() == L"")
			//	ime::Get()->SetString(m_Text);
			//else if (m_Text.size() == 0)
			//{
			//	if (Input::Get().GetKeyState(VK_BACK) == EKeyState::DOWN)
			//	{
			//		ime::Get()->SetString(L"");
			//	}
			//}
			/* MaxLength */
			if (m_Text.size() == m_iMaxLength)
				ime::Get()->SetString(m_Text);
		}
		/* MaxLength 2 */
		if (m_iMaxLength > 0)
		{
			while (TRUE)
			{
				if (m_Text.size() > m_iMaxLength)
					m_Text.pop_back();
				else
					break;
			}
		}
		if (m_bPrivate)
		{
			m_strPrivate = m_Text;
			m_strPrivate.assign(m_strPrivate.size(), L'*');
		}
	}
	bool JEditCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
			if (!m_bRender) return false;
			JImageCtrl::Update();
			this->Update();
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JEditCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		if (!m_bRender) return false;
		JImageCtrl::Render(pContext);
		WriteManager::Get().SetFontColor(D2D1::ColorF::Black);
		WriteManager::Get().SetFontSizeAlign(m_fSize, m_Align, EAlign::Center);
		if (m_bPrivate)
		{
			WriteManager::Get().Draw(m_rtText, m_strPrivate);
		}
		else
		{
			WriteManager::Get().Draw(m_rtText, m_Text);
		}
		return true;
	}
	bool JEditCtrl::Release()noexcept
	{
		//m_pText.clear();
		//m_pTextrt.clear();
		//SAFE_DELETE(m_fValue);
		JImageCtrl::Release();
		return true;
	}
}
