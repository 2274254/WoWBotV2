#pragma once
#include "CGObject.h"
#include "vector3.h"
#include <string>

namespace Agony
{
	namespace Native
	{
		DLLEXPORT class CGUnit
		{
		public:
			std::string GetName();

			MAKE_GET(Position, Vector3, Offsets::GameObject::Position);
			MAKE_GET(fAngle, float, Offsets::GameObject::fAngle);
			MAKE_GET(UnitRace, int8_t, Offsets::GameObject::UnitRace);
			MAKE_GET(UnitClass, int8_t, Offsets::GameObject::UnitClass);
			MAKE_GET(CurrentHP, int32_t, Offsets::GameObject::CurrentHP);
			MAKE_GET(MaxHP, int32_t, Offsets::GameObject::MaxHP);
			MAKE_GET(CurrentMana, int32_t, Offsets::GameObject::CurrentMana);
			MAKE_GET(MaxMana, int32_t, Offsets::GameObject::MaxMana);
			MAKE_GET(Strength, int32_t, Offsets::GameObject::Strength);
			MAKE_GET(Agility, int32_t, Offsets::GameObject::Agility);
			MAKE_GET(Stamina, int32_t, Offsets::GameObject::Stamina);
			MAKE_GET(Intellect, int32_t, Offsets::GameObject::Intellect);
			MAKE_GET(Spirit, int32_t, Offsets::GameObject::Spirit);
			MAKE_GET(BaseArmor, int32_t, Offsets::GameObject::BaseArmor);
			MAKE_GET(NegBuffArmor, int32_t, Offsets::GameObject::NegBuffArmor);
			MAKE_GET(Money, int32_t, Offsets::GameObject::Money);
			MAKE_GET(CurrentXP, int32_t, Offsets::GameObject::CurrentXP);
			MAKE_GET(MaxXP, int32_t, Offsets::GameObject::MaxXP);
		};
	}
}
