#include "CGUnit.h"

namespace Agony
{
	Native::CGUnit* CGUnit::GetPtr()
	{
		return static_cast<Native::CGUnit*>(this->self);
	}

	UnitRaceId CGUnit::Race::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return static_cast<UnitRaceId>(unit->GetRace());
		}
		return Agony::UnitRaceId::Invalid;
	}

	UnitClassId CGUnit::Class::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return static_cast<UnitClassId>(unit->GetClass());
		}
		return Agony::UnitClassId::Invalid;
	}

	float CGUnit::fAngle::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetfAngle();
		}
		return 0;
	}

	Int32 CGUnit::CurrentHP::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetCurrentHP();
		}
		return 0;
	}

	Int32 CGUnit::MaxHP::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetMaxHP();
		}
		return 0;
	}

	Int32 CGUnit::CurrentMana::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetCurrentMana();
		}
		return 0;
	}

	Int32 CGUnit::MaxMana::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetMaxMana();
		}
		return 0;
	}

	Int32 CGUnit::Strength::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetStrength();
		}
		return 0;
	}

	Int32 CGUnit::Agility::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetAgility();
		}
		return 0;
	}

	Int32 CGUnit::Stamina::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetStamina();
		}
		return 0;
	}

	Int32 CGUnit::Intellect::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetIntellect();
		}
		return 0;
	}

	Int32 CGUnit::Spirit::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetSpirit();
		}
		return 0;
	}

	Int32 CGUnit::BaseArmor::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetBaseArmor();
		}
		return 0;
	}

	Int32 CGUnit::NegBuffArmor::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetNegBuffArmor();
		}
		return 0;
	}

	float CGUnit::CurrentSpeed::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetCurrentSpeed();
		}
		return 0;
	}

	float CGUnit::RunSpeed::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetRunSpeed();
		}
		return 0;
	}

	float CGUnit::FlightSpeed::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetFlightSpeed();
		}
		return 0;
	}

	float CGUnit::SwimSpeed::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetSwimSpeed();
		}
		return 0;
	}

	Int64 CGUnit::SpellStartTimeMS::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetSpellStartTimeMS();
		}
		return 0;
	}

	Int64 CGUnit::SpellEndTimeMS::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->GetSpellEndTimeMS();
		}
		return 0;
	}

	bool CGUnit::Interact()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->Interact();
		}
		return false;
	}

	bool CGUnit::IsInCombat()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->IsInCombat();
		}
		return false;
	}

	bool CGUnit::IsDead()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->IsDead();
		}
		return false;
	}

	bool CGUnit::IsGhost()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->IsGhost();
		}
		return false;
	}

	bool CGUnit::IsCasting()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			return unit->IsCasting();
		}
		return false;
	}
}