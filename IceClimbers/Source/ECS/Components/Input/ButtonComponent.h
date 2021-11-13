#pragma once
#include <functional>
#include "AInputComponent.h"

#include "ECS/Components/Data/TransformComponent.h"

enum class ButtonState
{
	Idle,
	Hover,
	Press
};

class ButtonComponent final : public AInputComponent
{
public:
	ButtonComponent(AGameObject& owner,
					const sf::Vector2f& boundSize,
					std::function<void(AGameObject&)> onIdle = [](AGameObject&)->void {},
					std::function<void(AGameObject&)> onHover = [](AGameObject&)->void {},
					std::function<void(AGameObject&)> onPress = [](AGameObject&)->void {},
					std::function<void(AGameObject&)> onExecute = [](AGameObject&)->void {});
	~ButtonComponent() override;

	MAKE_COMPONENT(INPUT, ButtonComponent)

	void ProcessInput(const sf::Event& event) override;

private:
	TransformComponent& m_TransformComponent;
	sf::Vector2f m_BoundingBoxSize;
	sf::FloatRect m_BoundingBox;
	std::function<void(AGameObject&)> m_OnIdle;
	std::function<void(AGameObject&)> m_OnHover;
	std::function<void(AGameObject&)> m_OnPress;
	std::function<void(AGameObject&)> m_OnExecute;

	ButtonState m_CurrentState;

	void SwitchState(ButtonState state);
	void OnMouseMoved(const sf::Event::MouseMoveEvent& mouseMoveEvent);
	void OnMousePressed(const sf::Event::MouseButtonEvent& mouseButtonEvent);
	void OnMouseReleased(const sf::Event::MouseButtonEvent& mouseButtonEvent);
	void UpdateBoundingBox();
};
