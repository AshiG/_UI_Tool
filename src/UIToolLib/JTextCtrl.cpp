#include "JTextCtrl.h"
#include "WriteManager.h"
#include "Window.h"
namespace UI
{
	void* JTextCtrl::uiclone()
	{
		return new JTextCtrl(*this);
	}
	bool JTextCtrl::Create(ID3D11Device* pDevice, wstring Text, float TextSize, const TCHAR* szNORMAL, const TCHAR* szHOVER, const TCHAR* szPRESS,
		const char* PSName, const TCHAR* szShaderName)
	{
		JButtonCtrl::Create(pDevice, szNORMAL, szHOVER, szPRESS, PSName, szShaderName);

		m_Text = Text;
		m_fSize = TextSize;
		return true;
	}
	wstring JTextCtrl::GetString()
	{
		return m_Text;
	}
	void JTextCtrl::SetString(wstring strData)
	{
		m_Text = strData;
	}
	void JTextCtrl::Update()
	{
		/* 버튼 rect 안에서 write 출력 */
		RECT rt = Window::getClientRect();
		float width = ((rt.right / 2.0f) / (m_fWidth / 2.0f));
		float height = ((rt.bottom / 2.0f) / (m_fHeight / 2.0f));

		//m_rtText.x = (m_vPos.x * width) - m_vScl.x + (rt.right / 2.0f);
		//m_rtText.y = (-m_vPos.y * height) - m_vScl.y + (rt.bottom / 2.0f);
		//m_rtText.z = (m_vPos.x * width) + m_vScl.x + (rt.right / 2.0f);
		//m_rtText.w = (-m_vPos.y * height) + m_vScl.y + (rt.bottom / 2.0f);

		D3DXVECTOR2 vPos;
		vPos.x = m_vPos.x + m_pParent->m_vPos.x;
		vPos.y = m_vPos.y + m_pParent->m_vPos.y;

		m_rtText.x = ((vPos.x - m_vScl.x + (m_fWidth / 2.0f)) * width);
		m_rtText.y = (-vPos.y - m_vScl.y + (m_fHeight / 2.0f)) * height;
		m_rtText.z = (vPos.x + m_vScl.x + (m_fWidth / 2.0f)) * width;
		m_rtText.w = (-vPos.y + m_vScl.y + (m_fHeight / 2.0f)) * height;
	}
	bool JTextCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
		if (!m_bRender) return false;
			JButtonCtrl::Update();
			this->Update();
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JTextCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		if (!m_bRender) return false;
		JButtonCtrl::Render(pContext);
		WriteManager::Get().SetFontColor(D2D1::ColorF::Black);
		WriteManager::Get().SetFontSizeAlign(m_fSize, m_Align, EAlign::Center);
		WriteManager::Get().Draw(D3DXVECTOR4(m_rtText.x - 1, m_rtText.y - 1, m_rtText.z - 1, m_rtText.w - 1), m_Text);
		WriteManager::Get().Draw(D3DXVECTOR4(m_rtText.x + 1, m_rtText.y + 1, m_rtText.z + 1, m_rtText.w + 1), m_Text);
		WriteManager::Get().SetFontColor(D2D1::ColorF::White);
		WriteManager::Get().Draw(m_rtText, m_Text);
		return true;
	}
	bool JTextCtrl::Release()noexcept
	{
		JButtonCtrl::Release();
		return true;
	}
}