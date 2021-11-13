#pragma once
#include "ECS/AGameObject.h"

class BaseObject final : public AGameObject
{
public:
	explicit BaseObject(const String& name);
	~BaseObject() override;

	void OnInitialize() override;
	void OnDestroy() override;
};
