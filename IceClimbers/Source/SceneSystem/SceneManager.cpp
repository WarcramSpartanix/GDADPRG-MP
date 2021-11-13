#include "pch.h"
#include "SceneManager.h"
#include "Core/Debug.h"

SceneManager& SceneManager::GetInstance()
{
    static SceneManager instance;
    return instance;
}

SceneManager::SceneManager() :
    m_SceneStorage(HashTable<String, AScene*>())
{
}

void SceneManager::DeregisterAllScenes()
{
    UnloadActiveScenes();

    // No currently registered scenes should be initialized from this point on.
    while (!m_InitializeSceneQueue.empty())
    {
        m_InitializeSceneQueue.pop();
    }
    
    for (auto sceneEntry : m_SceneStorage)
    {
        if (sceneEntry.second != nullptr)
        {
            delete sceneEntry.second;
        }
    }
    
    m_SceneStorage.clear();
}

SceneManager::~SceneManager()
{
}

void SceneManager::RegisterScenes(List<AScene*>& scenes)
{
    for (auto* scene : scenes)
    {
        ASSERT(scene != nullptr,
               "[SceneManager] Attempting to register a null scene!")
        
        if (m_SceneStorage.find(scene->GetName()) == m_SceneStorage.end())
        {
            m_SceneStorage[scene->GetName()] = scene;
        }
    }
}

void SceneManager::LoadScene(const String& sceneName)
{
    auto* scene = m_SceneStorage[sceneName];

    ASSERT(scene != nullptr,
        "[SceneManager] Attempting to load a null / unregistered scene {0}!",
                 sceneName);
    
    m_InitializeSceneQueue.push(scene);
    
    UnloadActiveScenes();

}

void SceneManager::UnloadActiveScenes()
{
    for (auto* scene : m_ActiveScenes)
    {
        m_DeinitializeSceneQueue.push(scene);
    }
    m_ActiveScenes.clear();
    m_ActiveScenes.shrink_to_fit();
}

void SceneManager::InitializeScenes()
{
    while (!m_InitializeSceneQueue.empty())
    {
        auto* scene = m_InitializeSceneQueue.front();
        scene->LoadResources();
        scene->CreateObjects();
        m_InitializeSceneQueue.pop();
        m_ActiveScenes.emplace_back(scene);
    }
}

void SceneManager::DeinitializeScenes()
{
    while (!m_DeinitializeSceneQueue.empty())
    {
        auto* scene = m_DeinitializeSceneQueue.front();
        scene->DestroyObjects();
        scene->UnloadResources();
        m_DeinitializeSceneQueue.pop();
    }
}

bool SceneManager::IsSceneActive(const String& sceneName) const
{
    bool isFound = false;
    for (auto* scene : m_ActiveScenes)
    {
        if (scene->GetName() == sceneName)
        {
            isFound = true;
            break;
        }
    }
    return isFound;
}