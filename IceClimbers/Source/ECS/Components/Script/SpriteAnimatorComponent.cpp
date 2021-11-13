#include "pch.h"
#include "SpriteAnimatorComponent.h"

#include "ECS/AGameObject.h"



SpriteAnimatorComponent::SpriteAnimatorComponent(AGameObject& owner,
                                                 const sf::Vector2i& startFramePosition,
                                                 const sf::Vector2i& endFramePosition,
                                                 const sf::Vector2i& frameSize,
                                                 const float timePerFrame,
                                                 const float initialDelay,
                                                 const bool enableLooping) :
	AScriptComponent{owner},
	m_SpriteRendererComponent{GetOwner().GetComponent<SpriteRendererComponent>()},
	m_CurrentFrame{startFramePosition.x, startFramePosition.y},
	m_StartFrame{startFramePosition},
	m_EndFrame{endFramePosition},
	m_FrameSize{frameSize},
	m_TimePerFrame{timePerFrame},
	m_ElapsedTime{0.0f},
	m_InitialDelay{initialDelay},
	m_IsLooping{enableLooping},
	m_IsAtEndFrame{false}
{
	ASSERT(startFramePosition.x <= endFramePosition.x &&
              startFramePosition.y <= endFramePosition.y,
              "EndFramePosition is greater than StartFramePosition!")
	
	UpdateTextureRect();
}

void SpriteAnimatorComponent::UpdateTextureRect() const
{
	m_SpriteRendererComponent.SetTextureRect(m_CurrentFrame,
                                             m_FrameSize);
}

void SpriteAnimatorComponent::NextFrame()
{
	m_CurrentFrame.x++;
	if (m_CurrentFrame.x > m_EndFrame.x)
	{
		m_CurrentFrame.x = m_StartFrame.x;
		m_CurrentFrame.y++;
		
		if (m_CurrentFrame.y > m_EndFrame.y)
		{
			m_IsAtEndFrame = true;
			m_CurrentFrame = m_EndFrame;
		}
	}
}

bool SpriteAnimatorComponent::CheckIfEndOfFrame() const
{
	return m_CurrentFrame.x >= m_EndFrame.x &&
		   m_CurrentFrame.y >= m_EndFrame.y;
}

void SpriteAnimatorComponent::Update(const float deltaTime)
{
	if (!m_IsLooping && m_IsAtEndFrame)
	{
		return;
	}
	
	m_ElapsedTime += deltaTime;
	
	if (m_InitialDelay > m_ElapsedTime)
	{
		return;
	}
	
	if (m_TimePerFrame + m_InitialDelay < m_ElapsedTime)
	{
		NextFrame();

		if (m_IsLooping && m_IsAtEndFrame)
		{
			m_CurrentFrame = m_StartFrame;
			m_IsAtEndFrame = false;
		}
	
		UpdateTextureRect();
		
		m_ElapsedTime = m_InitialDelay;
	}

	
}

void SpriteAnimatorComponent::UpdateStartAndEndFrame(const sf::Vector2i& startFramePosition,
													 const sf::Vector2i& endFramePosition,
													 bool enableLooping = true)
{
	ASSERT(startFramePosition.x <= endFramePosition.x &&
              startFramePosition.y <= endFramePosition.y,
              "EndFramePosition is greater than StartFramePosition!")

	if (m_IsLooping != enableLooping)
	{
		m_IsLooping = enableLooping;
	}
	
	m_StartFrame = startFramePosition;
	m_EndFrame = endFramePosition;
	RestartAnimation();
}

void SpriteAnimatorComponent::RestartAnimation()
{
	m_CurrentFrame = m_StartFrame;
	m_IsAtEndFrame = false;
	m_ElapsedTime = 0.0f;
	UpdateTextureRect();
}

