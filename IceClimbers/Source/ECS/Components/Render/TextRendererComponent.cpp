#include "pch.h"
#include "TextRendererComponent.h"

#include "ECS/AGameObject.h"

TextRendererComponent::TextRendererComponent(AGameObject& owner) :
	ARenderComponent{owner},
	m_TransformComponent{GetOwner().GetComponent<TransformComponent>()},
	m_TextComponent{GetOwner().GetComponent<TextComponent>()}
{
}

void TextRendererComponent::Draw(sf::RenderWindow& window,
	sf::RenderStates renderStates)
{
	renderStates.transform = m_TransformComponent.GetWorldTransform();
	window.draw(m_TextComponent.GetText(), renderStates);
}
