#pragma once
#include <Windows.h>

namespace Offsets
{
	//now just modify
	inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
	//WoW Lua
	inline uintptr_t InvalidFunctionPtr = 0x29551F0;
	inline uintptr_t FrameScript_RegisterFunction = 0x51D610;
	inline uintptr_t FrameScript_Execute = 0x51C640;
	inline uintptr_t FrameScript_GetText = 0x5204C0;
	//Lua
	inline uintptr_t lua_gettop = 0x1D82D0;
	inline uintptr_t lua_isnumber = 0x1D8580;
	inline uintptr_t lua_tonumber = 0x1D9880;
	inline uintptr_t lua_pushnumber = 0x1D8B70;
	inline uintptr_t lua_pushinteger = 0x1D8A80;
	inline uintptr_t lua_pushstring = 0x1D8B90;
	inline uintptr_t lua_isstring = 0x1D85B0;
	inline uintptr_t lua_tolstring = 0x1D97E0;
	inline uintptr_t lua_pushboolean = 0x1D88E0;
	inline uintptr_t lua_createtable = 0x1D7BD0;
	inline uintptr_t lua_rawseti = 0x1D8FB0;
	inline uintptr_t lua_pcall = 0x1D8850;
	inline uintptr_t lua_settop = 0x1D9520;
	inline uintptr_t luaL_error = 0x19A45A0;
	inline uintptr_t lua_state = 0x292C8A8;
	inline uintptr_t lua_getfield = 0x1D81B0;

	//Game:
	inline uintptr_t GameVersion = 0x207FF2C;
	inline uintptr_t GetBaseFromToken = 0x1670AE0;
	inline uintptr_t InGame = 0x2A5DAEC;

	inline uintptr_t TerrainClick = 0xD83ED0;
	inline uintptr_t CameraBase = 0x2A5EAA8;
	inline uintptr_t CorpseBase = 0x27B5DB8;
	inline uintptr_t ObjectMgr = 0x29C5ED0;
	inline uintptr_t CGUnit_C__GetUnitNameExposed = 0xD659B0;

	namespace GameObject
	{
		inline uintptr_t Type = 0x0010;
		inline uintptr_t Position = 0x0110;
		inline uintptr_t fAngle = 0x0120;
		inline uintptr_t UnitRace = 0x157C;
		inline uintptr_t UnitClass = 0x157D;
		inline uintptr_t CurrentHP = 0x1588;
		inline uintptr_t MaxHP = 0x1590;
		inline uintptr_t CurrentMana = 0x1788;
		inline uintptr_t MaxMana = 0x17A0;
		inline uintptr_t Strength = 0x1808;
		inline uintptr_t Agility = 0x180C;
		inline uintptr_t Stamina = 0x1810;
		inline uintptr_t Intellect = 0x1814;
		inline uintptr_t Spirit = 0x1818;
		inline uintptr_t BaseArmor = 0x1838;
		inline uintptr_t NegBuffArmor = 0x1854;
		inline uintptr_t Money = 0x3DD8;
		inline uintptr_t CurrentXP = 0x3DE0;
		inline uintptr_t MaxXP = 0x3DE4;
	}
}