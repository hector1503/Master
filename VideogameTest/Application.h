#pragma once

#include "SphericalCameraController.h"
#include "FPSCameraController.h"
#include "HelperTypes.h"
#include "RenderManager.h"
#include "MaterialManager.h"

class CDebugRender;
class CContextManager;

class CApplication
{
public:
	CApplication(CDebugRender *_DebugRender, CContextManager *_ContextManager);
	~CApplication();

	void SwitchCamera();

	void Init();
	void Update(float _ElapsedTime);
	void Render();
private:

	CSphericalCameraController m_SphericalCamera;
	CFPSCameraController m_FPSCamera;

	int m_CurrentCamera;

	CDebugRender *m_DebugRender;
	CContextManager *m_ContextManager;

	CColor m_BackgroundColor;
	CRenderableObject m_Cube;

	CRenderManager m_RenderManager;
	CMaterialManager m_MaterialManager;
};

