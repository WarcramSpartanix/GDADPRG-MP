#include "pch.h"
#include "StateControllerComponent.h"

StateControllerComponent::StateControllerComponent(AGameObject& owner) :
	AComponent{owner},
	m_CurrentState{nullptr}
{
}

AState& StateControllerComponent::GetCurrentState() const
{
	ASSERT(m_CurrentState != nullptr,
			"StateController doesn't have state yet!")
	return *m_CurrentState;
}
