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

}