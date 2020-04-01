#pragma once
#include "WoWObject.h"
#include "CGObject.h"
#include "Macros.h"
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

struct CGObjectManager
{
	TSGrowableArray ActiveObjects;	// 0x000
	TSGrowableArray InvalidObjects;	// 0x020
	TSLink unk_040[14];				// 0x040
	TSLink VisibleObjects;			// 0x120
	TSLink unk_120;					// 0x128
	Agony::Native::ObjectGuid LocalGuid;			// 0x140
	uint32_t MapId;					// 0x150
	uint32_t unk_154;				// 0x154
	uintptr_t unk_158;				// 0x158
	uintptr_t MovementGlobals;		// 0x160
};
#pragma pack(pop)

struct CurMgr0x8Entry
{
public:
	uint64_t Next;							//0x0000
	Agony::Native::ObjectGuid WowGuid;		//0x0008
	Agony::Native::CGObject* ObjectBase;	//0x0018
}; //Size: 0x0020

namespace Agony
{
	namespace Native
	{
		class DLLEXPORT ObjectManager
		{
		public:
			static std::vector<CGObject*> GetVisibleObjects();
			static std::vector<CGObject*> GetObjects();
			static CGObject* GetBaseFromToken(std::string token);
			static ObjectGuid GetGUIDFromToken(std::string token);
			static CGObject* GetObjectFromGuid(ObjectGuid* guid);
			static bool UnitExist(std::string token);
		};
	}
}
