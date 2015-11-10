#include "ContextManager.h"

CContextManager::CContextManager(void)
{
	m_D3DDevice=0; // esta clase, el device, nos sirve para crear objetos de DirectX
	m_DeviceContext=0; // el contexto nos va a servir para usar objetos de DirectX
	m_SwapChain=0; // la cadena de swap
	m_RenderTargetView=0;
}

CContextManager::~CContextManager(void)
{
	m_D3DDevice->Release();
	m_DeviceContext->Release();
	m_SwapChain->Release();
	m_RenderTargetView->Release();
}

HRESULT CContextManager::CreateRenderTarget(){
	ID3D11Texture2D *pBackBuffer;
	if (FAILED(m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer)))
		return FALSE;
	HRESULT hr = m_D3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_RenderTargetView);
	pBackBuffer->Release();
	return hr;
}

void CContextManager::Draw(int WIDTH_APPLICATION, int HEIGHT_APPLICATION){		
	// Limpiar el framebuffer:
	// ID3D11DeviceContext::ClearRenderTargetView
	// ID3D11DeviceContext::ClearDepthStencilView

	// definir a que target vamos a pintar:
	// ID3D11DeviceContext::OMSetRenderTargets

	// definir el viewport:
	// ID3D11DeviceContext::RSSetViewports

	// TODO renderizar aqui

	// presentar lo pintado:
	// IDXGISwapChain::Present
	float color[4] = {0, 1, 1, 1};




	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, color);
	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);

	D3D11_VIEWPORT viewport = {0, 0, WIDTH_APPLICATION, HEIGHT_APPLICATION, 0, 1};

	m_DeviceContext->RSSetViewports(1, &viewport);

	m_SwapChain->Present(0, 0);
}

HRESULT CContextManager::CrearContexto(HWND hWnd, int WIDTH_APPLICATION, int HEIGHT_APPLICATION){
	

	// Tendremos que crear y rellenar una estructura de este tipo
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	// o
	//DXGI_SWAP_CHAIN_DESC desc = {};
	desc.BufferCount = 1;
	desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.Windowed = TRUE;
	// TODO:
	desc.BufferDesc.Width = WIDTH_APPLICATION;
	desc.BufferDesc.Height = HEIGHT_APPLICATION;
	desc.BufferDesc.RefreshRate.Numerator = 1;
	desc.BufferDesc.RefreshRate.Denominator = 60;
	desc.OutputWindow = hWnd;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	//desc. ????

	// Que DirectX queremos
	D3D_FEATURE_LEVEL featureLevels[] =
	{
		
		D3D_FEATURE_LEVEL_11_0,
		//D3D_FEATURE_LEVEL_10_1,
		//D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = ARRAYSIZE(featureLevels);


	

	if (FAILED(D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, &desc, &m_SwapChain, &m_D3DDevice, NULL, &m_DeviceContext)))
	{
		return S_FALSE;
	}
	return S_OK;
}