#include "pch.h"
#include "WidgetStorage.h"
#include "AWidget.h"

WidgetStorage::WidgetStorage()
{
}

WidgetStorage::~WidgetStorage()
{
	Clear();
}

void WidgetStorage::Add(AWidget* widget)
{
	ASSERT(widget != nullptr,
            "Cannot add a null Widget in storage!")
	
	const bool isWidgetInStorage = IsInStorage(widget);
	
	ASSERT(!isWidgetInStorage,
		"{0} has already been added!",
			 	widget->GetName())
	
	m_WidgetList.emplace_back(widget);
	m_WidgetTable[widget->GetName()] = widget;
}

void WidgetStorage::Remove(AWidget* widget)
{
	ASSERT(widget != nullptr,
            "Cannot remove a null Widget in storage!")

	const bool isWidgetInStorage = IsInStorage(widget);
	
	ASSERT(!isWidgetInStorage,
        "{0} has already been added!",
                 widget->GetName())
	
	auto findWidgetFunction =
		[widget](AWidget* other) -> bool
		{
			return widget->GetName() == other->GetName();
		};
	
	const auto foundWidget =
		std::remove_if(m_WidgetList.begin(),
					   m_WidgetList.end(),
					       findWidgetFunction);
	
	m_WidgetList.erase(foundWidget);
	m_WidgetList.shrink_to_fit();
	m_WidgetTable.erase((*foundWidget)->GetName());
}

AWidget* WidgetStorage::Get(const String& name)
{
	auto* foundObject = m_WidgetTable[name];
	Debug::Warn("Attempting to retrieve a widget {0} that doesn't exist in storage.", name);
	return foundObject;
}

bool WidgetStorage::IsInStorage(AWidget* widget)
{
	ASSERT(widget != nullptr,
			"Cannot find a null Widget in storage!")
	
	const auto foundObjectInTable = m_WidgetTable.find(widget->GetName());
	
	return foundObjectInTable != m_WidgetTable.end();
}

bool WidgetStorage::IsInStorageByName(const String& name)
{
    AGameObject* foundWidget = Get(name);
	return foundWidget != nullptr;
}

void WidgetStorage::Clear()
{
	m_WidgetList.clear();
	m_WidgetList.shrink_to_fit();
	m_WidgetTable.clear();
}

const List<AWidget*>& WidgetStorage::GetAll() const
{
	return m_WidgetList;
}
