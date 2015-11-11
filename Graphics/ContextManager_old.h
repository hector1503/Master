#pragma once
#include <d3d11.h>

class CContextManager
{
private:
	ID3D11RenderTargetView *m_RenderTargetView;
	ID3D11Device *m_D3DDevice; // esta clase, el device, nos sirve para crear objetos de DirectX
	ID3D11DeviceContext *m_DeviceContext; // el contexto nos va a servir para usar objetos de DirectX
	IDXGISwapChain *m_SwapChain; // la cadena de swap
public:
	CContextManager::CContextManager(void);
	CContextManager::~CContextManager(void);

	

	HRESULT CrearContexto(HWND hWnd, int WIDTH_APPLICATION, int HEIGHT_APPLICATION);

	HRESULT CContextManager::CreateRenderTarget();

	void CContextManager::Draw(int WIDTH_APPLICATION, int HEIGHT_APPLICATION);

	ID3D11Device* CContextManager::GetDevice(){
		return m_D3DDevice;
	}

	ID3D11DeviceContext* CContextManager::GetDeviceContext(){
		return m_DeviceContext;
	}

	IDXGISwapChain* CContextManager::GetSwapChain(){
		return m_SwapChain;
}
	
};
