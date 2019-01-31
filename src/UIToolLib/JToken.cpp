#include "JToken.h"

namespace UI
{
	bool JToken::LoadFile(const TCHAR* szFileName)
	{
		HANDLE hRead = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

		if (hRead == INVALID_HANDLE_VALUE)
		{
			CloseHandle(hRead);
			return false;
		}

		GetFileSizeEx(hRead, &m_iFileSize);
		m_pData = new char[m_iFileSize.QuadPart];

		if (m_pData == NULL)
		{
			SAFE_DELETE(m_pData);
			CloseHandle(hRead);
			return false;
		}

		if (FALSE == ReadFile(hRead, m_pData, (DWORD)m_iFileSize.QuadPart, 0, 0))
		{
			SAFE_DELETE(m_pData);
			CloseHandle(hRead);
			return false;
		}
		CloseHandle(hRead);

		if (m_pData == NULL) return false;
		string pData = m_pData;
		string strToken = "^";
		size_t start = pData.find_first_not_of(strToken);
		size_t end = pData.find_first_of(strToken, start);
		for (; start < pData.size(); start = pData.find_first_not_of(strToken, end))
		{
			end = pData.find_first_of(strToken, start);

			string Token = pData.substr(start, end - start);
			m_pTokenList.push_back(Token);
		}
		m_dwMaxTokenLine = (DWORD)m_pTokenList.size();
		return true;
	}
	const char* JToken::GetNextToken()
	{
		m_CurrentToken = m_pTokenList[m_dwTokenIndex++];
		return m_CurrentToken.c_str();
	}
	INT JToken::FindToken(string szToken)
	{
		int EndLine = m_dwMaxTokenLine;
		INT retIndex = -1;
		while (EndLine > m_dwTokenIndex)
		{
			GetNextToken();
			if (NULL != strstr(m_CurrentToken.c_str(), szToken.c_str()))
			{
				retIndex = m_dwTokenIndex - 1;
				break;
			}
		}
		if (EndLine < m_dwTokenIndex) return -1;
		return retIndex;
	}
	INT JToken::GetLine(string szToken)
	{
		char szTemp[256] = { 0, };
		INT retIndex = -1;
		strcpy(szTemp, szToken.c_str());
		if (m_dwTokenIndex + 1 < m_pTokenList.size())
		{
			m_CurrentToken = m_pTokenList[m_dwTokenIndex++];
		}
		if (NULL != strstr(m_CurrentToken.c_str(), szToken.c_str()))
		{
			retIndex = m_dwTokenIndex - 1;
			return retIndex;
		}
		--m_dwTokenIndex;
		return retIndex;
	}
}