#pragma once
#include <Core/TypeAlias.h>

#define MAKE_COMPONENT(type, component)     static ComponentType GetStaticType() { return ComponentType::type; }	\
                                            static const char* GetStaticName() { return #component; }               \
                                            ComponentType GetType() const override { return ComponentType::type; }  \
                                            String GetName() const override { return #component; }

class AGameObject;

enum class ComponentType
{
    NONE,
    DATA,
    INPUT,
    SCRIPT,
    RENDER
};

class AComponent
{
public:
    explicit AComponent(AGameObject& owner);
    virtual ~AComponent() = 0;
    AGameObject& GetOwner() const;
    
    virtual ComponentType GetType() const = 0;
    virtual String GetName() const = 0;

    bool operator==(const AComponent& other) const;
    bool operator!=(const AComponent& other) const;

private:
    AGameObject& m_Owner;
};