#include "pch.h"
#include "Game.h"

#include "ECS/GameObjectManager.h"
#include "SceneSystem/SceneManager.h"
#include "ViewManager.h"

#include "UISystem/UIManager.h"
Uint Game::SCREEN_WIDTH = 0;
Uint Game::SCREEN_HEIGHT = 0;

const sf::Time TIMESTEP = sf::seconds(1.0f / 200.0f);

Game::Game(const Uint width,
             const Uint height,
             const String& title,
             List<AScene*> sceneList,
             const String& defaultSceneName) :
    m_Title{title},
    m_IsPlaying{true},
    m_IsRunning{true},
    m_DefaultSceneName{defaultSceneName}
{
    Debug::Init();
    
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;

    m_Window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),
                    m_Title,
                    sf::Style::Close);
    m_Window.setFramerateLimit(60);

    SceneManager::GetInstance().RegisterScenes(sceneList);

    ViewManager::GetInstance().SetWindow(&m_Window);
    ViewManager::GetInstance().AddView(ViewNames::GAME_VIEW, new sf::View(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT)));
    ViewManager::GetInstance().AddView(ViewNames::UI_VIEW, new sf::View(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT)));
    
}

Game::~Game()
{
}

void Game::Run()
{
    auto clock = sf::Clock();
    auto timeSinceLastUpdate = sf::Time::Zero;

    SceneManager::GetInstance().LoadScene(m_DefaultSceneName);
    
    while (m_IsRunning)
    {
        Initialize();
        ProcessEvents();
        
        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate > TIMESTEP)
        {
            Update(TIMESTEP.asSeconds());
            timeSinceLastUpdate -= TIMESTEP;
        }
        
        Render();
        Deinitialize();
    }

    SceneManager::GetInstance().DeregisterAllScenes();
    m_Window.close();

    // TODO: Issue when the program exits
    // The destruction of all singleton managers are not-defined
    // The problem lies when a manager destroys a resource on destroy
    // i.e. SceneManager deregisters all scenes, but the destroyObjects
    // and unload resources are executed even if it is already called beforehand
    // or had not even loaded at all
    // Idea: Have a Service Locator for all singletons so that I only have one singleton
    // then call it to deinitialize at the end of the program
    // Or, Unload all resources on deinitialize where the destructor will not need
    // to do anything that has dependency
    // SceneManager's destruction can deregister all scenes on deinitialize
}

void Game::Initialize()
{
    SceneManager::GetInstance().InitializeScenes();
    GameObjectManager::GetInstance().InitializeGameObjects();
    // UIManager::GetInstance().InitializeWidgets();
}

void Game::ProcessEvents()
{
    // We'll need an event queue so that the top-most layer receives input first
    // so that it doesn't bleed through the next layer
    auto event = sf::Event();
    while (m_Window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                m_IsRunning = false;
                SceneManager::GetInstance().UnloadActiveScenes();
                break;
            case sf::Event::KeyPressed:
            case sf::Event::KeyReleased:
            case sf::Event::MouseWheelMoved:
            case sf::Event::MouseWheelScrolled:
            case sf::Event::MouseButtonPressed:
            case sf::Event::MouseButtonReleased:
            case sf::Event::MouseMoved:
            case sf::Event::MouseEntered:
            case sf::Event::MouseLeft:
            case sf::Event::JoystickButtonPressed:
            case sf::Event::JoystickButtonReleased:
            case sf::Event::JoystickMoved:
            case sf::Event::JoystickConnected:
            case sf::Event::JoystickDisconnected:
            case sf::Event::TouchBegan:
            case sf::Event::TouchMoved:
            case sf::Event::TouchEnded:
            case sf::Event::SensorChanged:
                UIManager::GetInstance().ProcessWidgetsInput(event);
                GameObjectManager::GetInstance().ProcessGameObjectsInput(event);
            default:
                break;
        }
    }

    // Get all events
    // Process the inputs in the UI Layer (GameObjects representing UI; important for popups)
    // if (event queue is not empty)
    //  Process the inputs in the Game Layer (GameObjects in the game)
}

void Game::Update(const float deltaTime)
{
    UIManager::GetInstance().UpdateWidgets(deltaTime);
    if (!m_IsPlaying)
    {
        return;
    }

    GameObjectManager::GetInstance().UpdateGameObjects(deltaTime);
}

void Game::Render()
{
    m_Window.clear();
    
    //Set window to sf::View (GameView) 
    ViewManager::GetInstance().SetWindowToView(ViewNames::GAME_VIEW);
    GameObjectManager::GetInstance().DrawGameObjects(m_Window);

    // Set window to sf::View (UIView) 
    ViewManager::GetInstance().SetWindowToView(ViewNames::UI_VIEW);
    UIManager::GetInstance().DrawWidgets(m_Window);
    
    m_Window.display();
}

void Game::Deinitialize()
{
    SceneManager::GetInstance().DeinitializeScenes();
    GameObjectManager::GetInstance().DestroyGameObjects();
    UIManager::GetInstance().DestroyWidgets();
}