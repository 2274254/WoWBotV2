#include "CGUnit.h"
#include "Console.h"

namespace Agony
{
	namespace Native
	{
		UnitRaceId CGUnit::GetRace()
		{
			__try
			{
				if (this == nullptr) return UnitRaceId::InvalidRaceId;
				return *reinterpret_cast<UnitRaceId*>(this + static_cast<uintptr_t>(Offsets::GameObject::UnitRace));
			}
			__except (1)
			{
				Console::PrintLn("Native Exception thrown at: const Native::CGUnit::GetRace() &");
			}
			return UnitRaceId::InvalidRaceId;
		}

		UnitClassId CGUnit::GetClass()
		{
			__try
			{
				if (this == nullptr) return UnitClassId::InvalidClassId;
				return *reinterpret_cast<UnitClassId*>(this + static_cast<uintptr_t>(Offsets::GameObject::UnitClass));
			}
			__except (1)
			{
				Console::PrintLn("Native Exception thrown at: const Native::CGUnit::GetRace() &");
			}
			return UnitClassId::InvalidClassId;
		}

		//Not tested:
		bool CGUnit::CanAttack(CGUnit* target)
		{
			__try
			{
				if (this == nullptr || target == nullptr) return false;
				return reinterpret_cast<bool(__fastcall*)(CGObject*, CGObject*)>(Offsets::Base + Offsets::CGUnit_C__CanAttack)(this, target);
			}
			__except (1)
			{
				Console::PrintLn("Native Exception thrown at: const Native::CGUnit::CanAttack(CGUnit target) &");
			}
			return false;
		}

		bool CGUnit::Interact()
		{
			return reinterpret_cast<bool(__fastcall*)(ObjectGuid*)>(Offsets::Base + Offsets::CGGameUI__OnSpriteRightClick)(&this->GetGuid());
		}

		bool CGUnit::IsInCombat()
		{
			__try
			{
				if (this == nullptr) return false;
				DWORD someWeirdFlag = *reinterpret_cast<DWORD*>(this + static_cast<uintptr_t>(Offsets::GameObject::AffectingCombat));
				return (someWeirdFlag >> 19) & 1;
			}
			__except (1)
			{
				Console::PrintLn("Native Exception thrown at: const Native::CGUnit::IsInCombat() &");
			}
			return false;
		}
	}
}