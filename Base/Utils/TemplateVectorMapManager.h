#include <map>
#include <string>
#include <vector>
#include <assert.h>

template<class T>
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
		Destroy();
	}
	void RemoveResource(const std::string &Name)
	{
		size_t l_Id = 0;
		TMapResources::iterator it = m_ResourcesMap.find(Name);

		if (it != m_ResourcesMap.end())
		{
			l_Id = m_ResourcesMap[Name].m_Id;
			m_ResourcesMap.erase(it);
			m_ResourcesVector.erase(m_ResourcesVector.begin() + l_Id);

			for(int i = l_Id; i < m_ResourcesVector.size(); i++)
			{
				T* l_Value = m_ResourcesVector[i];
				it = m_ResourcesMap.begin();
				while(it->second.m_Value != l_Value)
				{
					it++;
				}

				it->second.m_Id = i;
			}
		}
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
		TMapResources::iterator it = m_ResourcesMap.find(Name);

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
		TMapResources::iterator it = m_ResourcesMap.find(Name);

		if (it == m_ResourcesMap.end())
		{
			CMapResourceValue Obj(Resource, m_ResourcesVector.size());
			m_ResourcesMap[Name] = Obj;
			m_ResourcesVector.push_back(Resource);
			return true;
		}
		else
		{
			return false;
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