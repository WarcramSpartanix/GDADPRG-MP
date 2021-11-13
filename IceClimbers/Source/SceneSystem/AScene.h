#pragma once

class AScene
{
public:
	explicit AScene(const String& name);
	virtual ~AScene() = default;

	virtual void LoadResources() = 0;
	virtual void CreateObjects() = 0;
	virtual void UnloadResources() = 0;
	virtual void DestroyObjects();

	const String& GetName() const { return m_Name; }
	String GetName() { return m_Name; }

private:
	String m_Name;

	// TODO: Layer system
	// If receiving input, UI layer receives first then the game layer
	// If rendering, Game Layer goes first then the UI layer
};