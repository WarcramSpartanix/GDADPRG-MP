#include "pch.h"
#include "TileObject.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"

float TileObject::TILE_SIZE = 30.0f;

TileObject::TileObject(const String& name, Texture& texture, float x, float y, bool isDestructible, int heightLevel) : AGameObject(name)
{
	auto& transform = AddComponent<TransformComponent>();
	AddComponent<SpriteRendererComponent>(texture);
	AddComponent<BoxColliderComponent>(TILE_SIZE, TILE_SIZE, true, ColliderLayer::Tile, 0, 0);

	transform.SetPosition(x, y);
	transform.SetScale(1, 1);

	m_IsDestructible = isDestructible;
	m_HeightLevel = heightLevel;
}

TileObject::~TileObject()
{
}

void TileObject::OnInitialize()
{
}

void TileObject::OnDestroy()
{
}

void TileObject::DestroyTile()
{
	// Destroy Tile Animation
	Debug::Log("Destroying Tile {0}", GetName());
	GameObjectManager::GetInstance().DestroyGameObject(*this); // causing crash, need to fix
}

int TileObject::GetHeightLevel()
{
	return m_HeightLevel;
}
