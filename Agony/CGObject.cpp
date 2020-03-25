#include "CGObject.h"
#include "Console.h"

namespace Agony::Native
{
	WoWObjectType CGObject::GetType()
	{
		__try
		{
			if (this == nullptr) return WoWObjectType::Invalid;
			return *reinterpret_cast<WoWObjectType*>(this + static_cast<int>(Offsets::GameObject::Type));
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
		return *reinterpret_cast<ObjectGuid*>(this + static_cast<int>(Offsets::GameObject::Guid));
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

		}
		else if (this->GetType() == WoWObjectType::Player)
		{

		}
		else
		{
			name = "Not Implemented yet";
		}
		return name == nullptr ? "Unknown" : std::string(name);
	}

	Vector3 CGObject::GetPosition()
	{
		/*__try
		{
			if (this == nullptr) return Vector3();
			return reinterpret_cast<Vector3(__fastcall*)(CGObject*)>(Offsets::Base + Offsets::CGGameObject_C__GetPosition)(this);
		}
		__except (1)
		{
			Console::PrintLn("Native Exception thrown at: const Native::CGObject::GetPosition() &");
		}*/
		return Vector3();
	}
}
