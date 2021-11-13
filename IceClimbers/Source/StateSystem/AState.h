#pragma once

#define MAKE_STATE(state)	static const char* GetStaticName() { return #state; }       \
							String GetName() const override { return #state; }

class StateControllerComponent;
class AState
{
public:
	explicit AState();
	virtual ~AState() = default;

	virtual String GetName() const = 0;

	virtual void Enter() = 0;
	virtual void Exit() = 0;

	void TransitionToState(const String& state);
	void SetFloat();
	void SetInt();
	void SetBool();
	void SetTrigger();
private:
	HashTable<String, AState*> m_TransitionToStateTable;
};
