#pragma once
#include <Windows.h>

namespace Offsets
{
	//now just modify
	inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
	//WoW Lua
	inline uintptr_t InvalidFunctionPtr = 0x296B200;//GetTextEnd
	inline uintptr_t FrameScript_RegisterFunction = 0x51AA40;
	inline uintptr_t FrameScript_Execute = 0x519A70;
	inline uintptr_t FrameScript_GetText = 0x51D8F0;
	//Lua
	inline uintptr_t lua_gettop = 0x1DB700;
	inline uintptr_t lua_isnumber = 0x1DB9B0;
	inline uintptr_t lua_tonumber = 0x1DCCB0;
	inline uintptr_t lua_pushnumber = 0x1DBFA0;
	inline uintptr_t lua_pushinteger = 0x1DBEB0;
	inline uintptr_t lua_pushstring = 0x1DBFC0;
	inline uintptr_t lua_isstring = 0x1DB9E0;
	inline uintptr_t lua_tolstring = 0x1DCC10;
	inline uintptr_t lua_pushboolean = 0x1DBD10;
	inline uintptr_t lua_createtable = 0x1DB000;
	inline uintptr_t lua_rawseti = 0x1DC3E0;
	inline uintptr_t lua_pcall = 0x1DBC80;
	inline uintptr_t lua_settop = 0x1DC950;
	inline uintptr_t luaL_error = 0x19B9F00;
	inline uintptr_t lua_state = 0x29428A8;
	inline uintptr_t lua_getfield = 0x1DB5E0;

	//Game:
	inline uintptr_t GameVersion = 0x21A31BC;
	inline uintptr_t GetBaseFromToken = 0x16842E0;
	inline uintptr_t InGame = 0x2A73ADC;

	inline uintptr_t TerrainClick = 0xD99F80;
	inline uintptr_t CameraBase = 0x2A74A88;
	inline uintptr_t CorpseBase = 0x27CBDA8;
	inline uintptr_t ObjectMgr = 0x29DBED0;
	inline uintptr_t CGUnit_C__GetUnitNameExposed = 0xD7B960;

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