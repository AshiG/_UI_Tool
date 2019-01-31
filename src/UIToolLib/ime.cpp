#include "ime.h"
namespace UI
{
	ime* ime::m_pInstance = nullptr;

	bool ime::Set(HWND hWnd)
	{
		if (hWnd == nullptr) return false;
		m_hWnd = hWnd;
		m_hIMC = ImmGetContext(m_hWnd);
		return true;
	}
	wstring ime::GetString()
	{
		wstring Complate = m_CompString + m_CompWord;
		if (m_iMaxLength > 0)
		{
			while (TRUE)
			{
				if (Complate.size() > m_iMaxLength)
					Complate.pop_back();
				else
					break;
			}
		}
		return Complate;
	}
	bool ime::GetPlay()
	{
		return m_bPlay;
	}
	void ime::SetLength(const int iLength)
	{
		m_iMaxLength = iLength;
	}
	void ime::SetString(wstring str)
	{
		m_CompString = str;
	}
	void ime::imeStart()
	{
		m_bPlay = true;
	}
	void ime::imeEnd()
	{
		m_bPlay = false;
		m_iMaxLength = 0;
		m_CompString.clear();
		m_CompWord.clear();
	}
	int ime::WndProc(MSG msg)
	{
		if (!m_bPlay) return 1;
		int len;
		switch (msg.message)
		{
		case WM_IME_STARTCOMPOSITION: // 조합 시작
		{
			m_CompWord.clear(); // 조합 중 문자 초기화
		}
		case WM_IME_ENDCOMPOSITION: // 조합 끝
		{
			m_CompWord = (wchar_t)msg.wParam; // 완성문자 추가
		}
		case WM_IME_COMPOSITION: // 조합 중
		{
			//if (msg.lParam & GCS_RESULTSTR) // 완성되면?
			//{
				//TCHAR szBackup[10] = {0,};
				//len = ImmGetCompositionString(m_hIMC, GCS_RESULTSTR, NULL, 0); // IME스트링길이를얻음

				//ImmGetCompositionString(m_hIMC, GCS_RESULTSTR, szBackup, len); // 완성된 문자입력

				//if (len > 0)
				//{
				//	m_CompString += szBackup; // 아래 WM_CHAR에서 2번 추가됨.....
				//}

			//}
			//else
			if (msg.lParam & GCS_COMPSTR) // 조합 중 이면
			{
				TCHAR szBackup[10] = { 0, };
				len = ImmGetCompositionString(m_hIMC, GCS_COMPSTR, NULL, 0); // 조합 중인 길이 얻음

				ImmGetCompositionString(m_hIMC, GCS_COMPSTR, szBackup, len); // 문자열 입력
				m_CompWord = szBackup;
			}
			ImmReleaseContext(m_hWnd, m_hIMC); // 핸들반환
			return 0;
		}
		case WM_CHAR: // 문자넘어옴
		{
			switch (msg.wParam)
			{
			case VK_BACK: // backspace
			{
				if (m_CompWord.size() > 0)
				{
					m_CompWord.pop_back(); // 한글자 지움
				}
				else if (m_CompString.size() > 0)
				{
					m_CompString.pop_back();
				}
				break;
			}
			case VK_RETURN:
			{

			}break;
			default:
			{
				m_CompString += (wchar_t)msg.wParam;
				break;
			}
			}
			return 0;
		}
		}
		return 1;
	}

	ime::ime()
	{
	}


	ime::~ime()
	{
	}

}