#pragma once
#include "AScene.h"

class SceneManager final
{
public:
	static SceneManager& GetInstance();
	~SceneManager();

	SceneManager(SceneManager const&) = delete;
	void operator=(SceneManager const&) = delete;

	void RegisterScenes(List<AScene*>& scenes);
	void DeregisterAllScenes();

	void LoadScene(const String& sceneName);
	void UnloadActiveScenes();

	void InitializeScenes();
	void DeinitializeScenes();
    
	bool IsSceneActive(const String& sceneName) const;
private:
	SceneManager();

	List<AScene*> m_ActiveScenes;
	HashTable<String, AScene*> m_SceneStorage;
	Queue<AScene*> m_InitializeSceneQueue;
	Queue<AScene*> m_DeinitializeSceneQueue;
};