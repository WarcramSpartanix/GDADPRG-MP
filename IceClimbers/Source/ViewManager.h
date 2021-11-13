#pragma once
#include "SFML/Graphics.hpp"
#include "EventSystem/IEventListener.h"

class ViewManager : IEventListener
{

public:
	static ViewManager& GetInstance();

	void SetWindow(sf::RenderWindow* targetWindow);

	void MoveCamera(const String&, float x, float y);
	void SetCameraPosition(const String&, float x, float y);
	void SetWindowToView(const String&);
	void AddView(const String&, sf::View*);

	void MoveCameraToNextFloor();
	int GetCameraFloorIndex();
	void ResetCameraFloorIndex();
	void ReceiveEvent(String) override;
	sf::FloatRect GetViewBounds(const String&);
private:
	ViewManager();
	~ViewManager();
	
	sf::RenderWindow* m_Window;
	HashTable<String, sf::View*> m_ViewMap;

	sf::View* GetView(const String&);

	int m_HeightLevel = 4;	// IMPORTANT: reset this every level

};


namespace ViewNames
{
	const String GAME_VIEW = "Game";
	const String UI_VIEW = "UI";
}
