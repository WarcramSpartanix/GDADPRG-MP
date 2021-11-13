#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

#include "ECS/AComponent.h"

class ARenderComponent : public AComponent
{
public:
	explicit ARenderComponent(AGameObject& owner);
	virtual void Draw(sf::RenderWindow& window,
	                  sf::RenderStates renderStates) = 0;
};
