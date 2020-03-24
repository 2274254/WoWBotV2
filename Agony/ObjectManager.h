#pragma once
#include "WoWObject.h"
#include <vector>

#pragma pack(push, 1)
struct TSGrowableArray
{
	uint64_t Capacity;
	uintptr_t Array;
	uint64_t Allocated;
	uint64_t unk_18;
};

struct TSLink
{
	uintptr_t Next; // TSLink
	uintptr_t Previous;
};

class ObjectGuid
{
public:
	ObjectGuid() = default;
	ObjectGuid(uint64_t low, uint64_t high) : LoWord(low), HiWord(high) {}
	~ObjectGuid() {}

	ObjectGuid(const ObjectGuid&) = default;
	ObjectGuid(ObjectGuid&&) = default;

	ObjectGuid& operator=(const ObjectGuid&) = default;
	ObjectGuid& operator=(ObjectGuid&&) = default;

	bool operator==(const ObjectGuid& rhs)
	{
		if (rhs.LoWord == LoWord && rhs.HiWord == HiWord)
			return true;
		return false;
	}

	bool operator!=(const ObjectGuid& rhs)
	{
		return *this == rhs;
	}

	bool operator!()
	{
		return (!LoWord && !HiWord);
	}

	std::string ToString()
	{
		//return fmt::format("{0:16X}:{1:16X}", LoWord, HiWord);
		return "";//TODO
	}

	uint64_t LoWord = 0;
	uint64_t HiWord = 0;
};

// size = 0x168?
struct CGObjectManager
{
	TSGrowableArray ActiveObjects;	// 0x000
	TSGrowableArray InvalidObjects;	// 0x020
	TSLink unk_040[14];				// 0x040
	TSLink VisibleObjects;			// 0x120
	TSLink unk_120;					// 0x128
	ObjectGuid LocalGuid;			// 0x140
	uint32_t MapId;					// 0x150
	uint32_t unk_154;				// 0x154
	uintptr_t unk_158;				// 0x158
	uintptr_t MovementGlobals;		// 0x160
};
#pragma pack(pop)

namespace Agony
{
	namespace Native
	{
		class ObjectManager
		{
		public:
			static std::vector<WoWObject*> GetVisibleObjects();
			static WoWObject* GetBaseFromToken(std::string token);
			static bool UnitExist(std::string token);
		};
	}
}
