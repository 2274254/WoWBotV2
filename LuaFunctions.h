#pragma once
#include <cstdint>
#include <string>
#include <cmath>
#include <map>

#include "Offsets.h"
#include "vector3.h"
#include "WoWObject.h"
#include "Navigation.h"
#include "Drawings.h"

inline WoWObject* GetUnitById(const char* unitid)
{
    return reinterpret_cast<WoWObject*(__fastcall*)(const char*)>(Offsets::Base + Offsets::GetBaseFromToken)(unitid);
}

inline WoWObject* GetLocalPlayer()
{
    return GetUnitById("player");
}

inline WoWObject* GetTarget()
{
    return GetUnitById("target");
}

inline CorpseBase* GetCorpseBase()
{
    return reinterpret_cast<CorpseBase*>(Offsets::Base + Offsets::CorpseBase);
}

inline void Execute(const char* com)
{
    reinterpret_cast<uintptr_t(__fastcall*)(const char*, const char*, int64_t)>(Offsets::Base + Offsets::FrameScriptExecute)(com, "KappaMorpher", 0);
}

inline void Execute(const std::string& com)
{
    Execute(com.c_str());
}

inline bool FramescriptRegister(const char* command, const int64_t funcPointer)
{
    const auto textSectionEnd = *reinterpret_cast<int64_t*>(Offsets::Base + Offsets::InvalidFunctionPtr);
    if (funcPointer >= textSectionEnd)
    {
        const auto dif = funcPointer - textSectionEnd;
        *reinterpret_cast<int64_t*>(Offsets::Base + Offsets::InvalidFunctionPtr) = textSectionEnd + dif + 1;
    }
    return reinterpret_cast<bool(__fastcall*)(const char*, int64_t)>(Offsets::Base + Offsets::FrameScriptRegister)(command, funcPointer);
}

inline int64_t LuaGetTop(uintptr_t* l)
{
    return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*)>(Offsets::Base + Offsets::GetTop)(l);
}

inline bool LuaIsNumber(uintptr_t* l, const int32_t stackPos)
{
    return reinterpret_cast<bool(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::IsNumber)(l, stackPos);
}

inline double LuaToNumber(uintptr_t* l, const int32_t stackPos)
{
    return reinterpret_cast<double(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::ToNumber)(l, stackPos);
}

inline int64_t LuaPushNumber(uintptr_t* l, const double theNumber)
{
    return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*, double)>(Offsets::Base + Offsets::PushNumber)(l, theNumber);
}

inline bool LuaIsString(uintptr_t* l, const int32_t stackPos)
{
    return reinterpret_cast<bool(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::IsString)(l, stackPos);
}

inline const char* LuaToString(uintptr_t* l, const int32_t stackPos)
{
    return reinterpret_cast<const char* (__fastcall*)(uintptr_t*, int32_t, uintptr_t*)>(Offsets::Base + Offsets::ToLString)(l, stackPos, nullptr);
}

inline bool LuaPushBoolean(uintptr_t* l, const bool theBool)
{
    return reinterpret_cast<bool(__fastcall*)(uintptr_t*, bool)>(Offsets::Base + Offsets::PushBoolean)(l, theBool);
}

inline int64_t LuaError(uintptr_t* l, const char* msg)
{
    return reinterpret_cast<int64_t(__cdecl*)(uintptr_t*, const char*)>(Offsets::Base + Offsets::Error)(l, msg);
}

inline int64_t LuaCreateTable(uintptr_t* l, const int32_t narr, const int32_t nrec)
{
    return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*, int32_t, int32_t)>(Offsets::Base + Offsets::lua_createtable)(l, narr, nrec);
}

inline void LuaRawSeti(uintptr_t* l, const int32_t narr, const int32_t nrec)
{
    reinterpret_cast<void(__fastcall*)(uintptr_t*, int32_t, int32_t)>(Offsets::Base + Offsets::lua_rawseti)(l, narr, nrec);
}


//do u know how to make a clua function? nope ;P do u know how lua stack works lol not at all i barely coded lua
//fuck

//Leave me those in case im lost :D

//the first param will be sent by wow when u call this function and its the lua_state pointer aka stack basically
int32_t Unlock(uintptr_t* l) //ok so ur return value here is how many returns ur lua function will return we aernt returning anything so will be 0
{
    //so to run protected function from addon we need to call execute in our dll so the first thing we need to do is get the number of arguments on the lua stack when this is called

    //num args sent to this command we expect 1 and we expect it to be a string 
    auto numArgs = LuaGetTop(l);

    //if we have 1 arg passed to function like we expect
    if (numArgs == 1)
    {
        //check if that arg is a string like we expect
        //if we have 1 arg then its pos on stack is 1
        if (LuaIsString(l, 1))
        {
            //if we are here the 1 arg on the stack is a string now we need to convert it to a string type for lua > c++
            auto s = LuaToString(l, 1);
            Execute(s);
            return 0;
        }
        LuaError(l, "Invalid Argument: string expected.");
    }
    LuaError(l, "Invalid # of Arguments: 1 expected.");
    return 0;
}

//another function so u know how to return results 
//lets make it add 2 user supplied numbers and return a string and the number
//so we know already we need 2 args passed to the function

int32_t GetUnitPosition(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);

    if (numArgs == 1)
    {
        if (LuaIsString(l, 1))
        {
            auto unitId = LuaToString(l, 1);
            auto unit = GetUnitById(unitId);
            if (unit == nullptr)
            {
                LuaPushNumber(l, 0);
                LuaPushNumber(l, 0);
                LuaPushNumber(l, 0);
            }
            else
            {
                LuaPushNumber(l, unit->pos.y);
                LuaPushNumber(l, unit->pos.x);
                LuaPushNumber(l, unit->pos.z);
            }
            return 3;
        }
        LuaError(l, "Invalid Argument: string expected.");
        //err die
        return 0;
    }
    LuaError(l, "Invalid # of Arguments: 1 expected.");
    return 0;
}

int32_t IsFacingTarget(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);

    if (numArgs == 0)
    {
        auto player = GetLocalPlayer();
        auto target = GetTarget();
        if (target == nullptr)
        {

            auto Object1Facing = player->fAngle;

            auto Angle = ((player->pos.x - target->pos.x) * std::cos(-Object1Facing)) - ((player->pos.y - target->pos.y) * std::sin(-Object1Facing));
            bool isFacing = Angle < 0;
            LuaPushBoolean(l, isFacing);
        }
        else
        {
            LuaPushBoolean(l, false);
        }
        //err die
        return 1;
    }
    return 0;
}

int32_t CalculatePath(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);
    if (numArgs == 4)
    {
        if (LuaIsNumber(l, 1) && LuaIsNumber(l, 2) && LuaIsNumber(l, 3) && LuaIsNumber(l, 4))
        {
            auto player = GetLocalPlayer();

            Navigation* navigation = Navigation::GetInstance();

            Vector3 start = Vector3(player->pos.x, player->pos.y, player->pos.z);
            Vector3 end = Vector3(LuaToNumber(l, 1), LuaToNumber(l, 2), LuaToNumber(l, 3));

            //XYZ start = XYZ(-8949.95f, -132.493f, 83.5312f);
            //XYZ end = XYZ(-9046.507f, -45.71962f, 88.33186f);

            int instanceId = LuaToNumber(l, 4);
            Navigation::GetInstance()->Initialize(instanceId);

            if (Drawings::Waypoints)
            {
                Navigation::GetInstance()->FreePathArr(Drawings::Waypoints);
            }
            Drawings::CurrentWaypoint = 0;
            Drawings::Waypoints = Navigation::GetInstance()->CalculatePath(instanceId, start, end, false, &Drawings::WaypointsLenght, false);
            LuaCreateTable(l, Drawings::WaypointsLenght, 0);
            for (int i = 0; i < Drawings::WaypointsLenght; i++)
            {
                LuaCreateTable(l, 3, 0);
                LuaPushNumber(l, Drawings::Waypoints[i].x);
                LuaRawSeti(l, -2, 1);
                LuaPushNumber(l, Drawings::Waypoints[i].y);
                LuaRawSeti(l, -2, 2);
                LuaPushNumber(l, Drawings::Waypoints[i].z);
                LuaRawSeti(l, -2, 3);
                LuaRawSeti(l, -2, i + 1);
            }
            return 1;
        }
        return 0;
    }
    //
}

int32_t NextPoint(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);
    if (numArgs == 0)
    {
        Drawings::CurrentWaypoint++;
        if (Drawings::CurrentWaypoint == Drawings::WaypointsLenght) Drawings::CurrentWaypoint = Drawings::WaypointsLenght - 1;
        return 0;
    }
    //
}

int32_t GoToPoint(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);
    if (numArgs == 3)
    {
        if (LuaIsNumber(l, 1) && LuaIsNumber(l, 2) && LuaIsNumber(l, 3))
        {
            auto player = GetLocalPlayer();
            Vector3 point = Vector3(LuaToNumber(l, 1), LuaToNumber(l, 2), LuaToNumber(l, 3));
            reinterpret_cast<void(__fastcall*)(WoWObject*, Vector3*)>(Offsets::Base + Offsets::TerrainClick)(player, &point);//same shit XD
            return 0;
        }
        return 0;
    }
    //
}

int32_t WorldToScreen(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);
    if (numArgs == 3)
    {
        if (LuaIsNumber(l, 1) && LuaIsNumber(l, 2) && LuaIsNumber(l, 3))
        {
            Vector3 point = Vector3(LuaToNumber(l, 1), LuaToNumber(l, 2), LuaToNumber(l, 3));
            auto screenPos = Drawings::WorldToScreen(point);

            LuaPushNumber(l, screenPos.x);
            LuaPushNumber(l, screenPos.y);

            return 2;
        }
        return 0;
    }
    //
}

int32_t DrawLine3D(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);
    if (numArgs == 6)
    {
        if (LuaIsNumber(l, 1) && LuaIsNumber(l, 2) && LuaIsNumber(l, 3) && LuaIsNumber(l, 4) && LuaIsNumber(l, 5) && LuaIsNumber(l, 6))
        {
            Vector3 from = Vector3(LuaToNumber(l, 1), LuaToNumber(l, 2), LuaToNumber(l, 3));
            Vector3 to = Vector3(LuaToNumber(l, 4), LuaToNumber(l, 5), LuaToNumber(l, 6));

            Drawings::DrawLine(from, to);

            return 0;
        }
        return 0;
    }
    //
}

int32_t GetCorpsePosition(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);
    if (numArgs == 0)
    {
        auto corpseBase = GetCorpseBase();
        if (corpseBase == nullptr)
        {
            LuaPushNumber(l, 0);
            LuaPushNumber(l, 0);
            LuaPushNumber(l, 0);
        }
        else
        {
            LuaPushNumber(l, corpseBase->pos.x);
            LuaPushNumber(l, corpseBase->pos.y);
            LuaPushNumber(l, corpseBase->pos.z);
        }
        return 3;
    }
    return 0;
}

int32_t GetPlayerAngle(uintptr_t* l)
{
    auto numArgs = LuaGetTop(l);
    if (numArgs == 0)
    {
        auto player = GetLocalPlayer();
        LuaPushNumber(l, player->fAngle);
        return 1;
    }
    return 0;
}

inline std::map<const char*, int64_t> FunctionsMap
{
    {"Unlock", reinterpret_cast<int64_t>(Unlock)},
    {"GetUnitPosition", reinterpret_cast<int64_t>(GetUnitPosition)},
    {"IsFacingTarget", reinterpret_cast<int64_t>(IsFacingTarget)},
    {"CalculatePath", reinterpret_cast<int64_t>(CalculatePath)},
    {"GoToPoint", reinterpret_cast<int64_t>(GoToPoint)},
    {"WorldToScreen", reinterpret_cast<int64_t>(WorldToScreen)},
    {"DrawLine3D", reinterpret_cast<int64_t>(DrawLine3D)},
    {"GetCorpsePosition", reinterpret_cast<int64_t>(GetCorpsePosition)},
    {"GetPlayerAngle", reinterpret_cast<int64_t>(GetPlayerAngle)},
    {"NextPoint", reinterpret_cast<int64_t>(NextPoint)}
};
