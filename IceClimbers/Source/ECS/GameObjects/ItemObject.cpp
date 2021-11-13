#include "pch.h"
#include "ItemObject.h"
#include "ECS/Components/Data/TransformComponent.h"
#include "ECS/Components/Render/SpriteRendererComponent.h"
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"
#include "ResourceSystem/ResourceManager.h"
#include "ResourceSystem/Texture/TextureAssets.h"

float ItemObject::ITEM_WIDTH = 30;
float ItemObject::ITEM_HEIGHT = 30;

ItemObject::ItemObject(const String& name, float x, float y, int index) : AGameObject(name)
{
	auto& transform = AddComponent<TransformComponent>();
	auto& spriteRenderer = AddComponent<SpriteRendererComponent>(ResourceManager::GetInstance().Acquire<Texture>(TextureNames::Level::ITEM_ICONS));
	AddComponent<BoxColliderComponent>(ITEM_WIDTH, ITEM_HEIGHT, false, ColliderLayer::Item, 0, 0);

	sf::Vector2i& texturePosition = sf::Vector2i(index, 0);
	sf::Vector2i& textureRect = sf::Vector2i(ITEM_WIDTH, ITEM_HEIGHT);

	spriteRenderer.SetTextureRect(texturePosition, textureRect);
		
	transform.SetPosition(x, y);
}

ItemObject::~ItemObject()
{
}

void ItemObject::OnInitialize()
{
}

void ItemObject::OnDestroy()
{
}
