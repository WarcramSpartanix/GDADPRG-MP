#include "pch.h"
#include "SpriteRendererComponent.h"

#include "ECS/AGameObject.h"

SpriteRendererComponent::SpriteRendererComponent(AGameObject& owner,
                                                 Texture& texture) :
	ARenderComponent{owner},
	m_TransformComponent{GetOwner().GetComponent<TransformComponent>()},
	m_Sprite{sf::Sprite()}
{
	m_Sprite.setTexture(texture.GetData());
	m_Sprite.setOrigin(texture.GetData().getSize().x / 2.0f,
					   texture.GetData().getSize().y / 2.0f);
}

void SpriteRendererComponent::Draw(sf::RenderWindow& window,
								   sf::RenderStates renderStates)
{
	// TODO: Account for child objects
	renderStates.transform = m_TransformComponent.GetWorldTransform();
	window.draw(m_Sprite, renderStates);
}

void SpriteRendererComponent::SetTextureRect(const sf::Vector2i& subTexturePosition,
                                             const sf::Vector2i& subTextureSize)
{
	const auto texturePosition = sf::Vector2i(subTexturePosition.x * subTextureSize.x,
	                                          subTexturePosition.y * subTextureSize.y);
	
	m_Sprite.setTextureRect(sf::IntRect(texturePosition,
											   subTextureSize));
	
	m_Sprite.setOrigin(subTextureSize.x / 2.0f, subTextureSize.y / 2.0f);
}
