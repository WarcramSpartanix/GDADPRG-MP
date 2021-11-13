#pragma once
#include "UISystem/AWidget.h"

class BaseWidget final : public AWidget
{
public:
	explicit BaseWidget(const String& name);
	~BaseWidget() override;
	void OnInitialize() override;
	void OnDestroy() override;
};
