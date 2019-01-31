#include "JLine.h"

namespace UI
{
	void JLine::SetMatrix(D3DXMATRIX* matWorld, D3DXMATRIX* matView, D3DXMATRIX* matProj)
	{
		if (matWorld != NULL)
			m_matWorld = *matWorld;
		if (matView != NULL)
			m_matView = *matView;
		if (matProj != NULL)
			m_matProj = *matProj;

		D3DXMatrixTranspose(&m_cbData.matWorld, &m_matWorld);
		D3DXMatrixTranspose(&m_cbData.matView, &m_matView);
		D3DXMatrixTranspose(&m_cbData.matProj, &m_matProj);
	}
	bool JLine::PreRender(ID3D11DeviceContext* pContext)
	{
		JModel::PreRender(pContext);
		return true;
	}
	bool JLine::Render(ID3D11DeviceContext* pContext)
	{
		this->PreRender(pContext);
		{
			pContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &m_cbData, 0, 0);
		}
		pContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		this->PostRender(pContext);
		return true;
	}
	bool JLine::PostRender(ID3D11DeviceContext* pContext)
	{
		JModel::PostRender(pContext);
		return true;
	}
	bool JLine::Draw(ID3D11DeviceContext* pContext, D3DXVECTOR3 vPos, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor)
	{
		PNCT_VERTEX vertex[2];
		vertex[0].p = vPos;
		vertex[1].p = vEnd;
		m_cbData.vColor = vColor;
		pContext->UpdateSubresource(m_pVertexBuffer, 0, NULL, &vertex, 0, 0);
		Render(pContext);
		return true;
	}
	bool JLine::Create(ID3D11Device* pDevice, const char* PSName, const TCHAR* szShaderName)
	{
		m_pVertices.resize(2);
		m_pVertices[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(-1.0f, -1.0f));
		m_pVertices[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f), D3DXVECTOR2(1.0f, -1.0f));
		m_iVertexNum = (UINT)m_pVertices.size();
		m_iVertexSize = sizeof(UI::PNCT_VERTEX);

		m_pIndices.resize(2);
		m_pIndices[0] = 0; m_pIndices[1] = 1;
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
}
