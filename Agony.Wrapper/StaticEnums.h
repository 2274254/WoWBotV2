#include <Windows.h>
#pragma once
namespace Agony
{
	public enum class WoWObjectType : signed char
	{
		Object = 0,
		Item = 1,
		Container = 2,
		AzeriteEmpoweredItem = 3,
		AzeriteItem = 4,
		Unit = 5,
		Player = 6,
		ActivePlayer = 7,
		GameObject = 8,
		DynamicObject = 9,
		Corpse = 10,
		AreaTrigger = 11,
		Scene = 12,
		Conversation = 13,
		AIGroup = 14,
		Scenario = 15,
		Loot = 16,
		Invalid = 17,
	};
}