#include "pch.h"
#include "CloudObject.h"
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ECS/Components/Script/CloudMovementComponent.h"

CloudObject::CloudObject(const String& name, Texture& texture, float x, float y, float width, float speed, int heightLevel) :
	AGameObject(name)
{
	auto& transform = AddComponent<TransformComponent>();
	AddComponent<SpriteRendererComponent>(texture);
	AddComponent<BoxColliderComponent>(width, 30.0f, true, ColliderLayer::Cloud, 0, 0);
	AddComponent<CloudMovementComponent>(speed);

	transform.SetPosition(x, y);
	transform.SetScale(1, 1);

	m_HeightLevel = heightLevel;
}

CloudObject::~CloudObject()
{
}

void CloudObject::OnInitialize()
{
}

void CloudObject::OnDestroy()
{
}

int CloudObject::GetHeightLevel()
{
    return m_HeightLevel;
}

float CloudObject::GetLastMoveDistance()
{
	return GetComponent<CloudMovementComponent>().GetLastMoveDistance();
}
