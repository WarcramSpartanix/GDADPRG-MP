#include "pch.h"
#include "TextButtonWidget.h"

#include "ECS/Components/Data/TextComponent.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Input/ButtonComponent.h"
#include "ECS/Components/Render/TextRendererComponent.h"

TextButtonWidget::TextButtonWidget(const String& name,
                                   Font& font,
                                   Uint fontSize,
                                   String textString,
                                   std::function<void(AGameObject&)> onExecute) :
	AWidget{name}
{
	TransformComponent& transform = AddComponent<TransformComponent>();
	TextComponent& textComponent = AddComponent<TextComponent>(font, fontSize, textString);
	AddComponent<TextRendererComponent>();
	

	auto onButtonIdle =
            [](AGameObject& buttonObject)->void
            {
            	buttonObject.GetComponent<TextComponent>().SetFillColor(sf::Color::White);
            };

	auto onButtonHover =
            [](AGameObject& buttonObject)->void
            {
            	buttonObject.GetComponent<TextComponent>().SetFillColor(sf::Color(128, 128, 128));
            };

	auto onButtonPress =
            [](AGameObject& buttonObject)->void
            {
            	buttonObject.GetComponent<TextComponent>().SetFillColor(sf::Color(32, 32, 32));
            };
	
	sf::Text& text = textComponent.GetText();
	AddComponent<ButtonComponent>(sf::Vector2f(text.getLocalBounds().width + 5.0f,
											   text.getLocalBounds().height + 5.0f),
						       onButtonIdle,
						       onButtonHover,
						       onButtonPress,
						       onExecute);
}

TextButtonWidget::~TextButtonWidget()
{
}

void TextButtonWidget::OnInitialize()
{
}

void TextButtonWidget::OnDestroy()
{
}
