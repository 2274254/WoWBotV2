#include "CGObject.h"
#include "Console.h"

namespace Agony::Native
{
	WoWObjectType CGObject::GetType()
	{
		__try
		{
			if (this == nullptr) return WoWObjectType::Invalid;
			return *reinterpret_cast<WoWObjectType*>(this + static_cast<uintptr_t>(Offsets::GameObject::Type));//oops just realise all those int, is bad lol, could crash the game
		}
		__except (1)
		{
			Console::PrintLn("Native Exception thrown at: const Native::CGObject::GetType() &");
		}
		return WoWObjectType::Invalid;
	}

	ObjectGuid CGObject::GetGuid()
	{
		if (this == nullptr) return ObjectGuid{};
		return *reinterpret_cast<ObjectGuid*>(this + static_cast<uintptr_t>(Offsets::GameObject::Guid));
	}

	std::string CGObject::GetName()
	{
		const char* name = "Unknown";
		if (this == nullptr)
		{
			return "Unknown";
		}
		if (this->GetType() == WoWObjectType::GameObject)
		{
			name = reinterpret_cast<const char* (__fastcall*)(CGObject*)>(Offsets::Base + Offsets::CGGameObject_C__GetName)(this);
		}
		else if (this->GetType() == WoWObjectType::Unit)
		{
			name = reinterpret_cast<const char* (__fastcall*)(CGObject*)>(Offsets::Base + Offsets::CGUnit_C__GetUnitNameExposed)(this);
		}
		else if (this->GetType() == WoWObjectType::Item)
		{
			name = "Item not implemented yet";
		}
		else if (this->GetType() == WoWObjectType::Player)
		{
			//This is tricky because i have not yet found how to parse players on different servers
			//( it crash when i pass them in the CGUnit_C__GetUnitNameExposed, but works if same server players )
		}
		else
		{
			name = "Not Implemented yet";
		}
		return name == nullptr ? "Unknown" : std::string(name);
	}

	Vector3 CGObject::GetPosition()
	{
		__try
		{
			if (this == nullptr) return Vector3();
			if (this->GetType() == WoWObjectType::Unit || this->GetType() == WoWObjectType::Player)
			{
				return *reinterpret_cast<Vector3*>(this + static_cast<uintptr_t>(Offsets::GameObject::UnitPosition));
			}
			else if (this->GetType() == WoWObjectType::GameObject)
			{
				return *reinterpret_cast<Vector3*>(this + static_cast<uintptr_t>(Offsets::GameObject::ObjectPosition));
			}
		}
		__except (1)
		{
			Console::PrintLn("Native Exception thrown at: const Native::CGObject::GetPosition() &");
		}
		return Vector3();
	}
}
