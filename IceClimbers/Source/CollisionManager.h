#pragma once
#include "ECS/Components/Script/Collider/BoxColliderComponent.h"

class CollisionManager
{
public:
	static CollisionManager& GetInstance();
	List<BoxColliderComponent*> GetAllColliders();
	void AddCollider(BoxColliderComponent* collider);
	void RemoveCollider(BoxColliderComponent* collider);

private:
	CollisionManager();
	~CollisionManager();

	List<BoxColliderComponent*> m_ColliderList;
};

