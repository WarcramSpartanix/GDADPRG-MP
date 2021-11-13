#pragma once
#include <SFML/Graphics/Transformable.hpp>

#include "ECS/AComponent.h"

class TransformComponent final : public AComponent
{
public:
	explicit TransformComponent(AGameObject& owner);

	MAKE_COMPONENT(DATA, TransformComponent)
	
	const sf::Vector2f& GetPosition() const;
	const sf::Vector2f& GetWorldPosition() const;

	void SetPosition(float x, float y);

	void Move(float x, float y);

	float GetRotation() const; 
	void SetRotation(float angle);

	void Rotate(float angleAdded);

	const sf::Vector2f& GetScale() const; 
	void SetScale(float scaleX, float scaleY);

	void Scale(float scaleVectorX, float scaleVectorY);

	void SetOrigin(float x, float y);
	const sf::Vector2f& GetOrigin() const;

	const sf::Transform& GetLocalTransform() const;
	const sf::Transform& GetWorldTransform() const;
private:
	sf::Transformable m_Transform;
	sf::Transform m_WorldTransform;

	void UpdateWorldTransform();
};