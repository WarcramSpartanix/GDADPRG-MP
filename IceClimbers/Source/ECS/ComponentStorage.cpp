#include "pch.h"
#include "ComponentStorage.h"

void ComponentStorage::Add(AComponent* component)
{
	ASSERT(component != nullptr,
				  "Cannot add a null component in storage!")

	AComponent* foundComponent = Get(component->GetName()); 

	ASSERT(foundComponent == nullptr,
        "{0} has already been added in the storage!",
                component->GetName());
	
	m_ComponentTable[component->GetName()] = component;
	m_ComponentListTable[component->GetType()].emplace_back(component);
}

void ComponentStorage::Remove(const String& componentName)
{
	AComponent* foundComponent = Get(componentName);
	
	ASSERT(foundComponent != nullptr,
        "{0} does not exist in storage!",
                 componentName)

    auto findComponentFunction =
        [componentName](AComponent* other) -> bool
        {
        	return componentName == other->GetName();
        };
	
	const ComponentType componentType = foundComponent->GetType();
	
	const auto foundComponentInList =
        std::remove_if(m_ComponentListTable[componentType].begin(),
                       m_ComponentListTable[componentType].end(),
                           findComponentFunction);

	m_ComponentListTable[componentType].erase(foundComponentInList);
	m_ComponentListTable[componentType].shrink_to_fit();
	m_ComponentTable.erase(foundComponent->GetName());
}

AComponent* ComponentStorage::Get(const String& componentName)
{
	return m_ComponentTable[componentName];
}

List<AComponent*>& ComponentStorage::GetListOfType(const ComponentType componentType)
{
	return m_ComponentListTable[componentType];
}
