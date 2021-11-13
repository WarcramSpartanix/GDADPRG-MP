#pragma once
#include "ResourceSystem/Font/Font.h"

#include "UISystem/AWidget.h"

class TextButtonWidget final : public AWidget
{
public:
	explicit TextButtonWidget(const String& name,
							  Font& font,
							  Uint fontSize,
							  String textString,
							  std::function<void(AGameObject&)> onExecute);
	~TextButtonWidget() override;
	void OnInitialize() override;
	void OnDestroy() override;
};
