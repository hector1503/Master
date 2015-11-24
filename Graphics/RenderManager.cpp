#include "RenderManager.h"

#include "ContextManager.h"
#include "MaterialManager.h"

void CRenderManager::SetCurrentCamera(const CCamera& _CurrentCamera)
{
	m_CurrentCamera = _CurrentCamera;
	Mat44f viewProj = m_CurrentCamera.GetView() * m_CurrentCamera.GetProjection();
	m_CullFrustum.Update(viewProj);
}

bool CRenderManager::AddRenderableObjectToRenderList(const CRenderableObject* _RenderableObject)
{
	// Alguien se atrebe a arreglar el frustum?

	//if (m_CullFrustum.SphereVisible(_RenderableObject->GetTransform().Position, _RenderableObject->GetBoundingRadius()))
	{
		if (m_CurrentRenderlistLength == m_RenderableObjects.size())
		{
			m_RenderableObjects.push_back(_RenderableObject);
		}
		else
		{
			m_RenderableObjects[m_CurrentRenderlistLength];
		}
		++m_CurrentRenderlistLength;
		return true;
	}
	//else
	//{
	//	return false;
	//}
}


	struct BlendedSubmesh
	{
	    const CRenderableVertexs* vertices;
	    Mat44f world;
	    const CMaterial* material;
	    Vect3f position;
	};

void CRenderManager::Render(CContextManager* _Context, CMaterialManager* _MaterialManager)
{
	if (m_UseDebugCamera)
	{
		_Context->SetCamera(m_DebugCamera);
	}
	else
	{
		_Context->SetCamera(m_CurrentCamera);
	}
	std::vector<BlendedSubmesh> l_SubmeshesWithBlend;


	for (unsigned int i = 0; i < m_CurrentRenderlistLength; ++i)
	{
		const CRenderableObject* l_RenderableObject = m_RenderableObjects[i];
		const SPositionOrientation& l_Transform = l_RenderableObject->GetTransform();

		Mat44f world;
		world.SetFromPosAndAnglesYXZ(l_Transform.Position, l_Transform.Yaw, l_Transform.Pitch, l_Transform.Roll);
		_Context->SetWorldMatrix(world);

		for (unsigned int j = 0; j < l_RenderableObject->GetNumSubmeshes(); ++j)
		{
			const CRenderableObject::SSubmesh& l_Submesh = l_RenderableObject->GetSubmesh(j);
			const CMaterial* l_Material = _MaterialManager->GetMaterial(l_Submesh.material);
			if (!l_Material->HasBlending())
			{
				l_Material->SetShaderParameters(_Context);
				_Context->Draw(l_Submesh.vertices, l_Material->GetRasterizerState(), l_Material->GetDepthStencilState(), l_Material->GetBlendState());
			} 
			else
			{
				BlendedSubmesh object = { l_Submesh.vertices, world, l_Material, world.GetPos() };
				l_SubmeshesWithBlend.push_back(object);
				int a=0;
			}
		}
	}

	const Vect3f& l_CameraPosition = m_CurrentCamera.GetPosition();
	int swap = 0;
	do {
		swap = 0;

		for (unsigned int j = 0; j < l_SubmeshesWithBlend.size(); ++j)
		{
			float l_DistanceSQ = l_SubmeshesWithBlend[j].position.SquaredLength();
			float distance = l_CameraPosition.SquaredLength() - l_DistanceSQ;
			
			float l_DistanceSQ_2 = l_SubmeshesWithBlend[j+1].position.SquaredLength();
			float distance_2 = l_CameraPosition.SquaredLength() - l_DistanceSQ_2;

			if (distance_2 < distance)
			{
				BlendedSubmesh temp = { l_SubmeshesWithBlend[j].vertices, l_SubmeshesWithBlend[j].world, l_SubmeshesWithBlend[j].material, l_SubmeshesWithBlend[j].world.GetPos() };
				l_SubmeshesWithBlend[j] = l_SubmeshesWithBlend[j+1];
				l_SubmeshesWithBlend[j+1] = temp;
				swap = 1;
			}
		}
	} while(swap);

	// TODO: Pintar objetos translúcidos
	for (int i = 0; i < l_SubmeshesWithBlend.size(); ++i)
	{
		
	}

	m_CurrentRenderlistLength = 0;
}