#pragma once
#include <Windows.h>

namespace Offsets
{
	//now just modify
	inline uintptr_t Base = reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
	//WoW Lua
	inline uintptr_t InvalidFunctionPtr = 0x294B240;//GetTextEnd
	inline uintptr_t FrameScript_RegisterFunction = 0x513310;
	inline uintptr_t FrameScript_Execute = 0x512340;
	inline uintptr_t FrameScript_GetText = 0x5161C0;
	//Lua
	inline uintptr_t lua_gettop = 0x1D0390;
	inline uintptr_t lua_isnumber = 0x1D0640;
	inline uintptr_t lua_tonumber = 0x1D1940;
	inline uintptr_t lua_pushnumber = 0x1D0C30;
	inline uintptr_t lua_pushinteger = 0x1D0B40;
	inline uintptr_t lua_pushstring = 0x1D0C50;
	inline uintptr_t lua_isstring = 0x1D0670;
	inline uintptr_t lua_tolstring = 0x1D18A0;
	inline uintptr_t lua_pushboolean = 0x1D09A0;
	inline uintptr_t lua_createtable = 0x1CFC90;
	inline uintptr_t lua_rawseti = 0x1D1070;
	inline uintptr_t lua_pcall = 0x1D0910;
	inline uintptr_t lua_settop = 0x1D15E0;
	inline uintptr_t luaL_error = 0x1995B10;
	inline uintptr_t lua_state = 0x29228E8;
	inline uintptr_t lua_getfield = 0x1D0270;

	//Game:
	inline uintptr_t GetBaseFromToken = 0x16634C0;
	inline uintptr_t InGame = 0x2A53B6C;

	inline uintptr_t TerrainClick = 0xD79960;
	inline uintptr_t CameraBase = 0x2A54B18;
	inline uintptr_t CorpseBase = 0x27ABDD8;
	inline uintptr_t ObjectMgr = 0x29BBF30;
	inline uintptr_t ClntObjMgrObjectPtr = 0xFBC440;//TODO
	inline uintptr_t CGGameObject_C__GetName = 0xDF4310;
	inline uintptr_t CGUnit_C__GetUnitNameExposed = 0xD5B480;
	inline uintptr_t CGUnit_C__CanAttack = 0xD628A0;
	inline uintptr_t Script_GetGUIDFromToken = 0x1662140;
	inline uintptr_t CGGameUI__OnSpriteRightClick = 0x1170940;
	inline uintptr_t CGGameUI__ClosestObjectMatch = 0x115C920;
	inline uintptr_t CGGameUI__m_currentObjectTrack = 0x2A53B70;//(Mouse over object)
	inline uintptr_t FrameTime__GetCurTimeMs = 0x49FAA0;
	inline uintptr_t CGBag_C__GetItemPointer = 0xED2E30;

	namespace GameObject
	{
		namespace MovementInfos
		{
			inline uintptr_t CurrentSpeed = 0xA4;
			inline uintptr_t RunSpeed = 0xAC;
			inline uintptr_t FlightSpeed = 0xBC;
			inline uintptr_t SwimSpeed = 0xB4;
		}
		inline uintptr_t Type = 0x0010;
		inline uintptr_t Guid = 0x0040;
		inline uintptr_t MovementInfo = 0x00B0;
		inline uintptr_t ObjectPosition = 0x00C8;
		inline uintptr_t VehiculeGuid = 0x0100;
		inline uintptr_t UnitPosition = 0x0110;
		inline uintptr_t fAngle = 0x0120;

		inline uintptr_t CastSpellID = 0x04F0;//Found inside UnitChannelInfo
		inline uintptr_t CastSpellStartTimeMS = 0x04F8;
		inline uintptr_t CastSpellEndTimeMS = 0x04FC;

		inline uintptr_t UnitRace = 0x157C;
		inline uintptr_t UnitClass = 0x157D;
		inline uintptr_t CurrentHP = 0x1588;
		inline uintptr_t MaxHP = 0x1590;

		inline uintptr_t AffectingCombat = 0x15C0;//This is some flag enum, i dont know yet what it is... but we can know if unit is in combat or has aggro with that using ( (*(_DWORD *)(wowObj + 0x15C0) >> 19) & 1 )
		inline uintptr_t IsDeadFlag = 0x15C8;
		inline uintptr_t IsGhostFlag = 0x1AB8;

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