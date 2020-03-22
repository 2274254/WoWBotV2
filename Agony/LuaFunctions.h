#pragma once
#include <cstdint>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <tuple>
#include "Macros.h"
#include "WoWObject.h"

namespace Agony
{
    namespace Native
    {
        /*
        struct DLLEXPORT Caster {
            template<typename ...T>
            operator std::tuple<T...>()
            {
                constexpr auto size = std::tuple_size<std::tuple<T...>>::value;
                constexpr auto seq = std::make_index_sequence<size>{};
                return std::make_tuple(Get<T>(seq) ...);
            }

            template<typename R, size_t ... I>
            R Get(const std::index_sequence<I ...>&)
            {
                // make sure refs is long enough to have I
                // if not then error/throw?
                return R();// LuaGetReturn(L, refs[I])
            }

            std::vector<int> refs;
        };
        */
        class DLLEXPORT LuaFunctions
        {
        public:
            static WoWObject* GetUnitById(const char* unitid);
            static WoWObject* GetLocalPlayer();
            static WoWObject* GetTarget();
            static CorpseBase* GetCorpseBase();
            static void Execute(const char* com);
            static void Execute(const std::string& com);
            template<typename ...Args>
            static void Call(std::string const& functionName, Args&&... args);
            static std::string ExecuteGetResult(const std::string& com, const std::string& arg);
            static bool FramescriptRegister(const char* command, const int64_t funcPointer);
            static int64_t LuaSetTop(uintptr_t* l, const int32_t a2);
            static int64_t LuaGetTop(uintptr_t* l);
            static int64_t LuaGetField(uintptr_t* l, int idx, const char* k);
            static bool LuaIsNumber(uintptr_t* l, const int32_t stackPos);
            static double LuaToNumber(uintptr_t* l, const int32_t stackPos);
            static int64_t LuaPushInteger(uintptr_t* l, const int32_t theInteger);
            static int64_t LuaPushNumber(uintptr_t* l, const double theNumber);
            static int64_t LuaPushString(uintptr_t* l, const char* theString);
            static bool LuaIsString(uintptr_t* l, const int32_t stackPos);
            static const char* LuaToString(uintptr_t* l, const int32_t stackPos);
            static bool LuaPushBoolean(uintptr_t* l, const bool theBool);
            static int64_t LuaError(uintptr_t* l, const char* msg);
            static int64_t LuaCreateTable(uintptr_t* l, const int32_t narr, const int32_t nrec);
            static void LuaRawSeti(uintptr_t* l, const int32_t narr, const int32_t nrec);
            static int32_t LuaPCall(uintptr_t* l, const int32_t nargs, const int32_t nresults, const int32_t errfunc);
            static int32_t Unlock(uintptr_t* l);
            static int32_t GetUnitPosition(uintptr_t* l);
            static int32_t IsFacingTarget(uintptr_t* l);
            static int32_t CalculatePath(uintptr_t* l);
            static int32_t NextPoint(uintptr_t* l);
            static int32_t GoToPoint(uintptr_t* l);
            static int32_t WorldToScreen(uintptr_t* l);
            static int32_t DrawLine3D(uintptr_t* l);
            static int32_t GetCorpsePosition(uintptr_t* l);
            static int32_t GetPlayerAngle(uintptr_t* l);
            static int32_t IsInGame(uintptr_t* l);
            static std::map<const char*, int64_t> FunctionsMap;
        };
    }
}
