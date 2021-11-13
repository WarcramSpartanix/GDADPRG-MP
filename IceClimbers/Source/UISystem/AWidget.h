#pragma once
#include "ECS/AGameObject.h"

class AWidget : public AGameObject
{
public:
	explicit AWidget(const String& name);
	virtual ~AWidget();
};
