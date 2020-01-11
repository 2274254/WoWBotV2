#pragma once
#include <Windows.h>

namespace Offsets
{
	//now just modify
	inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
	//WoW Lua
	inline uintptr_t InvalidFunctionPtr = 0x28291D0; //48 8b 05 ? ? ? ? 48 85 d2 74
	inline uintptr_t FrameScriptRegister = 0x5394C0;
	inline uintptr_t FrameScriptExecute = 0x5384F0;
	inline uintptr_t FrameScriptGetText = 0x0;
	//Lua
	inline uintptr_t GetTop = 0x2003C0;
	inline uintptr_t IsNumber = 0x200670;
	inline uintptr_t ToNumber = 0x201970;
	inline uintptr_t PushNumber = 0x200C60;
	inline uintptr_t IsString = 0x2006A0;
	inline uintptr_t ToLString = 0x2018D0;
	inline uintptr_t PushBoolean = 0x2009D0;
	inline uintptr_t lua_createtable = 0x1FFCC0;
	inline uintptr_t lua_rawseti = 0x2010A0;
	inline uintptr_t Error = 0x1904770; //LuaL_error

	//Game:
	inline uintptr_t GameVersion = 0x206FEFC;
	inline uintptr_t GetBaseFromToken = 0x15D7CC0;
	inline uintptr_t InGame = 0x292F7B4;
	inline uintptr_t TerrainClick = 0xD11760;
	inline uintptr_t CameraBase = 0x2930758;
	inline uintptr_t CorpseBase = 0x267CA48;

}