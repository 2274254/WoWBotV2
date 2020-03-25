#include "CGUnit.h"
#include "Console.h"

namespace Agony
{
	namespace Native
	{
		Vector3 CGUnit::GetPosition()
		{
			__try
			{
				if (this == nullptr) return Vector3();
				return *reinterpret_cast<Vector3*>(this + static_cast<int>(Offsets::GameObject::Position));
			}
			__except (1)
			{
				Console::PrintLn("Native Exception thrown at: const Native::CGUnit::GetPosition() &");
			}
			return Vector3();
		}

		UnitRaceId CGUnit::GetRace()
		{
			__try
			{
				if (this == nullptr) return UnitRaceId::InvalidRaceId;
				return *reinterpret_cast<UnitRaceId*>(this + static_cast<int>(Offsets::GameObject::UnitRace));
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
				return *reinterpret_cast<UnitClassId*>(this + static_cast<int>(Offsets::GameObject::UnitClass));
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
	}
}
