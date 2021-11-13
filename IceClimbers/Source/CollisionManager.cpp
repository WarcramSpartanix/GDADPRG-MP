#include "pch.h"
#include "CollisionManager.h"

CollisionManager& CollisionManager::GetInstance()
{
    static CollisionManager instance;
    return instance;
}

List<BoxColliderComponent*> CollisionManager::GetAllColliders()
{
    return m_ColliderList;
}

void CollisionManager::AddCollider(BoxColliderComponent* collider)
{
    m_ColliderList.push_back(collider);
}

void CollisionManager::RemoveCollider(BoxColliderComponent* collider)
{
    for (int i = 0; i < m_ColliderList.size(); i++)
    {
        if (collider == m_ColliderList[i])
        {
            m_ColliderList.erase(m_ColliderList.begin() + i);
            break;
        }
    }
}

CollisionManager::CollisionManager()
{
}

CollisionManager::~CollisionManager()
{
}
