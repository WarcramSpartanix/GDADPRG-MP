#include "pch.h"
#include "BonusWall.h"
#include "ECS/GameObjectManager.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"

float BonusWall::WALL_WIDTH = 90;
float BonusWall::WALL_HEIGHT = 30;

BonusWall::BonusWall(const String& name, float x, float y, Texture& texture) : AGameObject(name)
{
	auto& transform = AddComponent<TransformComponent>();
	AddComponent<SpriteRendererComponent>(texture);
	AddComponent<BoxColliderComponent>(WALL_WIDTH, WALL_HEIGHT, true, ColliderLayer::Wall, 0, 0);
	transform.SetPosition(x, y);
}

BonusWall::~BonusWall()
{
}

void BonusWall::OnInitialize()
{
}

void BonusWall::OnDestroy()
{
}
