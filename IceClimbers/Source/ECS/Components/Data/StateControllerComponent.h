#pragma once
#include "ECS/AComponent.h"

#include "StateSystem/AState.h"

class StateControllerComponent final : public AComponent
{
public:
	explicit StateControllerComponent(AGameObject& owner);
	
	MAKE_COMPONENT(DATA, StateControllerComponent)
	
	AState& GetCurrentState() const;

	template <typename T, typename ...Args>
    void AddState(Args&&... args);
	
	template <typename T, typename ...Args>
	void ChangeState(Args&&... args);

private:
	AState* m_CurrentState;
	HashTable<String, AState*> m_StateTable;
};

template <typename T, typename ... Args>
void StateControllerComponent::AddState(Args&&... args)
{
	auto doesStateAlreadyExist = m_StateTable.find(T::GetStaticName());

	if (doesStateAlreadyExist == m_StateTable.end())
	{
		T* state = new T(*this, std::forward<Args>(args)...);
		m_StateTable[T::GetStaticName()] = state;

		if (m_CurrentState == nullptr)
		{
			m_CurrentState = state;
			m_CurrentState->Enter();
		}
	}
}

template <typename T, typename ... Args>
void StateControllerComponent::ChangeState(Args&&... args)
{
	if (m_CurrentState->GetName() == T::GetStaticName())
		return;
	
	m_CurrentState->Exit();
	
	auto doesStateAlreadyExist = m_StateTable.find(T::GetStaticName());
	
	T* state; 

	if (doesStateAlreadyExist == m_StateTable.end())
	{
		state = new T(*this, std::forward<Args>(args)...);
		m_StateTable[T::GetStaticName()] = state;
	}
	else
	{
		state = static_cast<T*>(m_StateTable[T::GetStaticName()]);
	}
	
	m_CurrentState = state;
	
	m_CurrentState->Enter();
}
