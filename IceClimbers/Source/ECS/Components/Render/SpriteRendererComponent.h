#pragma once
#include <SFML/Graphics/Sprite.hpp>

#include "ARenderComponent.h"

#include "ECS/AComponent.h"
#include "ECS/Components/Data/TransformComponent.h"

#include "ResourceSystem/Texture/Texture.h"

class SpriteRendererComponent final : public ARenderComponent
{
public:
	explicit SpriteRendererComponent(AGameObject& owner,
								     Texture& texture);

	MAKE_COMPONENT(RENDER, SpriteRendererComponent)
	
	void Draw(sf::RenderWindow& window,
              sf::RenderStates renderStates = sf::RenderStates::Default) override;

	void SetTextureRect(const sf::Vector2i& subTexturePosition,
						const sf::Vector2i& subTextureSize);
private:
	TransformComponent& m_TransformComponent;
	sf::Sprite m_Sprite;
};
