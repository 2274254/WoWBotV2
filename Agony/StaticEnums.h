#pragma once
namespace Agony
{
	namespace Native
	{
		enum WoWObjectType : signed char
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

		enum UnitRaceId : signed char
		{
			InvalidRaceId = 0,
			Human = 1,
			Orc = 2,
			Dwarf = 3,
			NightElf = 4,
			Undead = 5,
			Tauren = 6,
			Gnome = 7,
			Troll = 8,
			Goblin = 9,
			BloodElf = 10,
			Draenei = 11,
			FelOrc = 12,
			Naga = 13,
			Broken = 14,
			Skeleton = 15,
			Vrykul = 16,
			Tuskarr = 17,
			ForestTroll = 18,
			Taunka = 19,
			NorthrendSkeleton = 20,
			IceTroll = 21,
			Worgen = 22,
			Gilnean = 23,
			PandarenNeutral = 24,
			PandarenAlliance = 25,
			PandarenHorde = 26,
			Nightborne = 27,
			HighmountainTauren = 28,
			VoidElf = 29,
			LightforgedDraenei = 30,
			ZandalariTroll = 31,
			KulTiran = 32,
			ThinHuman = 33,
			DarkIronDwarf = 34,
			Vulpera = 35,
			MagharOrc = 36,
			Mechagnome = 37
		};

		enum UnitClassId : signed char
		{
			InvalidClassId = 0,
			Warrior = 1,
			Paladin = 2,
			Hunter = 3,
			Rogue  = 4,
			Priest = 5,
			DeathKnight = 6,
			Shaman = 7,
			Mage = 8,
			Warlock = 9,
			Monk = 10,
			Druid = 11,
			DemonHunter = 12
		};
	}
}