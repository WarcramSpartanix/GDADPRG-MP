#include "pch.h"
#include "IceCubeObject.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ResourceSystem/ResourceManager.h"
#include "ECS/Components/Script/Collider/IceCubeColliderComponent.h"

IceCubeObject::IceCubeObject(const String& name, int direction) : AGameObject(name)
{
	auto& transform = AddComponent<TransformComponent>();
	AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>("IceCube"));
	AddComponent<IceCubeColliderComponent>(direction);

	transform.SetPosition(0, 0);
}

IceCubeObject::~IceCubeObject()
{
}

void IceCubeObject::OnInitialize()
{
}

void IceCubeObject::OnDestroy()
{
}

void IceCubeObject::SetTopiParent(TopiObject* topiParent)
{
	GetComponent<IceCubeColliderComponent>().SetTopiParent(topiParent);
}
