#include "CGPlayer.h"
#include "Console.h"
#include "LuaFunctions.h"

namespace Agony
{
	namespace Native
	{
		CGObject* CGPlayer::GetItemBySlot(int slot)
		{
			__try
			{
				if (this == nullptr) return nullptr;
				return reinterpret_cast<CGObject * (__fastcall*)(void*, int slot)>(Offsets::Base + Offsets::CGBag_C__GetItemPointer)(this + 0x8118, slot - 1);
			}
			__except (1)
			{
				Console::PrintLn("Native Exception thrown at: const Native::CGPlayer::GetItemBySlot(int slot) &");
			}
			return nullptr;
		}
	}
}