#ifndef WALKER_SYSTEM_H
#define WALKER_SYSTEM_H

#include <NDK/System.hpp>
#include <NDK/Component.hpp>
#include "../Components/WalkerComponent.hpp"
#include "../World/WorldMap.hpp"

#include <exception>

class WalkerSystem : public Ndk::System<WalkerSystem>
{
public:
	WalkerSystem(WorldMap& map);
	~WalkerSystem() = default;

	static Ndk::SystemIndex systemIndex;

private:
	WorldMap& m_worldMap;

	void OnUpdate(float elapsed) override;
};

#endif // !WALKER_SYSTEM_H
