#pragma once
#include <string>
#include "Texture.h"
#include "TemplatedMapManager.h"
class CTextureManager : public CTemplatedMapManager<CTexture>
{
public:
	CTextureManager();
	virtual ~CTextureManager();
	CTexture * GetTexture(const std::string &Filename);
	void Reload();
};
