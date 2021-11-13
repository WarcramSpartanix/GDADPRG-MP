#include "pch.h"
#include "TextComponent.h"

TextComponent::TextComponent(AGameObject& owner,
							 Font& font,
							 Uint fontSize,
							 const String& initialString) :
	AComponent{owner},
	m_Text{initialString, font.GetData(), fontSize}
{
	ResetOrigin();
}

sf::Text& TextComponent::GetText()
{
	return m_Text;
}

void TextComponent::SetString(const sf::String& string)
{
	m_Text.setString(string);
	ResetOrigin();
}

void TextComponent::SetFontSize(const Uint fontSize)
{
	m_Text.setCharacterSize(fontSize);
	ResetOrigin();
}

void TextComponent::SetFillColor(const sf::Color& color)
{
	m_Text.setFillColor(color);
}

void TextComponent::SetOutlineColor(const sf::Color& color)
{
	m_Text.setOutlineColor(color);
}

void TextComponent::SetOutlineThickness(const float thicknessValue)
{
	m_Text.setOutlineThickness(thicknessValue);
	ResetOrigin();
}

const String& TextComponent::GetString() const
{
	return m_Text.getString();
}

void TextComponent::ResetOrigin()
{
	const sf::FloatRect localBounds = m_Text.getLocalBounds();
	m_Text.setOrigin(localBounds.width / 2.0f, localBounds.height / 2.0f);
}
