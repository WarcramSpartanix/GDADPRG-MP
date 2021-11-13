#include "pch.h"
#include "Asset.h"

Asset::Asset(const String& name,
             const String& filepath) :
	m_Name(name),
	m_Filepath(filepath)
{
}

Asset::~Asset()
{
}