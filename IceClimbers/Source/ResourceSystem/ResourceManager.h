#pragma once
#include "Asset.h"
using AssetTable = HashTable<String, Asset*>;

class ResourceManager final
{
public:
	ResourceManager(const ResourceManager& other)                = delete;
	ResourceManager(ResourceManager&& other) noexcept            = delete;
	ResourceManager& operator=(const ResourceManager& other)     = delete;
	ResourceManager& operator=(ResourceManager&& other) noexcept = delete;
	
	static ResourceManager& GetInstance();
	~ResourceManager();
	
	template <class Resource>
	void Load(const String& name,
	          const String& filepath);
	
	template <class Resource>
	void Unload(const String& name);
	
	template <class Resource>
	Resource& Acquire(const String& name);

private:
	ResourceManager();
	HashTable<String, AssetTable> m_AssetStorage;
};

template <class Resource>
void ResourceManager::Load(const String& name,
                       const String& filepath)
{
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticType()];
	const auto found           = selectedAssetStorage.find(name);
	
	if (found == selectedAssetStorage.end())
		selectedAssetStorage[name] = new Resource(name, filepath);
	
	ASSERT(found == selectedAssetStorage.end(),
	       "[ResourceManager] {0}({1}) has already been loaded or cannot be found!",
	       Resource::GetStaticType(), name)
}

template <class Resource>
void ResourceManager::Unload(const String& name)
{
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticType()];
	const auto found           = selectedAssetStorage.find(name);
	
	ASSERT(found != selectedAssetStorage.end(),
	       "[ResourceManager] Attempting to delete a non-existing {0}({1})",
	       Resource::GetStaticType(), name)
	
	auto* deletedAsset = selectedAssetStorage[name];
	selectedAssetStorage.erase(name);
	delete deletedAsset;
}

template <class Resource>
Resource& ResourceManager::Acquire(const String& name)
{
	auto& selectedAssetStorage = m_AssetStorage[Resource::GetStaticType()];
	auto* found                = selectedAssetStorage[name];
	
	ASSERT(found != nullptr,
	       "[ResourceManager] {0}({1}) does not exist!",
	       Resource::GetStaticType(), name)
	
	return *static_cast<Resource*>(found);
}