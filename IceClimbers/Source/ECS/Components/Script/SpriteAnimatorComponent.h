#pragma once
#include <SFML/System/Vector2.hpp>

#include "AScriptComponent.h"

#include "ECS/Components/Render/SpriteRendererComponent.h"

class SpriteAnimatorComponent final : public AScriptComponent
{
public:
	explicit SpriteAnimatorComponent(AGameObject& owner,
	                                 const sf::Vector2i& startFramePosition,
	                                 const sf::Vector2i& endFramePosition,
	                                 const sf::Vector2i& frameSize,
	                                 float timePerFrame,
	                                 float initialDelay = 0.0f,
	                                 bool enableLooping = true);
	
	MAKE_COMPONENT(SCRIPT, SpriteAnimatorComponent)

	void Update(float deltaTime) override;
	
	void UpdateStartAndEndFrame(const sf::Vector2i& startFramePosition,
								const sf::Vector2i& endFramePosition,
								bool enableLooping);

	void RestartAnimation();

private:
	SpriteRendererComponent& m_SpriteRendererComponent;
	sf::Vector2i m_CurrentFrame;
	sf::Vector2i m_StartFrame;
	sf::Vector2i m_EndFrame;
	sf::Vector2i m_FrameSize;

	float m_TimePerFrame;
	float m_ElapsedTime;
	float m_InitialDelay;

	bool m_IsLooping;
	bool m_IsAtEndFrame;

	void UpdateTextureRect() const;
	void NextFrame();
	bool CheckIfEndOfFrame() const;
};


