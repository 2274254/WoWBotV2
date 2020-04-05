#include "lualib.h"

int luaopen_base(lua_State* L)
{
	return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0x1998FF0))(L);
}

int luaopen_table (lua_State *L)
{
	return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0x1999E70))(L);
}

int luaopen_io (lua_State *L)
{
	return 0;//Removed by blizzard
}

int luaopen_os (lua_State *L)
{
	return 0;//Removed by blizzard
}

int luaopen_string (lua_State *L)
{
	return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0x199B410))(L);
}

int luaopen_math (lua_State *L)
{
	return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0x1997CE0))(L);
}

int luaopen_debug (lua_State *L)
{
	return 0;//Removed by blizzard
}

int luaopen_package (lua_State *L)
{
	return 0;//Removed by blizzard
}

void luaL_openlibs (lua_State *L)
{
	return;//Removed by blizzard
}