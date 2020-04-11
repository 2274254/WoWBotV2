// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdint.h>
#include <iostream>

class ObjectGuid
{
	ObjectGuid() = default;
	ObjectGuid(uint64_t low, uint64_t high) : LoWord(low), HiWord(high) {}
	~ObjectGuid() {}

	ObjectGuid(const ObjectGuid&) = default;
	ObjectGuid(ObjectGuid&&) = default;

	ObjectGuid& operator=(const ObjectGuid&) = default;
	ObjectGuid& operator=(ObjectGuid&&) = default;

	bool operator==(const ObjectGuid & rhs)
	{
		if (rhs.LoWord == LoWord && rhs.HiWord == HiWord)
			return true;
		return false;
	}

	bool operator!=(const ObjectGuid & rhs)
	{
		return *this == rhs;
	}

	bool operator!()
	{
		return (!LoWord && !HiWord);
	}
	/*
	std::string ToString()
	{
		//return fmt::format("{0:16X}:{1:16X}", LoWord, HiWord);
		return "";//TODO
	}

	GuidType Type()
	{
		return (GuidType)(HiWord >> 58);
	}
	*/
	unsigned short RealmId()
	{
		return (unsigned short)((HiWord >> 42) & 0x1FFF);
	}

	unsigned short ServerId()
	{
		return (unsigned short)((LoWord >> 40) & 0x1FFF);
	}

	unsigned short MapId()
	{
		return (unsigned short)((HiWord >> 29) & 0x1FFF);
	}

	unsigned int Id()
	{
		return (unsigned int)(HiWord & 0xFFFFFF) >> 6;
	}

	unsigned long CreationBits()
	{
		return LoWord & 0xFFFFFFFFFF;
	}

	uint64_t LoWord = 0;
	uint64_t HiWord = 0;
};

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
	ObjectGuid LocalGuid;			// 0x140
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
	ObjectGuid WowGuid;		//0x0008
	uintptr_t ObjectBase;	//0x0018
}; //Size: 0x0020

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
		case DLL_PROCESS_ATTACH:
		{
			AllocConsole();
			freopen("CON", "w", stdout);

			auto playerPtr = reinterpret_cast<uintptr_t (__fastcall*)(const char*)>(reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + 0x16634C0)("player");
			std::cout << "Player ptr = " << playerPtr << std::endl;

			const CGObjectManager* m_CurObjectMgr = *reinterpret_cast<CGObjectManager**>(reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr)) + 0x29BBF30);
			std::cout << "ActiveObjects.Capacity = " << m_CurObjectMgr->ActiveObjects.Capacity << std::endl;
			std::cout << "ActiveObjects.Array ptr = " << std::hex << m_CurObjectMgr->ActiveObjects.Array << std::endl;
			for (uint64_t i = 0; i < m_CurObjectMgr->ActiveObjects.Capacity; i++)
			{
				CurMgr0x8Entry* entry = *reinterpret_cast<CurMgr0x8Entry**>(m_CurObjectMgr->ActiveObjects.Array + (8 * i));
				if (entry != nullptr && entry->ObjectBase != 0)
				{
					std::cout << "Possible obj ptr = " << std::hex << entry->ObjectBase << std::endl;
				}
			}
		}
		break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

