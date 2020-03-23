#pragma once
#include <cstdint>
#include <iostream>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <tuple>
#include <any>
#include "Macros.h"
#include "Offsets.h"
#include "WoWObject.h"

struct any {
    enum type { Int, Float, String, Boolean, Double };
    any(int   e) { m_data.INT = e; m_type = Int; }
    any(float e) { m_data.FLOAT = e; m_type = Float; }
    any(const char* e) { m_data.STRING = e; m_type = String; }
    any(bool e) { m_data.BOOLEAN = e; m_type = Boolean; }
    any(double e) { m_data.DOUBLE = e; m_type = Double; }
    type get_type() const { return m_type; }
    int get_int() const { return m_data.INT; }
    float get_float() const { return m_data.FLOAT; }
    const char* get_string() const { return m_data.STRING; }
    bool get_bool() const { return m_data.BOOLEAN; }
    double get_double() const { return m_data.DOUBLE; }
private:
    type m_type;
    union {
        int   INT;
        float FLOAT;
        const char* STRING;
        bool BOOLEAN;
        double DOUBLE;
    } m_data;
};

namespace Agony
{
    namespace Native
    {
        /*template <class ...Args>
        void LuaFunctions::Call(const char* functionName, Args... values)
        {
            return LuaFunctions::internal_Call(std::string functionName, const Args &... args);
        }*/
        class DLLEXPORT LuaFunctions
        {
            #define LUA_GLOBALSINDEX        (-10002)
            #define lua_pop(L,n)            LuaFunctions::LuaSetTop(L, -(n)-1)
            #define lua_getglobal(L,s)      LuaFunctions::LuaGetField(L, LUA_GLOBALSINDEX, (s))
            template <class ...Args>
            static std::vector<std::any> internal_Call(std::string const& functionName, std::vector<int> returns, const Args&... args)
            {
                std::vector<std::any> returnValues;
                uintptr_t* L = *(uintptr_t**)(Offsets::Base + Offsets::lua_state);
                lua_getglobal(L, functionName.c_str());
                int argsSize = sizeof...(Args);
                any vec[sizeof...(Args)] = { args... };
                int argsc = 0;
                for (unsigned i = 0; i < argsSize; ++i)
                {
                    switch (vec[i].get_type())
                    {
                        case any::Int:
                        {
                            LuaPushInteger(L, vec[i].get_int());
                            argsc++;
                        }
                        break;
                        case any::Float:
                        {
                            LuaPushNumber(L, (double)vec[i].get_float());
                            argsc++;
                        }
                        break;
                        case any::String:
                        {
                            LuaPushString(L, vec[i].get_string());
                            argsc++;
                        }
                        break;
                        case any::Boolean:
                        {
                            LuaPushBoolean(L, vec[i].get_bool());
                            argsc++;
                        }
                        break;
                        case any::Double:
                        {
                            LuaPushNumber(L, vec[i].get_double());
                            argsc++;
                        }
                        break;
                        default:
                        {
                            std::cout << "Unable to find type" << std::endl;
                        }
                        break;
                    }
                }

                if (LuaPCall(L, argsc, returns.size(), 0) != 0)
                {
                    auto error = LuaToString(L, -1);
                    std::cout << "LUA Error: " << error << std::endl;
                    return returnValues;
                }
                for (unsigned i = 0; i < returns.size(); i++)
                {
                    int expectedType = returns[i];
                    switch (expectedType)
                    {
                    case 2: returnValues.push_back(LuaFunctions::LuaToString(L, i - 1)); break;
                    case 1: returnValues.push_back(LuaFunctions::LuaToNumber(L, i - 1)); break;
                    case 0: returnValues.push_back(LuaFunctions::LuaToNumber(L, i - 1) == 1); break;
                    }
                }
                lua_pop(L, 1);
                return returnValues;
            }
        public:
            static WoWObject* GetUnitById(const char* unitid);
            static WoWObject* GetLocalPlayer();
            static WoWObject* GetTarget();
            static CorpseBase* GetCorpseBase();
            static void Execute(const char* com);
            static void Execute(const std::string& com);
            
            template <class ...Args>
            static std::vector<std::any> Call(std::string const& functionName, std::vector<int> returns, Args... args)
            {
                return internal_Call(functionName, returns, any(args)...);
            };
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
