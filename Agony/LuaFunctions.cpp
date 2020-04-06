#include "LuaFunctions.h"
#include "vector3.h"
#include "Navigation.h"
#include "Drawings.h"
#include "ObjectManager.h"
#include "Game.h"
#include "LuaGlobals.h"
#include <tuple>

namespace Agony
{
    namespace Native
    {
        std::map<const char*, int64_t> LuaFunctions::FunctionsMap =
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
            {"NextPoint", reinterpret_cast<int64_t>(NextPoint)},
            {"IsInGame", reinterpret_cast<int64_t>(IsInGame)},
            {"Test", reinterpret_cast<int64_t>(Test)}
        };

        WoWObject* LuaFunctions::GetUnitById(const char* unitid)
        {
            return reinterpret_cast<WoWObject * (__fastcall*)(const char*)>(Offsets::Base + Offsets::GetBaseFromToken)(unitid);
        }

        WoWObject* LuaFunctions::GetLocalPlayer()
        {
            return GetUnitById("player");
        }

        WoWObject* LuaFunctions::GetTarget()
        {
            return GetUnitById("target");
        }

        void LuaFunctions::Execute(const char* com)
        {
            reinterpret_cast<uintptr_t(__fastcall*)(const char*, const char*, int64_t)>(Offsets::Base + Offsets::FrameScript_Execute)(com, "KappaMorpher", 0);
        }

        void LuaFunctions::Execute(const std::string& com)
        {
            Execute(com.c_str());
        }

        std::string LuaFunctions::ExecuteGetResult(const std::string& com, const std::string& arg)
        {
            reinterpret_cast<uintptr_t(__fastcall*)(const char*, const char*, int64_t)>(Offsets::Base + Offsets::FrameScript_Execute)(com.c_str(), "KappaMorpher", 0);
            return std::string(reinterpret_cast<const char*>(reinterpret_cast<uintptr_t(__fastcall*)(const char*, int64_t, int32_t, uint8_t)>(Offsets::Base + Offsets::FrameScript_GetText)(arg.c_str(), -1, 0, 0)));
        }

        bool LuaFunctions::FramescriptRegister(const char* command, const int64_t funcPointer)
        {
            const auto textSectionEnd = *reinterpret_cast<int64_t*>(Offsets::Base + Offsets::InvalidFunctionPtr);
            if (funcPointer >= textSectionEnd)
            {
                const auto dif = funcPointer - textSectionEnd;
                *reinterpret_cast<int64_t*>(Offsets::Base + Offsets::InvalidFunctionPtr) = textSectionEnd + dif + 1;
            }
            return reinterpret_cast<bool(__fastcall*)(const char*, int64_t)>(Offsets::Base + Offsets::FrameScript_RegisterFunction)(command, funcPointer);
        }

        int64_t LuaFunctions::LuaSetTop(uintptr_t* l, const int32_t a2)
        {
            return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::lua_settop)(l, a2);
        }

        int64_t LuaFunctions::LuaGetTop(uintptr_t* l)
        {
            return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*)>(Offsets::Base + Offsets::lua_gettop)(l);
        }

        int64_t LuaFunctions::LuaGetField(uintptr_t* l, int idx, const char* k)
        {
            return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*, int idx, const char* k)>(Offsets::Base + Offsets::lua_getfield)(l, idx, k);
        }

        bool LuaFunctions::LuaIsNumber(uintptr_t* l, const int32_t stackPos)
        {
            return reinterpret_cast<bool(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::lua_isnumber)(l, stackPos);
        }

        double LuaFunctions::LuaToNumber(uintptr_t* l, const int32_t stackPos)
        {
            return reinterpret_cast<double(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::lua_tonumber)(l, stackPos);
        }

        int64_t LuaFunctions::LuaPushInteger(uintptr_t* l, const int32_t theInteger)
        {
            return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::lua_pushinteger)(l, theInteger);
        }

        int64_t LuaFunctions::LuaPushNumber(uintptr_t* l, const double theNumber)
        {
            return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*, double)>(Offsets::Base + Offsets::lua_pushnumber)(l, theNumber);
        }

        int64_t LuaFunctions::LuaPushString(uintptr_t* l, const char* theString)
        {
            return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*, const char*)>(Offsets::Base + Offsets::lua_pushstring)(l, theString);
        }

        bool LuaFunctions::LuaIsString(uintptr_t* l, const int32_t stackPos)
        {
            return reinterpret_cast<bool(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::lua_isstring)(l, stackPos);
        }

        const char* LuaFunctions::LuaToString(uintptr_t* l, const int32_t stackPos)
        {
            return reinterpret_cast<const char* (__fastcall*)(uintptr_t*, int32_t, uintptr_t*)>(Offsets::Base + Offsets::lua_tolstring)(l, stackPos, nullptr);
        }

        bool LuaFunctions::LuaPushBoolean(uintptr_t* l, const bool theBool)
        {
            return reinterpret_cast<bool(__fastcall*)(uintptr_t*, bool)>(Offsets::Base + Offsets::lua_pushboolean)(l, theBool);
        }

        int64_t LuaFunctions::LuaError(uintptr_t* l, const char* msg)
        {
            return reinterpret_cast<int64_t(__cdecl*)(uintptr_t*, const char*)>(Offsets::Base + Offsets::luaL_error)(l, msg);
        }

        int64_t LuaFunctions::LuaCreateTable(uintptr_t* l, const int32_t narr, const int32_t nrec)
        {
            return reinterpret_cast<int64_t(__fastcall*)(uintptr_t*, int32_t, int32_t)>(Offsets::Base + Offsets::lua_createtable)(l, narr, nrec);
        }

        void LuaFunctions::LuaRawSeti(uintptr_t* l, const int32_t narr, const int32_t nrec)
        {
            reinterpret_cast<void(__fastcall*)(uintptr_t*, int32_t, int32_t)>(Offsets::Base + Offsets::lua_rawseti)(l, narr, nrec);
        }

        int32_t LuaFunctions::LuaPCall(uintptr_t* l, const int32_t nargs, const int32_t nresults, const int32_t errfunc)
        {
            return reinterpret_cast<int32_t(__fastcall*)(uintptr_t*, int32_t, int32_t, int32_t)>(Offsets::Base + Offsets::lua_pcall)(l, nargs, nresults, errfunc);
        }

        //the first param will be sent by wow when u call this function and its the lua_state pointer aka stack basically
        int32_t LuaFunctions::Unlock(uintptr_t* l) //ok so ur return value here is how many returns ur lua function will return we aernt returning anything so will be 0
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
                    const auto currentState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
                    if ((currentState >> 4) & 1)
                    {
                        //if we are here the 1 arg on the stack is a string now we need to convert it to a string type for lua > c++
                        auto s = LuaToString(l, 1);
                        Execute(s);
                    }
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

        int32_t LuaFunctions::GetUnitPosition(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);

            if (numArgs == 1)
            {
                if (LuaIsString(l, 1))
                {
                    const auto currentState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
                    if ((currentState >> 4) & 1)
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
                    }
                    else
                    {
                        LuaPushNumber(l, 0);
                        LuaPushNumber(l, 0);
                        LuaPushNumber(l, 0);
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

        int32_t LuaFunctions::IsFacingTarget(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);

            if (numArgs == 0)
            {
                auto player = GetLocalPlayer();
                auto target = GetTarget();
                if (target == nullptr)
                {
                    const auto currentState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
                    if ((currentState >> 4) & 1)
                    {
                        auto Object1Facing = player->fAngle;

                        auto Angle = ((player->pos.x - target->pos.x) * std::cos(-Object1Facing)) - ((player->pos.y - target->pos.y) * std::sin(-Object1Facing));
                        bool isFacing = Angle < 0;
                        LuaPushBoolean(l, isFacing);
                    }
                    else
                    {
                        LuaPushBoolean(l, true);
                    }
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

        int32_t LuaFunctions::CalculatePath(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);
            if (numArgs == 4)
            {
                if (LuaIsNumber(l, 1) && LuaIsNumber(l, 2) && LuaIsNumber(l, 3) && LuaIsNumber(l, 4))
                {
                    const auto currentState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
                    if ((currentState >> 4) & 1)
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
                    else
                    {
                        if (Drawings::Waypoints)
                        {
                            Navigation::GetInstance()->FreePathArr(Drawings::Waypoints);
                        }
                        Drawings::Waypoints = new Vector3[0];
                        Drawings::WaypointsLenght = 0;
                        LuaCreateTable(l, Drawings::WaypointsLenght, 0);
                        return 1;
                    }
                }
                else
                {
                    if (Drawings::Waypoints)
                    {
                        Navigation::GetInstance()->FreePathArr(Drawings::Waypoints);
                    }
                    Drawings::Waypoints = new Vector3[0];
                    Drawings::WaypointsLenght = 0;
                    LuaCreateTable(l, Drawings::WaypointsLenght, 0);
                    return 1;
                }
            }
            return 0;
        }

        int32_t LuaFunctions::NextPoint(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);
            if (numArgs == 0)
            {
                Drawings::CurrentWaypoint++;
                if (Drawings::CurrentWaypoint == Drawings::WaypointsLenght) Drawings::CurrentWaypoint = Drawings::WaypointsLenght - 1;
            }
            return 0;
        }

        int32_t LuaFunctions::GoToPoint(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);
            if (numArgs == 3)
            {
                if (LuaIsNumber(l, 1) && LuaIsNumber(l, 2) && LuaIsNumber(l, 3))
                {
                    const auto currentState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
                    if ((currentState >> 4) & 1)
                    {
                        auto player = GetLocalPlayer();
                        Vector3 point = Vector3(LuaToNumber(l, 1), LuaToNumber(l, 2), LuaToNumber(l, 3));
                        reinterpret_cast<void(__fastcall*)(WoWObject*, Vector3*)>(Offsets::Base + Offsets::TerrainClick)(player, &point);//same shit XD
                    }
                }
            }
            return 0;
        }

        int32_t LuaFunctions::WorldToScreen(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);
            if (numArgs == 3)
            {
                if (LuaIsNumber(l, 1) && LuaIsNumber(l, 2) && LuaIsNumber(l, 3))
                {
                    Vector2 screenLoc;
                    if (Drawings::WorldToScreen(Vector3(LuaToNumber(l, 1), LuaToNumber(l, 2), LuaToNumber(l, 3)), &screenLoc))
                    {
                        LuaPushNumber(l, screenLoc.x);
                        LuaPushNumber(l, screenLoc.y);
                    }
                    else
                    {
                        LuaPushNumber(l, 0);
                        LuaPushNumber(l, 0);
                    }
                    //auto screenPos = Drawings::WorldToScreen(point);
                    return 2;
                }
                return 0;
            }
            //
        }

        int32_t LuaFunctions::DrawLine3D(uintptr_t* l)
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

        int32_t LuaFunctions::GetCorpsePosition(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);
            if (numArgs == 0)
            {
                auto corpseBase = reinterpret_cast<CorpseBase*>(Offsets::Base + Offsets::CorpseBase);
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

        int32_t LuaFunctions::GetPlayerAngle(uintptr_t* l)
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

        int32_t LuaFunctions::IsInGame(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);
            if (numArgs == 0)
            {
                const auto currentState = *reinterpret_cast<unsigned __int16*>(Offsets::Base + Offsets::InGame);
                LuaPushBoolean(l, (currentState >> 4) & 1);
                return 1;
            }
            return 0;
        }

        int32_t LuaFunctions::Test(uintptr_t* l)
        {
            auto numArgs = LuaGetTop(l);
            if (numArgs == 0)
            {
                //auto player = Agony::Native::Game::Me();
                //uintptr_t* L = *(uintptr_t**)(Offsets::Base + Offsets::lua_state);
                //auto v4 = 0;// reinterpret_cast<uintptr_t* (__thiscall*)(void*)>(Offsets::Base + 0xD08BE0)(L);
                //auto result = LuaFunctions::Call("GetProfessionInfo", {2, 2, 1, 1, 1, 1, 1, 1, 1, 1}, 5);
                //std::cout << "v4 = " << std::dec << std::any_cast<int>(result[2]) << "/" << std::any_cast<int>(result[3]) << std::endl;

                auto result = LuaFunctions::Call("UnitHealth", {1}, "player");
                std::cout << "Test = " << std::dec << std::any_cast<int>(result[0]) << std::endl;



                /*ObjectGuid* guid2 = reinterpret_cast<ObjectGuid*>(Offsets::Base + Offsets::CGGameUI__m_currentObjectTrack);
                if (guid2 != nullptr && !(guid2->HiWord == 0 && guid2->LoWord))
                {
                    //std::cout << "guid1 type " << std::dec << guid1.Type()  << std::endl;
                    std::cout << "guid2 type " << std::dec << guid2->Type() << std::endl;

                    auto obj = ObjectManager::GetObjectFromGuid(guid2);
                    if (obj != nullptr)
                    {
                        std::cout << "Obj address 0x" << std::hex << obj << std::endl;
                        if (obj->GetType() == WoWObjectType::Unit)
                        {
                            std::cout << obj->GetName() << std::endl;
                        }
                        else if (obj->GetType() == WoWObjectType::GameObject)
                        {
                            std::cout << obj->GetName() << std::endl;
                            //This even check if it is called from Unlock or not : this one?
                            reinterpret_cast<bool(__fastcall*)(ObjectGuid*)>(Offsets::Base + Offsets::CGGameUI__OnSpriteRightClick)(&obj->GetGuid());
                        }
                    }
                }*/
                /*THIS ALSO WORKS:
                auto gameObjects = ObjectManager::GetVisibleObjects();
                for (std::size_t i = 0; i < gameObjects.size(); ++i)
                {
                    auto gameObject = gameObjects[i];
                    if (gameObject->GetType() == WoWObjectType::GameObject)
                    {
                        //std::cout << gameObject->GetName() << std::endl;
                        reinterpret_cast<bool(__fastcall*)(ObjectGuid*)>(Offsets::Base + Offsets::CGGameUI__OnSpriteRightClick)(&gameObject->GetGuid());
                    }
                }*/
            }
            return 0;
        }
        
        void LuaFunctions::OnGossipShow()
        {
            std::cout << "TRIGGER ON GOSSIP SHOW Using EventCallback\n";
        }

        void LuaFunctions::OnCinematicStart(bool canCancel)
        {
            std::cout << "OnCinematicStart\n";
        }

        void LuaFunctions::OnCinematicStop()
        {
            std::cout << "TRIGGER ON CinematicStop\n";
        }

        void LuaFunctions::OnPlayerStartedMoving()
        {
            std::cout << "TRIGGER On PlayerStartedMoving\n";
        }

        void LuaFunctions::OnPlayerStoppedMoving()
        {
            std::cout << "TRIGGER On PlayerStoppedMoving\n";
        }

        const char* LuaFunctions::GetMainScriptCode()
        {
            int32_t dummy = 0;
            #include "main.lua"//really that will execute lua ?
        }

        inline void PrintLuaResults(const sol::variadic_results& results)
        {
            for (const auto& result : results)
            {
                switch (result.get_type())
                {
                    case sol::type::nil:
                    {
                        std::cout << "nil\n";
                        break;
                    }
                    case sol::type::function:
                    {
                        std::cout << "function: 0x" << std::hex << result.as<uintptr_t>() << "\n";
                        break;
                    }
                    case sol::type::string:
                    {
                        std::cout << result.as<std::string>() << "\n";
                        break;
                    }
                    case sol::type::number:
                    {
                        std::cout << std::to_string(result.as<double>()) << "\n";
                        break;
                    }
                    case sol::type::boolean:
                    {
                        std::cout << (result.as<bool>() ? "true" : "false") << "\n";
                        break;
                    }
                    case sol::type::table:
                    {
                        std::cout << "table: 0x" << std::hex << result.as<uintptr_t>() << "\n";
                        break;
                    }
                    case sol::type::userdata:
                    {
                        std::cout << "userdata: 0x" << std::hex << result.as<uintptr_t>() << "\n";
                        break;
                    }
                    default:
                    {
                        std::cout << "Type value is either unknown or doesn't matter\n";
                        break;
                    }
                }
            }
        }

        //create var to bind only once later
        void LuaFunctions::SolTest() 
        {
            const auto l = *reinterpret_cast<lua_State**>(Offsets::Base + Offsets::lua_state);

            if (LuaGlobals::MainEnvironment == nullptr) //need to set a bool instead here
            {
                const auto l = *reinterpret_cast<lua_State**>(Offsets::Base + Offsets::lua_state);
                LuaGlobals::MainEnvironment = std::make_unique<sol::state_view>(l);
                auto& lua = *LuaGlobals::MainEnvironment;

                lua.new_usertype<void>("AgonyLuaEvents",
                    //"new", sol::no_constructor,
                    "OnEvent", [](const sol::variadic_args& results)
                    {
                        std::string eventName;
                        std::vector<std::any> args = std::vector<std::any>();
                        int i = 0;
                        for (const auto& result : results)
                        {
                            switch (result.get_type())
                            {
                                case sol::type::nil:
                                {
                                    args.push_back(nullptr);
                                    break;
                                }
                                case sol::type::function:
                                {
                                    args.push_back(result.as<uintptr_t>());
                                    break;
                                }
                                case sol::type::string:
                                {
                                    if (i == 0)
                                    {
                                        eventName = result.as<std::string>();
                                    }
                                    else
                                    {
                                        args.push_back(result.as<std::string>());
                                    }
                                    break;
                                }
                                case sol::type::number:
                                {
                                    args.push_back(result.as<double>());
                                    break;
                                }
                                case sol::type::boolean:
                                {
                                    args.push_back(result.as<bool>());
                                    break;
                                }
                                case sol::type::table:
                                {
                                    args.push_back(result.as<uintptr_t>());
                                    break;
                                }
                                case sol::type::userdata:
                                {
                                    args.push_back(result.as<uintptr_t>());
                                    break;
                                }
                                default:
                                {
                                    std::cout << "Type value is either unknown or doesn't matter\n";
                                    break;
                                }
                            }
                            i++;
                        }
                        Game::GetInstance()->OnLuaEvent.Trigger(eventName, args);
                    }
                );

                //
                std::cout << "Finished binding functions.\n";
            }

            std::cout << GetMainScriptCode() << "\n";

            auto& lua = *LuaGlobals::MainEnvironment;
            //thats basically it SEE IF WORKS
            const auto badCodeResult = lua.safe_script(
                GetMainScriptCode(),
                [](lua_State*, const sol::protected_function_result& pfr)
                {
                    const auto errObj = pfr.get<sol::error>();
                    const auto errMsg = errObj.what();
                    std::cout << errMsg << "\n";
                    return pfr;
                }
            );
            //////ok now u can call lua anywhere but we do here for example
            //////let start simple unithealth
            //int health = lua["UnitHealth"]("player");
            //std::cout << "Player health = " << health << std::endl;

            //try
            //{
            //    sol::variadic_results result2 = lua["GetBattlefieldStatus"](1);//Guess it will work
            //    PrintLuaResults(result2);
            //    /*for (auto arg : result2)
            //    {
            //        if (arg.valid())
            //        {
            //            if (arg.is<std::string>())
            //                std::cout << "Got arg: " << arg.as<std::string>() << std::endl;
            //            else if (arg.is<float>())
            //                std::cout << "Got arg: " << arg.as<float>() << std::endl;
            //            else if (arg.is<int>())
            //                std::cout << "Got arg: " << arg.as<int>() << std::endl;
            //            else if (arg.is<bool>())
            //                std::cout << "Got arg: " << arg.as<bool>() << std::endl;
            //        }
            //    }*/
            //    /*if (result2.size() == 8)
            //    {
            //        std::cout << "status: " << result2.at(0).as<std::string>() << " mapName:  " << result2.at(1).as<std::string>() << std::endl;
            //    }*/
            //}
            //catch (...) {}
        }
    }
}