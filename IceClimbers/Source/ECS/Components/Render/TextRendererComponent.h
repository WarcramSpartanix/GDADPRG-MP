#pragma once

#include "ARenderComponent.h"

#include "ECS/AComponent.h"
#include "ECS/Components/Data/TextComponent.h"
#include "ECS/Components/Data/TransformComponent.h"

class TextRendererComponent final : public ARenderComponent
{
public:
	explicit TextRendererComponent(AGameObject& owner);

	MAKE_COMPONENT(RENDER, TextRendererComponent)
	
    void Draw(sf::RenderWindow& window,
              sf::RenderStates renderStates = sf::RenderStates::Default) override;

private:
	TransformComponent& m_TransformComponent;
	TextComponent& m_TextComponent;
};
