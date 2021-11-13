#include "pch.h"
#include "TimerObject.h"

#include "Game.h"

#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/TextRendererComponent.h"
#include "ECS/Components/Script/TimerBehaviorComponent.h"

#include "EventSystem/EventBroadcaster.h"

#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Font/FontAssets.h"

#include "SceneSystem/SceneManager.h"

TimerObject::TimerObject(const String& name,
                         float duration) :
	AGameObject{name}
{
	auto& transform = AddComponent<TransformComponent>();
	transform.SetPosition(Game::SCREEN_WIDTH / 2.0f, -1850);

	auto& font = ResourceManager::GetInstance().Acquire<Font>(FontNames::EMULOGIC);
	auto& text = AddComponent<TextComponent>(font);
	
	AddComponent<TextRendererComponent>();
	AddComponent<TimerBehaviorComponent>(duration, []() -> void
	{
		SceneManager::GetInstance().LoadScene("ResultScene");
	});

	EventBroadcaster::GetInstance().AddEventListener("BonusStart", this);
	
}

TimerObject::~TimerObject()
{
}

void TimerObject::OnInitialize()
{
}

void TimerObject::OnDestroy()
{
}

void TimerObject::ReceiveEvent(String eventName)
{
	if (eventName == "BonusStart")
	{
		GetComponent<TimerBehaviorComponent>().Start();
		
	}
	
}
