#include <Windows.h>

#include <d3d11.h>
#include "ContextManager.h"
//#include <d3dx11.h>

#ifdef NDEBUG
#pragma comment(lib,"d3dx11.lib")
#else
//#pragma comment(lib,"d3dx11d.lib")
#endif

#pragma comment(lib,"d3d11.lib")
//#pragma comment(lib,"dxerr.lib")
//#pragma comment(lib,"dxguid.lib")

#define APPLICATION_NAME	"VIDEOGAME TEST"

const int WIDTH_APPLICATION = 800;
const int HEIGHT_APPLICATION = 600;



//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{

  switch( msg )
  {
  case WM_DESTROY:
    {
      PostQuitMessage( 0 );
      return 0;
    }
    break;
  case WM_KEYDOWN:
    {
      switch( wParam )
      {
      case VK_ESCAPE:
        //Cleanup();
        PostQuitMessage( 0 ); //Mensaje de cerrar para poder salir del bucle.
        return 0;
        break;
      }
    }
    break;
  }//end switch( msg )

  return DefWindowProc( hWnd, msg, wParam, lParam );
}

//-----------------------------------------------------------------------
// WinMain
//-----------------------------------------------------------------------
int APIENTRY WinMain(HINSTANCE _hInstance, HINSTANCE _hPrevInstance, LPSTR _lpCmdLine, int _nCmdShow)
{
	CContextManager *l_ContextManager = new CContextManager;
	
  // Register the window class
  WNDCLASSEX wc = {	sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, APPLICATION_NAME, NULL };

  RegisterClassEx( &wc );

  // Calcular el tamano de nuestra ventana
	RECT rc = {0, 0, WIDTH_APPLICATION, HEIGHT_APPLICATION};
	AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE);

  // Create the application's window
  HWND hWnd = CreateWindow(	APPLICATION_NAME, APPLICATION_NAME, WS_OVERLAPPEDWINDOW, 100, 100, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, wc.hInstance, NULL );

  HRESULT Contexto = l_ContextManager->CrearContexto(hWnd, WIDTH_APPLICATION, HEIGHT_APPLICATION);//AQUI
  // Añadir aquí el Init de la applicacioón

  ShowWindow( hWnd, SW_SHOWDEFAULT );
  l_ContextManager->CreateRenderTarget();
  UpdateWindow( hWnd );
  MSG msg;
  ZeroMemory( &msg, sizeof(msg) );

  // Añadir en el while la condición de salida del programa de la aplicación

  while( msg.message != WM_QUIT )
  {
	//Mira en la cola de mensajes si hay uno para ti. Si hay realiza la accion de 1 mensaje cada vez. Si no hay ejecuta el juego.
    if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) ) 
    {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }
    else
    {
       // Main loop: Añadir aquí el Update y Render de la aplicación principal
		l_ContextManager->Draw(WIDTH_APPLICATION, HEIGHT_APPLICATION);
    }
  }
  UnregisterClass( APPLICATION_NAME, wc.hInstance );

  // Añadir una llamada a la alicación para finalizar/liberar memoria de todos sus datos

  return 0;
}