#pragma once
#include "ECS/AGameObject.h"

#include "EventSystem/IEventListener.h"

#include "ResourceSystem/Font/Font.h"

class TimerObject final : public AGameObject, public IEventListener
{
public:
	TimerObject(const String& name,
	            float duration);
	~TimerObject() override;
	void OnInitialize() override;
	void OnDestroy() override;
	void ReceiveEvent(String) override;

};
