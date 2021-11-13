#pragma once
#include "ECS/Components/Data/TextComponent.h"
#include "ECS/Components/Script/AScriptComponent.h"

class TimerBehaviorComponent final : public AScriptComponent
{
public:
	TimerBehaviorComponent(AGameObject& owner,
						   float duration,
						   std::function<void()> onElapsedTime);
	~TimerBehaviorComponent() override;

	void Start();
	void Reset();
	void Update(float deltaTime) override;
	
	MAKE_COMPONENT(SCRIPT, TimerBehaviorComponent)

private:
	float m_ElapsedTime = 0.0f;
	float m_Duration = 0.0f;
	bool m_IsTimerStarted = false;
	bool m_IsTimerEnd = false;
	std::function<void()> m_OnExecute;
	TextComponent& m_TextRendererComponent;
};
