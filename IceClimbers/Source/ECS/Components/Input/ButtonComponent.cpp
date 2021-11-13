#include "pch.h"
#include "ButtonComponent.h"

#include "ECS/AGameObject.h"

ButtonComponent::ButtonComponent(AGameObject& owner,
								 const sf::Vector2f& boundSize,
								 std::function<void(AGameObject&)> onIdle,
								 std::function<void(AGameObject&)> onHover,
								 std::function<void(AGameObject&)> onPress,
								 std::function<void(AGameObject&)> onExecute) :
	AInputComponent{owner},
	m_TransformComponent{GetOwner().GetComponent<TransformComponent>()},
	m_BoundingBoxSize{boundSize},
	m_OnIdle{onIdle},
	m_OnHover{onHover},
	m_OnPress{onPress},
	m_OnExecute{onExecute},
	m_CurrentState{ButtonState::Idle}
{
	UpdateBoundingBox();
	SwitchState(ButtonState::Idle);
}

ButtonComponent::~ButtonComponent()
{
}

void ButtonComponent::ProcessInput(const sf::Event& event)
{
	switch (event.type)
	{
		case sf::Event::MouseButtonPressed:
			OnMousePressed(event.mouseButton);
			break;
		case sf::Event::MouseButtonReleased:
			OnMouseReleased(event.mouseButton); 
			break;
		case sf::Event::MouseMoved:
			OnMouseMoved(event.mouseMove);
			break;
		default:
			break;
	}
}

void ButtonComponent::SwitchState(const ButtonState state)
{
	m_CurrentState = state;
	switch (m_CurrentState)
	{
		case ButtonState::Idle:
			m_OnIdle(GetOwner());
			break;
		case ButtonState::Hover:
			m_OnHover(GetOwner());
			break;
		case ButtonState::Press:
			m_OnPress(GetOwner());
			break;
		default:
			break;
	}
}

void ButtonComponent::OnMouseMoved(const sf::Event::MouseMoveEvent& mouseMoveEvent)
{
	UpdateBoundingBox();
	const sf::Vector2f mousePosition = {static_cast<float>(mouseMoveEvent.x),
                                        static_cast<float>(mouseMoveEvent.y)};
	const bool isMouseWithinBounds = m_BoundingBox.contains(mousePosition);
	
	if (m_CurrentState != ButtonState::Press &&
		isMouseWithinBounds)
	{
		SwitchState(ButtonState::Hover);
	}
	else if (m_CurrentState == ButtonState::Hover &&
			!isMouseWithinBounds)
	{
		SwitchState(ButtonState::Idle);
	}
}

void ButtonComponent::OnMousePressed(const sf::Event::MouseButtonEvent& mouseButtonEvent)
{
	UpdateBoundingBox();
	const sf::Vector2f mousePosition = {static_cast<float>(mouseButtonEvent.x),
                                        static_cast<float>(mouseButtonEvent.y)};
	if (m_CurrentState != ButtonState::Press &&
        m_BoundingBox.contains(mousePosition))
	{
		SwitchState(ButtonState::Press);
	}
}

void ButtonComponent::OnMouseReleased(const sf::Event::MouseButtonEvent& mouseButtonEvent)
{
	UpdateBoundingBox();
	const sf::Vector2f mousePosition = {static_cast<float>(mouseButtonEvent.x),
                                        static_cast<float>(mouseButtonEvent.y)};
	if (m_CurrentState == ButtonState::Press &&
		m_BoundingBox.contains(mousePosition))
	{
		m_OnExecute(GetOwner());
	}
	SwitchState(ButtonState::Idle);
}

void ButtonComponent::UpdateBoundingBox()
{
	m_BoundingBox = {m_TransformComponent.GetPosition().x - m_BoundingBoxSize.x / 2.0f,
                     m_TransformComponent.GetPosition().y - m_BoundingBoxSize.y / 2.0f,
                     m_BoundingBoxSize.x,
                     m_BoundingBoxSize.y};
}
