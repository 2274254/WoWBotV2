#include "CGUnit.h"

namespace Agony
{
	Native::CGUnit* CGUnit::GetPtr()
	{
		return static_cast<Native::CGUnit*>(this->self);
	}

	SharpDX::Vector3 CGUnit::Position::get()
	{
		auto unit = this->GetPtr();
		if (unit != nullptr)
		{
			auto pos = unit->GetPosition();
			return SharpDX::Vector3(pos.x, pos.y, pos.z);
		}
		return SharpDX::Vector3::Zero;
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
}
