#include <string>
#include <map>

template<class T>
class CTemplatedMapManager
{
protected:
	typedef std::map<std::string, T*> TMapResource;
	TMapResource m_Resources;

public:
	virtual T * GetResource(const std::string &Name)
	{
		std::map<std::string, T*>::iterator it = m_Resources.find(Name);

		if (it != m_Resources.end())
		{
			return it->second;
		}
		else
		{
			return NULL;
		}
	}

	virtual bool AddResource(const std::string &Name, T *Resource)
	{
		std::map<std::string, T*>::iterator it = m_Resources.find(Name);

		if (it == m_Resources.end())
		{
			m_Resources[Name] = Resource;
			return true;
		}
		else
		{
			return false;
		}
	}
	virtual void Destroy()
	{
		for (std::map<std::string, T*>::iterator it = m_Resources.begin(); it != m_Resources.end(); it++)
		{
			delete it->second;
		}

		m_Resources.clear();
	}
};
