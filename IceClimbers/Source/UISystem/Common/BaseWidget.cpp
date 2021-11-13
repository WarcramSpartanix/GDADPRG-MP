#include "pch.h"
#include "BaseWidget.h"

BaseWidget::BaseWidget(const String& name) :
	AWidget{name}
{
}

BaseWidget::~BaseWidget()
{
}

void BaseWidget::OnInitialize()
{
}

void BaseWidget::OnDestroy()
{
}
