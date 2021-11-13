#include "pch.h"
#include "TimerBehaviorComponent.h"

#include "ECS/AGameObject.h"

TimerBehaviorComponent::TimerBehaviorComponent(AGameObject& owner,
                                               float duration,
                                               std::function<void()> onElapsedTime) :
	AScriptComponent{owner},
	m_Duration{duration},
	m_OnExecute{onElapsedTime},
	m_TextRendererComponent{GetOwner().GetComponent<TextComponent>()}
{
}

TimerBehaviorComponent::~TimerBehaviorComponent()
{
}

void TimerBehaviorComponent::Start()
{
	m_IsTimerStarted = true;
}

void TimerBehaviorComponent::Reset()
{
	m_ElapsedTime = 0.0f;
	m_IsTimerEnd = false;
}

void TimerBehaviorComponent::Update(float deltaTime)
{
	if (m_IsTimerStarted && !m_IsTimerEnd)
	{
		m_ElapsedTime += deltaTime;

		m_TextRendererComponent.SetString("Timer: " + std::to_string(m_Duration - m_ElapsedTime));
		
		if (m_ElapsedTime > m_Duration)
		{
			m_OnExecute();
			m_IsTimerEnd = true;
		}
	}
}
