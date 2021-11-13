#include "pch.h"
#include "UIManager.h"
#include "AWidget.h"

UIManager& UIManager::GetInstance()
{
	static UIManager instance;
	return instance;
}

UIManager::~UIManager()
{
}

void UIManager::DestroyWidget(AWidget& widget)
{
	AWidget* toDestroy = m_WidgetStorage.Get(widget.GetName());
	if (toDestroy == nullptr)
	{
		return;
	}
	m_DestroyQueue.push(toDestroy);
	m_WidgetStorage.Remove(toDestroy);
}

void UIManager::DestroyWidgetByName(const String& widgetName)
{
	AWidget* toDestroy = m_WidgetStorage.Get(widgetName);
	if (toDestroy == nullptr)
	{
		return;
	}
	m_DestroyQueue.push(toDestroy);
	m_WidgetStorage.Remove(toDestroy);
}

void UIManager::DestroyAllWidgets()
{
	auto& widgetStorage = m_WidgetStorage.GetAll();
	for (auto* widget : widgetStorage)
	{
		m_DestroyQueue.push(widget);
	}
	m_WidgetStorage.Clear();
}

AWidget& UIManager::FindWidgetByName(const String& name)
{
	AWidget* widget = m_WidgetStorage.Get(name);

	ASSERT(widget != nullptr,
            "Cannot find Widget {0}!", name);
    
	return *widget;
}

void UIManager::InitializeWidgets()
{
	while (!m_InitializationQueue.empty())
	{
		m_InitializationQueue.front()->OnInitialize();
		m_InitializationQueue.pop();
	}
}

void UIManager::ProcessWidgetsInput(const sf::Event& event) const
{
	auto& widgetList = m_WidgetStorage.GetAll();
	for (auto* widget : widgetList)
	{
		widget->ProcessInput(event);
	}
}

void UIManager::UpdateWidgets(float deltaTime) const
{
	auto& widgetList = m_WidgetStorage.GetAll();
	for (auto* widget : widgetList)
	{
		widget->Update(deltaTime);
	}
}

void UIManager::DrawWidgets(sf::RenderWindow& window) const
{
	auto& widgetList = m_WidgetStorage.GetAll();
	for (auto* widget : widgetList)
	{
		widget->Draw(window, sf::RenderStates::Default);
	}
}

void UIManager::DestroyWidgets()
{
	while (!m_DestroyQueue.empty())
	{
		auto* widget = m_DestroyQueue.front();
		widget->OnDestroy();
		delete widget;
		m_DestroyQueue.pop();
	}
}

UIManager::UIManager()
{
}
