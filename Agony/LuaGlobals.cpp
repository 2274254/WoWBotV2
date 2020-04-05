#include "LuaGlobals.h"

std::unique_ptr<sol::state_view> LuaGlobals::MainEnvironment = nullptr;