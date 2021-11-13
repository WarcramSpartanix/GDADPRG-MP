#include "pch.h"
#include "ViewManager.h"
#include "ECS/GameObjects/FloorObject.h"
#include "Game.h"
#include "EventSystem/EventBroadcaster.h"
#include "EventSystem/EventNames.h"

ViewManager& ViewManager::GetInstance()
{
    static ViewManager instance;
    return instance;
}

void ViewManager::SetWindow(sf::RenderWindow* targetWindow)
{
    m_Window = targetWindow;
}

void ViewManager::MoveCamera(const String& viewName, float x, float y)
{
    GetView(viewName)->move(x, y);
}

void ViewManager::SetCameraPosition(const String& viewName,
                                    float x,
                                    float y)
{
    GetView(viewName)->reset(sf::FloatRect(x, y,
                                                  Game::SCREEN_WIDTH, Game::SCREEN_HEIGHT));
}

void ViewManager::SetWindowToView(const String& viewName)
{
    if (m_ViewMap.find(viewName) != m_ViewMap.end())
    {
        m_Window->setView(*m_ViewMap[viewName]);
    }
}

void ViewManager::AddView(const String& viewName, sf::View* view)
{
    m_ViewMap[viewName] = view;
}

void ViewManager::MoveCameraToNextFloor()
{
    m_HeightLevel++;
    Debug::Log("Height Level at {0}", m_HeightLevel);
    
    if (m_HeightLevel != 9)
    {
        MoveCamera(ViewNames::GAME_VIEW, 0.0f, -FloorObject::HEIGHT_PER_LEVEL);
    }
    else if (m_HeightLevel == 9)
    {
        EventBroadcaster::GetInstance().BroadcastEvent("BonusStart");
        MoveCamera(ViewNames::GAME_VIEW, 0.0f, -FloorObject::HEIGHT_PER_LEVEL);
        MoveCamera(ViewNames::GAME_VIEW, 0.0f, -FloorObject::HEIGHT_PER_LEVEL);
    }
}

int ViewManager::GetCameraFloorIndex()
{
    return m_HeightLevel;
}

void ViewManager::ResetCameraFloorIndex()
{
    m_HeightLevel = 4;
}

void ViewManager::ReceiveEvent(String eventName)
{
    if (eventName == EventNames::MOVE_NEXT_FLOOR)
    {
        MoveCameraToNextFloor();
    }
}

sf::FloatRect ViewManager::GetViewBounds(const String& viewName)
{
    sf::View* view = GetView(viewName);
    if (view != nullptr)
    {
        sf::FloatRect rt;
        rt.left = view->getCenter().x - view->getSize().x / 2.f;
        rt.top = view->getCenter().y - view->getSize().y / 2.f;
        rt.width = view->getSize().x;
        rt.height = view->getSize().y;
        return rt;
    }
     
    Debug::Error("Could not Find view {0} and failed to retrieve Bounds", viewName);

    return sf::FloatRect();
}


ViewManager::ViewManager()
{
    EventBroadcaster::GetInstance().AddEventListener(EventNames::MOVE_NEXT_FLOOR, this);
}

ViewManager::~ViewManager()
{
    EventBroadcaster::GetInstance().RemoveEventListener(EventNames::MOVE_NEXT_FLOOR, this);
}

sf::View* ViewManager::GetView(const String& viewName)
{
    if (m_ViewMap.find(viewName) != m_ViewMap.end())
    {
        return m_ViewMap[viewName];
    }
    return nullptr;
}
