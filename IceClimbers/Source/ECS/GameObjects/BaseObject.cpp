#include "pch.h"
#include "BaseObject.h"

BaseObject::BaseObject(const String& name) :
	AGameObject{name}
{
	Debug::Log("{0} has been created!", GetName());
}

BaseObject::~BaseObject()
{
}

void BaseObject::OnInitialize()
{
	Debug::Log("{0} has been initialized!", GetName());
}

void BaseObject::OnDestroy()
{
	Debug::Log("{0} has been destroyed!", GetName());
}
