#include <map>
#include <string>
#include <vector>
#include <assert.h>

//template<class T>
typedef int T;
class CTemplatedVectorMapManager
{
public:
	class CMapResourceValue
	{
	public:
		T *m_Value;
		size_t m_Id;

		CMapResourceValue()
		{
			assert(false);
		}
		CMapResourceValue(T *Value, size_t Id)
			: m_Value(Value)
			, m_Id(Id)
		{
		}
	};
	typedef std::vector<T *> TVectorResources;
	typedef std::map<std::string, CMapResourceValue> TMapResources;

protected:
	TVectorResources m_ResourcesVector;
	TMapResources m_ResourcesMap;

public:
	CTemplatedVectorMapManager()
	{
		//
	}
	virtual ~CTemplatedVectorMapManager()
	{
		//
	}
	void RemoveResource(const std::string &Name)
	{

	}
	virtual T * GetResourceById(size_t Id)
	{
		if (m_ResourcesVector.size() > Id)
		{
			return m_ResourcesVector[Id];
		}
		else
		{
			return NULL;
		}
	}
	virtual T * GetResourceByName(const std::string &Name)
	{
		TMapResources::iterator it;
		it = m_ResourcesMap.find(Name);

		if (it != m_ResourcesMap.end())
		{
			return it->second.m_Value;
		}
		else
		{
			return NULL;
		}
	}
	virtual bool AddResource(const std::string &Name, T *Resource)
	{
		TMapResources::iterator it;
		it = m_ResourcesMap.find(Name);

		if (it == m_ResourcesMap.end())
		{
			CMapResourceValue Obj(Resource, m_ResourcesVector.size());
			m_ResourcesMap[Name] = Obj;
			m_ResourcesVector.push_back(Resource);
			return 1;
		}
		else
		{
			return NULL;
		}
	}
	virtual void Destroy()
	{
		for (int i = 0; i < m_ResourcesVector.size(); i++)
		{
			delete m_ResourcesVector[i];
		}

		m_ResourcesVector.clear();
		m_ResourcesMap.clear();
	}
	TMapResources & GetResourcesMap()
	{
		return m_ResourcesMap;
	}
	TVectorResources & GetResourcesVector()
	{
		return m_ResourcesVector;
	}
};