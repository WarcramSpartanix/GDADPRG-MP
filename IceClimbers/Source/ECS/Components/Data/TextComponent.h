#pragma once
#include <SFML/Graphics/Text.hpp>

#include "ECS/AComponent.h"

#include "ResourceSystem/Font/Font.h"

class TextComponent final : public AComponent
{
public:
	TextComponent(AGameObject& owner,
				  Font& font,
				  Uint fontSize = 32U,
				  const String& initialString = "Sample Text");
	
	MAKE_COMPONENT(DATA, TextComponent)

	sf::Text& GetText();

	void SetString(const sf::String& string);
	void SetFontSize(Uint fontSize);
	void SetFillColor(const sf::Color& color);
	void SetOutlineColor(const sf::Color& color);
	void SetOutlineThickness(float thicknessValue);

	const String& GetString() const;
private:
	sf::Text m_Text;

	void ResetOrigin();
};
