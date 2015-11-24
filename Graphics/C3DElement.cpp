#include "C3DElement.h"


C3DElement::C3DElement()
{
}

C3DElement::C3DElement(const Vect3f &Position)
{
	m_Position = (0.f,0.f,0.f);
	m_Yaw = 0.f;
	m_Pitch = 0.f;
	m_Roll = 0.f;
}

C3DElement::C3DElement(const Vect3f &Position, float Yaw, float Pitch, float Roll)
{
	m_Position = Position;
	m_Yaw = Yaw;
	m_Pitch = Pitch;
	m_Roll = Roll;
}

C3DElement::C3DElement(float Yaw, float Pitch, float Roll)
{
	m_Position = (0.f,0.f,0.f);
	m_Yaw = Yaw;
	m_Pitch = Pitch;
	m_Roll = Roll;
}

C3DElement::C3DElement(const CXMLTreeNode &XMLTreeNode)
{
		const char *l_Pos=XMLTreeNode.GetPszProperty("pos", "0.0 0.0 0.0");
		sscanf_s(l_Pos, "%f %f %f", m_Position[0], m_Position[1], m_Position[2]);
		m_Yaw=XMLTreeNode.GetFloatProperty("yaw", 0.0f);
		m_Pitch=XMLTreeNode.GetFloatProperty("pitch", 0.0f);
		m_Roll=XMLTreeNode.GetFloatProperty("roll", 0.0f);
}

void C3DElement::SetPosition(const Vect3f &Position)
{
	m_Position=Position;
}

inline const Vect3f & C3DElement::GetPosition() const
{
	return m_Position;
}
	
inline const Vect3f & C3DElement::GetPrevPosition() const
{
	return m_PrevPos;
}
	
float C3DElement::GetYaw() const
{
	return m_Yaw;
}
	
float C3DElement::GetPitch() const
{
	return m_Pitch;
}
	
float C3DElement::GetRoll() const
{
	return m_Roll;
}
	
void C3DElement::SetYaw(float Yaw)
{
	m_Yaw=Yaw;
}
	
void C3DElement::SetPitch(float Pitch)
{
	m_Pitch=Pitch;
}
	
void C3DElement::SetRoll(float Roll)
{
	m_Roll=Roll;
}
	
void C3DElement::SetYawPitchRoll(float Yaw, float Pitch, float Roll)
{
	m_Yaw=Yaw;
	m_Pitch=Pitch;
	m_Roll=Roll;
}
	
void C3DElement::SetScale(const Vect3f &Scale)
{
	m_Scale=Scale;
}
	
inline const Vect3f & C3DElement::GetScale() const
{
	return m_Scale;
}
	
//virtual void C3DElement::Render(CRenderManager *RenderManager);
	
const Mat44f & C3DElement::GetTransform()
{
	return m_TransformMatrix;
}