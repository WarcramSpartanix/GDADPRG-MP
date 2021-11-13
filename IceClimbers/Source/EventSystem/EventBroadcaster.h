#pragma once
#include "Event.h"
#include "EventNames.h"
#include "IEventListener.h"

class EventBroadcaster
{
public:
	static EventBroadcaster& GetInstance();
	void AddEventListener(String, IEventListener*);
	void RemoveEventListener(String, IEventListener*);

	void BroadcastEvent(String);

private:
	EventBroadcaster();
	~EventBroadcaster();

	

	HashTable<String, List<IEventListener*>> m_EventMap;
};

