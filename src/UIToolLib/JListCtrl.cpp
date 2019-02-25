#include "JListCtrl.h"
#include "Window.h"
namespace UI
{
	void* JListCtrl::uiclone()
	{
		return new JListCtrl(*this);
	}
	bool JListCtrl::Create(ID3D11Device* pDevice, const TCHAR* szNORMAL, float fSize, const int iCols, const char* PSName, const TCHAR* szShaderName)
	{
		JImageCtrl::Create(pDevice, PSName, szShaderName);
		if (!SetTexture(pDevice, szNORMAL))  return false;
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
		m_fSize = fSize;
		m_iCols = iCols;
		m_pTextrt.resize(iCols);
		m_pText.resize(iCols);
		m_fValue = &m_fTemp;
		return true;
	}
	void JListCtrl::SetColumn(const int iCols)
	{
		m_iCols = iCols;
		m_pTextrt.clear();
		m_pText.clear();
		m_pTextrt.resize(iCols);
		m_pText.resize(iCols);
	}
	void JListCtrl::AddValue(const float value)
	{
		*m_fValue += value;
	}
	void JListCtrl::push_string(wstring str)
	{
		m_pText.push_front(str);
	}
	void JListCtrl::Update()
	{
#ifdef _DEBUG
		m_pTexture = I_TexMgr.GetPtr(m_pIndexList[txNORMAL]);
#endif
		//if (m_pShape->Hovered(m_rt, m_ptMouse.Getpt()))
		//{
		//	if (EventHover.first != nullptr && m_bEvent)
		//		EventHover.first(EventHover.second);
		//}
		//if (m_pShape->Pressed(m_rt, m_ptMouse.Getpt()) ||
		//	Input::Get().GetKeyState(m_pKeyHold) == EKeyState::HOLD)
		//{
		//	if (EventPress.first != nullptr && m_bEvent)
		//		EventPress.first(EventPress.second);
		//}
		//if (m_pShape->Clicked(m_rt, m_ptMouse.Getpt()) ||
		//	Input::Get().GetKeyState(m_pKeyDown) == EKeyState::UP)
		//{
		//	if (EventClick.first != nullptr && m_bEvent)
		//		EventClick.first(EventClick.second);
		//}
		RECT rt = Window::getClientRect();
		float width = ((rt.right / 2.0f) / (m_fWidth / 2.0f));
		float height = ((rt.bottom / 2.0f) / (m_fHeight / 2.0f));
		// left right =  button.rt 고정
		// top bottom = button.rt / col 만큼씩이동
		D3DXVECTOR4 temp;
		temp.x = ((m_vPos.x - m_vScl.x + (m_fWidth / 2.0f)) * width);
		temp.y = ((-m_vPos.y - m_vScl.y + (m_fHeight / 2.0f)) * height) / m_iCols;
		temp.z = ((m_vPos.x + m_vScl.x + (m_fWidth / 2.0f)) * width);
		temp.w = ((-m_vPos.y + m_vScl.y + (m_fHeight / 2.0f)) * height) / m_iCols;

		// button 맨 밑부터 증가
		D3DXVECTOR2 yPos;
		yPos.x = ((-m_vPos.y - m_vScl.y + (m_fHeight / 2.0f)) * height) + ((temp.w - temp.y) * (m_iCols - 1));
		yPos.y = ((-m_vPos.y + m_vScl.y + (m_fHeight / 2.0f)) * height);
		for (int iCol = 0; iCol < m_iCols; iCol++)
		{
			m_pTextrt[iCol].x = temp.x + 10.0f;
			m_pTextrt[iCol].y = yPos.x - ((temp.w - temp.y) * iCol);
			m_pTextrt[iCol].z = temp.z;
			m_pTextrt[iCol].w = yPos.y - ((temp.w - temp.y) * iCol);
		}
		// 100 줄 제한.
		if (m_pText.size() > 100)
		{
			m_pText.pop_back();
		}

		//// 값 제한.
		//if (m_fValue >= 1.0f)
		//{
		//	m_fValue = 1.0f;
		//}
		//else if (m_fValue <= 0.0f)
		//{
		//	m_fValue = 0.0f;
		//}
		fDivisionValue = 1.0f / ((float)m_pText.size() - m_iCols - m_iCols);
	}
	bool JListCtrl::Frame(const float& spf, const float& accTime) noexcept
	{
		JPanel::PreFrame(spf, accTime);
		{
		if (!m_bRender) return false;
			this->Update();
		}
		JPanel::PostFrame(spf, accTime);
		return true;
	}
	bool JListCtrl::Render(ID3D11DeviceContext* pContext) noexcept
	{
		if (!m_bRender) return false;
		JImageCtrl::Render(pContext);
		auto iter = m_pText.begin();
		float fCurValue = 0.0f;
		// float fDivisionValue = 1.0f / ((float)m_pText.size() - m_iCols - m_iCols);
		// slider value에 따라서 string iterator 이동 value = 0 ~ 1
		while (fCurValue < *m_fValue)
		{
			if (fDivisionValue <= 0.0f) break;
			iter++;
			fCurValue += fDivisionValue;
		}
		// 중앙 세팅
		WriteManager::Get().SetFontColor(D2D1::ColorF::Black);
		WriteManager::Get().SetFontSizeAlign(m_fSize, m_Align, EAlign::Center);
		for (int iCol = 0; iCol < m_iCols; iCol++)
		{
			WriteManager::Get().Draw(m_pTextrt[iCol], *(iter++));
		}
		return true;
	}
	bool JListCtrl::Release()noexcept
	{
		//m_pText.clear();
		//m_pTextrt.clear();
		//SAFE_DELETE(m_fValue);
		JImageCtrl::Release();
		return true;
	}
}
