#include "pch.h"
#include "EventBroadcaster.h"

EventBroadcaster& EventBroadcaster::GetInstance()
{
	static EventBroadcaster instance;
	return instance;
}



EventBroadcaster::EventBroadcaster()
{
}

EventBroadcaster::~EventBroadcaster()
{
}

void EventBroadcaster::AddEventListener(String eventName, IEventListener* eventListener)
{
	if (m_EventMap.find(eventName) == m_EventMap.end())
		m_EventMap[eventName] = *new List<IEventListener*>();

	m_EventMap[eventName].push_back(eventListener);
}

void EventBroadcaster::RemoveEventListener(String eventName, IEventListener* eventListener)
{
	if (m_EventMap.find(eventName) != m_EventMap.end())
	{
		for (int i = 0; i < m_EventMap[eventName].size(); i++)
		{
			if (m_EventMap[eventName][i] == eventListener)
			{
				m_EventMap[eventName].erase(m_EventMap[eventName].begin() + i);
			}
		}
	}
}

void EventBroadcaster::BroadcastEvent(String eventName)
{
	for (size_t i = 0; i < m_EventMap[eventName].size(); i++)
	{
		m_EventMap[eventName][i]->ReceiveEvent(eventName);
	}
}