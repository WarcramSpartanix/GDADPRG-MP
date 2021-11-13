#pragma once

#include <SFML/Graphics.hpp>
#include "Core/TypeAlias.h"

#include "SceneSystem/AScene.h"

class Game final
{
public:
	static Uint SCREEN_WIDTH;
	static Uint SCREEN_HEIGHT;
	
    Game(const Game& other) = delete;
    Game(Game&& other) noexcept = delete;
    Game& operator=(const Game& other) = delete;
    Game& operator=(Game&& other) noexcept = delete;
    
    explicit Game(Uint width,
                  Uint height,
                  const String& title,
                  List<AScene*> sceneList,
                  const String& defaultSceneName);
    ~Game();

    void Run();

private:
    String m_Title;
    bool m_IsPlaying;
	bool m_IsRunning;
	String m_DefaultSceneName;
    sf::RenderWindow m_Window;

    void Initialize();
    void ProcessEvents();
    void Update(float deltaTime);
    void Render();
    void Deinitialize();
};
