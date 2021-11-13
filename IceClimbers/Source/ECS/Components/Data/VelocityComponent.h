#pragma once
#include <SFML/System/Vector2.hpp>

#include "ECS/AComponent.h"

class VelocityComponent final: public AComponent
{
public:
	explicit VelocityComponent(AGameObject& owner,
							   const sf::Vector2f& initialVelocity = sf::Vector2f(0.0f, 0.0f));

	MAKE_COMPONENT(DATA, VelocityComponent)

    const sf::Vector2f& GetVelocity() const; 
	void SetVelocity(float x, float y);

private:
	sf::Vector2f m_VelocityVector;
};

