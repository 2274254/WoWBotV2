#pragma once
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#define SOL_ALL_SAFETIES_ON 1
#include "sol/sol.hpp"

class LuaGlobals
{
public:
    static std::unique_ptr<sol::state_view> MainEnvironment;
};