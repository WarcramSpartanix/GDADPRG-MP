#include "pch.h"
#include "TopiObject.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ECS/Components/Script/SpriteAnimatorComponent.h"
#include "ECS/Components/Script/TopiBehaviorComponent.h"
#include "ECS/Components/Script/Collider/TopiColliderComponent.h"
#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Texture/Texture.h"
#include "ResourceSystem/Texture/TextureAssets.h"

TopiObject::TopiObject(const String& name, float x, float y, int direction) : AGameObject(name)
{
	auto& transform = AddComponent<TransformComponent>();
	AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>("Topi"));

	AddComponent<SpriteAnimatorComponent>(sf::Vector2i{0, 0},
										  sf::Vector2i{2, 0},
										  sf::Vector2i{45, 45},
										  0.2f);
	transform.SetScale(-direction, 1.0f);
	
	AddComponent<TopiColliderComponent>();
	AddComponent<TopiBehaviorComponent>(x, y, direction);

	transform.SetPosition(x, y);
}

TopiObject::~TopiObject()
{
}

void TopiObject::OnInitialize()
{
}

void TopiObject::OnDestroy()
{
}

void TopiObject::Kill()
{
	this->GetComponent<TopiBehaviorComponent>().Kill();
}
