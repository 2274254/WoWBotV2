#include "CGUnit.h"
#include "Console.h"

std::string Agony::Native::CGUnit::GetName()
{
	if (this == nullptr)
	{
		return "Unknown";
	}
	return std::string(reinterpret_cast<const char* (__fastcall*)(CGUnit*)>(Offsets::Base + Offsets::CGUnit_C__GetUnitNameExposed)(this));
}

Vector3 Agony::Native::CGUnit::GetPosition()
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
