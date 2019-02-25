#include "JPlane.h"
#include "Input.h"
#include "DxManager.h"
namespace UI
{
	bool JPlane::Hovered(RECT& rt, POINT& pt)
	{
		if (JDxHelper::RectInPt(rt, pt))
		{
			return true;
		}
		return false;
	}
	bool JPlane::Pressed(RECT& rt, POINT& pt)
	{
		if (Input::GetKeyState(EMouseButton::Left) == EKeyState::HOLD)
		{
			if (JDxHelper::RectInPt(rt, pt))
			{
				return true;
			}
		}
		return false;
	}
	bool JPlane::Clicked(RECT& rt, POINT& pt)
	{
		if (Input::GetKeyState(EMouseButton::Left) == EKeyState::UP)
		{
			if (JDxHelper::RectInPt(rt, pt))
			{
				return true;
			}
		}
		return false;
	}
	//bool JPlane::CheckHovered()
	//{
	//	return m_bHovered;
	//}
	//bool JPlane::CheckPressed()
	//{
	//	return m_bPressed;
	//}
	//bool JPlane::CheckClicked()
	//{
	//	return m_bClicked;
	//}
	void JPlane::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
	{
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixRotationYawPitchRoll(&m_matWorld, m_vRot.x, m_vRot.y, m_vRot.z);
		if (pWorld != nullptr)
		{
			m_matWorld = m_matWorld * (*pWorld);
		}

		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
		D3DXMatrixTranspose(&m_cbData.matView, pView);
		D3DXMatrixTranspose(&m_cbData.matProj, pProj);
	}
	bool JPlane::Frame()
	{
		return true;
	}
	bool JPlane::PreRender(ID3D11DeviceContext* pContext)
	{
		JModel::PreRender(pContext);
		return true;
	}
	bool JPlane::Render(ID3D11DeviceContext* pContext, JTexture* pTexture)
	{
		this->PreRender(pContext);
		{
			if(pTexture != nullptr)
				pContext->PSSetShaderResources(0, 1, &pTexture->m_pSRV);
			pContext->UpdateSubresource(JPlane::m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
			pContext->UpdateSubresource(JPlane::m_pVertexBuffer, 0, NULL, &m_pVertices.at(0), 0, 0);
		}
		this->PostRender(pContext);
		return true;
	}
	bool JPlane::PostRender(ID3D11DeviceContext* pContext)
	{
		JModel::PostRender(pContext);
		return true;
	}
	bool JPlane::Create(ID3D11Device* pDevice, const char* PSName, const TCHAR* szShaderName)
	{
		m_pVertices.resize(4);
		m_pVertices[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),   D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
		m_pVertices[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 0.0f),   D3DXVECTOR3(0.0f, 0.0f, -1.0f),   D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
		m_pVertices[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 0.0f),  D3DXVECTOR3(0.0f, 0.0f, -1.0f),   D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
		m_pVertices[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f),   D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
		m_iVertexNum = (UINT)m_pVertices.size();
		m_iVertexSize = sizeof(UI::PNCT_VERTEX);

		m_pIndices.resize(6);
		m_pIndices[0] = 0; m_pIndices[1] = 1; m_pIndices[2] = 2;
		m_pIndices[3] = 0; m_pIndices[4] = 2; m_pIndices[5] = 3;
		m_iIndexNum = (UINT)m_pIndices.size();
		m_iIndexSize = sizeof(DWORD);

		m_pVertexBuffer = UI::CreateVertexBuffer(pDevice, &m_pVertices.at(0), m_iVertexSize, m_iVertexNum);
		m_pIndexBuffer = UI::CreateIndexBuffer(pDevice, &m_pIndices.at(0), m_iIndexSize, m_iIndexNum);
		m_pConstantBuffer = UI::CreateConstantBuffer(pDevice, &m_cbData, sizeof(VSCB), 1);
		m_pVS = UI::LoadVertexShader(pDevice, szShaderName, &m_BlobVS, "VS");
		m_pPS = UI::LoadPixelShader(pDevice, szShaderName, &m_BlobPS, PSName);

		D3D11_INPUT_ELEMENT_DESC ied[] =
		{
			{ "POSITION",	 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "NORMAL",		 0, DXGI_FORMAT_R32G32B32_FLOAT,	0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR",		 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",	 0, DXGI_FORMAT_R32G32_FLOAT,		0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		int ElementCnt = sizeof(ied) / sizeof(ied[0]);
		m_pIL = UI::CreateLayout(pDevice, ied, ElementCnt, m_BlobVS);

		m_cbData.vColor = D3DXVECTOR4(1, 1, 1, 1);
		return true;
	}
	JPlane::JPlane()
	{
	}

	JPlane::~JPlane()
	{
	}
}