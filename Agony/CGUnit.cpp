#include "CGUnit.h"

std::string Agony::Native::CGUnit::GetName()
{
	if (this == nullptr)
	{
		return "Unknown";
	}
	return reinterpret_cast<const char* (__fastcall*)(CGUnit*)>(Offsets::Base + Offsets::CGUnit_C__GetUnitNameExposed)(this);
}
