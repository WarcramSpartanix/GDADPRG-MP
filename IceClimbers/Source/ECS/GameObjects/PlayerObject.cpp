#include "pch.h"
#include "PlayerObject.h"
#include "ECS/Components/Input/PlayerInputComponent.h"
#include "ECS/Components/Script/MoveComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ECS/Components/Script/SpriteAnimatorComponent.h"
#include "ECS/Components/Script/Collider/PlayerColliderComponent.h"
#include "ECS/Components/Script/Collider/PlayerTileBreakerComponent.h"
#include "ECS/Components/Script/Collider/PlayerGroundHammerComponent.h"

PlayerObject::PlayerObject(const String& name, Texture& texture) : AGameObject (name)
{
	auto& transform = AddComponent<TransformComponent>();
	transform.SetScale(1,1);
	AddComponent<SpriteRendererComponent>(texture);

	AddComponent<SpriteAnimatorComponent>(sf::Vector2i(0, 0),
		sf::Vector2i(0, 0),
		sf::Vector2i(60, 80),
		0.13f);

	transform.SetPosition(500.0f, 750.0f);
	AddComponent<PlayerInputComponent>();
	AddComponent<PlayerMovementComponent>();
	AddComponent<PlayerTileBreakerComponent>();
	AddComponent<PlayerColliderComponent>();
	AddComponent<PlayerGroundHammerComponent>();
}

PlayerObject::~PlayerObject()
{
}

void PlayerObject::OnInitialize()
{

}

void PlayerObject::OnDestroy()
{
	
}
