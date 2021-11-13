#pragma once
#include "pch.h"

class IEventListener
{
public:
	virtual void ReceiveEvent(String) = 0;

};