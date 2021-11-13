#include "pch.h"
#include "PterodactylObject.h"
#include "ECS/Components/Script/CloudMovementComponent.h"
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ResourceSystem/ResourceManager.h"

PterodactylObject::PterodactylObject(const String& name) : AGameObject(name)
{
	auto& transform = AddComponent<TransformComponent>();
	AddComponent<BoxColliderComponent>(90, 30, false, ColliderLayer::Bird, 0, 0);
	AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>("Bird"));
	AddComponent<CloudMovementComponent>(200.0f);		// works as the same as intended so no point in making another component


	transform.SetPosition(0, -2270);
}

PterodactylObject::~PterodactylObject()
{
}

void PterodactylObject::OnInitialize()
{
}

void PterodactylObject::OnDestroy()
{
}
