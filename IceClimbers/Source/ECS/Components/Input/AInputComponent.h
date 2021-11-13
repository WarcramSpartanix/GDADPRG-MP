#pragma once
#include <SFML/Window/Event.hpp>

#include "ECS/AComponent.h"

class AInputComponent : public AComponent
{
public:
	explicit AInputComponent(AGameObject& owner);
	virtual void ProcessInput(const sf::Event& event) = 0;
};
