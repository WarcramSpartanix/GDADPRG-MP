#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "WidgetStorage.h"
class AWidget;

class UIManager final
{
public:
	static UIManager& GetInstance();
	~UIManager();

	template <class T, typename ...Args>
	T& CreateWidget(Args&& ...args);

	void DestroyWidget(AWidget& widget);
	void DestroyWidgetByName(const String& widgetName);
	void DestroyAllWidgets();

	AWidget& FindWidgetByName(const String& name);
    
	void InitializeWidgets();
	void ProcessWidgetsInput(const sf::Event& event) const;
	void UpdateWidgets(float deltaTime) const;
	void DrawWidgets(sf::RenderWindow& window) const;
	void DestroyWidgets();

private:
	UIManager();
	Queue<AWidget*> m_InitializationQueue;
	Queue<AWidget*> m_DestroyQueue;
	WidgetStorage m_WidgetStorage;
};

template <class T, typename ... Args>
T& UIManager::CreateWidget(Args&&... args)
{
	T* object = new T(std::forward<Args>(args) ...);
	m_WidgetStorage.Add(object);
	m_InitializationQueue.push(object);
	return *object;
}
