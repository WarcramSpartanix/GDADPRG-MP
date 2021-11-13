#pragma once
#include "AComponent.h"

class ComponentStorage
{
public:
	void Add(AComponent* component);
	void Remove(const String& componentName);
	AComponent* Get(const String& componentName);

	List<AComponent*>& GetListOfType(ComponentType componentType);
	
private:
	HashTable<String, AComponent*> m_ComponentTable;
	HashTable<ComponentType, List<AComponent*>> m_ComponentListTable;
};