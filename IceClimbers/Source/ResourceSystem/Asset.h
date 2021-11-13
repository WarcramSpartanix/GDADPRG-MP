#pragma once
#include "Core/TypeAlias.h"

#define MAKE_ASSET(assetType) static String GetStaticType() { return #assetType; }	\
							  virtual String GetType() const override { return #assetType; }

class Asset
{
public:
	Asset(const Asset& other)                = delete;
	Asset(Asset&& other) noexcept            = delete;
	Asset& operator=(const Asset& other)     = delete;
	Asset& operator=(Asset&& other) noexcept = delete;
	
	Asset(const String& name,
	      const String& filepath);
	virtual ~Asset();

	virtual String GetType() const = 0;

protected:
	String m_Name;
	String m_Filepath;
};
