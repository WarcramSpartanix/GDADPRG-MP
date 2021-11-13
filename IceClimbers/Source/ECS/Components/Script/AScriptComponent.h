#pragma once
#include "ECS/AComponent.h"

class AScriptComponent : public AComponent
{
public:
	explicit AScriptComponent(AGameObject& owner);
	virtual void Update(float deltaTime) = 0;
};
