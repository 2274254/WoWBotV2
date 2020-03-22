#pragma once
#include <cstdint>
#include <string>
#include <cmath>
#include <map>
#include <vector>
#include <tuple>
#include "Macros.h"
#include "Offsets.h"
#include "WoWObject.h"

struct any {
    enum type { Int, Float, String, Boolean, Double };
    any(int   e) { m_data.INT = e; m_type = Int; }
    any(float e) { m_data.FLOAT = e; m_type = Float; }
    any(char* e) { m_data.STRING = e; m_type = String; }
    any(bool e) { m_data.BOOLEAN = e; m_type = Boolean; }
    any(double e) { m_data.DOUBLE = e; m_type = Double; }
    type get_type() const { return m_type; }
    int get_int() const { return m_data.INT; }
    float get_float() const { return m_data.FLOAT; }
    char* get_string() const { return m_data.STRING; }
    bool get_bool() const { return m_data.BOOLEAN; }
    double get_double() const { return m_data.DOUBLE; }
private:
    type m_type;
    union {
        int   INT;
        float FLOAT;
        char* STRING;
        bool BOOLEAN;
        double DOUBLE;
    } m_data;
};

namespace Agony
{
    namespace Native
    {
        struct DLLEXPORT Caster
        {
            Caster(int top, uintptr_t* L) : top(top), L(L)
            {
            }
            template<typename ...T>
            operator std::tuple<T...>()
            {
                constexpr auto size = std::tuple_size<std::tuple<T...>>::value;
                constexpr auto seq = std::make_index_sequence<size>{};
                return std::make_tuple(Get<T>(seq) ...);
            }

            template<typename R, size_t I, size_t ... REST>
            R Get(const std::index_sequence<REST ...>&)
            {
                if (std::is_same<R, int>::value)
                    return reinterpret_cast<double(__fastcall*)(uintptr_t*, int32_t)>(Offsets::Base + Offsets::lua_tonumber)(L, top + I);
                return R();
            }

            int top;
            uintptr_t* L;
        };
        class DLLEXPORT LuaFunctions
        {
            #define LUA_GLOBALSINDEX        (-10002)
            #define lua_pop(L,n)            LuaFunctions::LuaSetTop(L, -(n)-1)
            #define lua_getglobal(L,s)      LuaFunctions::LuaGetField(L, LUA_GLOBALSINDEX, (s))

            /*template <class ...Args>
            static void internal_Call(const char* functionName, const Args&... args)
            {
                uintptr_t* L = *(uintptr_t**)(Offsets::Base + Offsets::lua_state);
                lua_getglobal(L, functionName);
                //std::vector<any> vec = { args... }; // unnecessary
                any vec[sizeof...(Args)] = { args... }; // more efficient
                for (unsigned i = 0; i < vec.size(); ++i)
                {
                    switch (vec[i].get_type())
                    {
                        case any::Int:
                        {
                            LuaPushInteger(L, vec[i].get_int());
                        }
                        break;
                        case any::Float:
                        {
                            LuaPushNumber(L, (double)vec[i].get_float());
                        }
                        break;
                        case any::String:
                        {
                            LuaPushString(L, vec[i].get_string());
                        }
                        break;
                        case any::Boolean:
                        {
                            LuaPushBoolean(L, vec[i].get_bool());
                        }
                        break;
                        case any::Double:
                        {
                            LuaPushNumber(L, vec[i].get_double());
                        }
                        break;
                    }
                }
                if (LuaPCall(L, 2, 1, 0) != 0)
                {
                    auto error = LuaToString(L, -1);
                    std::count << "LUA Error: " << error << std::endl;
                    return;
                }
                /*std::vector<std::any> returnValues;
                for (unsigned i = 0; i < returnValues.size(); i++)
                {
                    auto expectedType = returnValues[i];
                    switch (expectedType)
                    {
                        case "string": returnValues.push_back(LuaFunctions::LuaToString(L, i - 1)); break;
                        case "float":
                        case "double":
                        case "number": returnValues.push_back(LuaFunctions::LuaToNumber(L, i - 1)); break;
                        case "bool": returnValues.push_back(LuaFunctions::LuaToNumber(L, i - 1) == 1); break;
                    }
                }* /
                lua_pop(L, 1);
                //return returnValues;
            }*/
        public:
            static WoWObject* GetUnitById(const char* unitid);
            static WoWObject* GetLocalPlayer();
            static WoWObject* GetTarget();
            static CorpseBase* GetCorpseBase();
            static void Execute(const char* com);
            static void Execute(const std::string& com);
            
            template<typename R, typename ...Args>
            static R Call(std::string const& functionName, Args&&... args)
            {
                uintptr_t* L = *(uintptr_t**)(Offsets::Base + Offsets::lua_state);

                constexpr auto size = std::tuple_size<R>::value;
                int top = 0;

                lua_getglobal(L, functionName.c_str());

                //any vec[sizeof...(Args)] = { args... };
                std::vector<any> vec = { args... };
                
                for (unsigned i = 0; i < vec.size(); ++i)
                {
                    switch (vec[i].get_type())
                    {
                    case any::Int:
                    {
                        LuaPushInteger(L, vec[i].get_int());
                    }
                    break;
                    case any::Float:
                    {
                        LuaPushNumber(L, (double)vec[i].get_float());
                    }
                    break;
                    case any::String:
                    {
                        LuaPushString(L, vec[i].get_string());
                    }
                    break;
                    case any::Boolean:
                    {
                        LuaPushBoolean(L, vec[i].get_bool());
                    }
                    break;
                    case any::Double:
                    {
                        LuaPushNumber(L, vec[i].get_double());
                    }
                    break;
                    }
                }
                
                if (LuaPCall(L, vec.size(), size, 0) != 0)
                {
                    //auto error = LuaToString(L, -1);
                    //std::count << "LUA Error: " << error << std::endl;
                    //return Caster(top, L);
                }

                top = LuaGetTop(L);

                for (unsigned i = 0; i < top; i++)
                {
                    
                }

                //Foreach top, get type in R and add it to caster ?

                // lua_pcall(L, sizeof...(Args), size, errfunc); // check return value!
                return Caster(top, L);
            }
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
