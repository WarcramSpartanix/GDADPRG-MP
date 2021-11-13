#include "pch.h"
#include "AWidget.h"

AWidget::AWidget(const String& name) :
	AGameObject{name}
{
	// AddComponent<RectTransform>();
}

AWidget::~AWidget()
{
}
