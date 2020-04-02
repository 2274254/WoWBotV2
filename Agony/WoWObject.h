#pragma once
#include "vector3.h"

enum WoWObjectType : uint8_t
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

class WoWObject
{
public:
	char pad_0000[16]; //0x0000
	WoWObjectType Type; //0x0010
	char pad_0011[255]; //0x0011
	Vector3 pos; //0x0110
	char pad_011C[4]; //0x011C
	float fAngle; //0x0120
	char pad_0124[5208]; //0x0124
	int8_t unitRace; //0x157C
	int8_t unitClass; //0x157D
	char pad_157E[10]; //0x157E
	int32_t currentHP; //0x1588
	char pad_158C[4]; //0x158C
	int32_t maxHP; //0x1590
	char pad_1594[500]; //0x1594
	int32_t currentMana; //0x1788
	char pad_178C[20]; //0x178C
	int32_t maxMana; //0x17A0
	char pad_17A4[100]; //0x17A4
	int32_t strength; //0x1808
	int32_t agility; //0x180C
	int32_t stamina; //0x1810
	int32_t intellect; //0x1814
	int32_t spirit; //0x1818
	char pad_181C[28]; //0x181C
	int32_t baseArmor; //0x1838
	char pad_183C[24]; //0x183C
	int32_t negBuffArmor; //0x1854
	char pad_1858[9600]; //0x1858
	int32_t money; //0x3DD8
	char pad_3DDC[4]; //0x3DDC
	int32_t currentXP; //0x3DE0
	int32_t maxXP; //0x3DE4
};
