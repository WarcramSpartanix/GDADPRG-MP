#pragma once

class AGameObject;
class GameObjectStorage final
{
public:
	GameObjectStorage();
	~GameObjectStorage();
	
	void Add(AGameObject* gameObject);
	void Remove(AGameObject* gameObject);
	AGameObject* Get(const String& name);
	bool IsInStorage(AGameObject* gameObject);
	bool IsInStorageByName(const String& name);
	void Clear();
	const List<AGameObject*>& GetAll() const;
	
private:
	List<AGameObject*> m_GameObjectList;
	HashTable<String, AGameObject*> m_GameObjectTable;
};


