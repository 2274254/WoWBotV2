#pragma once
#include "../Agony/CGUnit.h"
#include "CGObject.h"
using namespace SharpDX;
using namespace System;

namespace Agony
{
	public ref class CGUnit : public CGObject
	{
		Native::CGUnit* GetPtr();
	public:
		CGUnit(Native::CGObject* obj) : CGObject(obj) {}

		property UnitRaceId Race
		{
			UnitRaceId get();
		}

		property UnitClassId Class
		{
			UnitClassId get();
		}

		property float fAngle
		{
			float get();
		}

		property Int32 CurrentHP
		{
			Int32 get();
		}

		property Int32 MaxHP
		{
			Int32 get();
		}

		property Int32 CurrentMana
		{
			Int32 get();
		}

		property Int32 MaxMana
		{
			Int32 get();
		}

		property Int32 Strength
		{
			Int32 get();
		}

		property Int32 Agility
		{
			Int32 get();
		}

		property Int32 Stamina
		{
			Int32 get();
		}

		property Int32 Intellect
		{
			Int32 get();
		}

		property Int32 Spirit
		{
			Int32 get();
		}

		property Int32 BaseArmor
		{
			Int32 get();
		}

		property Int32 NegBuffArmor
		{
			Int32 get();
		}

		property float CurrentSpeed
		{
			float get();
		}

		property float RunSpeed
		{
			float get();
		}

		property float FlightSpeed
		{
			float get();
		}

		property float SwimSpeed
		{
			float get();
		}

		bool Interact();

		bool IsInCombat();
	};
}
