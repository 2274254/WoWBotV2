#include "lua.h"

lua_State* lua_newstate (lua_Alloc f, void *ud) //same v
{
    return nullptr;
}

void lua_close (lua_State *L) //not going to be needed as using wows state anyways
{
    return;
}

lua_State* lua_newthread (lua_State *L)
{
    return reinterpret_cast<lua_State*(__fastcall*)(lua_State * L)>(PlusBase(0x1D0780))(L);
}

lua_CFunction lua_atpanic (lua_State *L, lua_CFunction panicf)
{
    return reinterpret_cast<lua_CFunction(__fastcall*)(lua_State * L, lua_CFunction panicf)>(PlusBase(0x1CF9D0))(L, panicf);
}

int lua_gettop (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(Offsets::lua_gettop))(L);
}

void lua_settop (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(Offsets::lua_settop))(L, idx);
}

void lua_pushvalue (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0D30))(L, idx);
}

void lua_remove (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1150))(L, idx);
}

void lua_insert (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D04F0))(L, idx);
}

void lua_replace (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1210))(L, idx);
}

int lua_checkstack (lua_State *L, int sz)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int sz)>(PlusBase(0x1CFA40))(L, sz);
}

void lua_xmove (lua_State *from, lua_State *to, int n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * from, lua_State * to, int n)>(PlusBase(0x1D1AA0))(from, to, n);
}

int lua_isnumber (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0640))(L, idx);
}

int lua_isstring (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0670))(L, idx);
}

int lua_iscfunction (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0610))(L, idx);
}

int lua_isuserdata (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D06B0))(L, idx);
}

int lua_type (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1A50))(L, idx);
}

const char* lua_typename (lua_State *L, int tp)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int tp)>(PlusBase(0x1D1A80))(L, tp);
}

int lua_equal (lua_State *L, int idx1, int idx2)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx1, int idx2)>(PlusBase(0x1CFD50))(L, idx1, idx2);
}

int lua_rawequal (lua_State *L, int idx1, int idx2)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx1, int idx2)>(PlusBase(0x1D0E10))(L, idx1, idx2);
}

int lua_lessthan (lua_State *L, int idx1, int idx2)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx1, int idx2)>(PlusBase(0x1D06E0))(L, idx1, idx2);
}

lua_Number lua_tonumber (lua_State *L, int idx)
{
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1940))(L, idx);
}

lua_Integer lua_tointeger (lua_State *L, int idx)
{
    return reinterpret_cast<lua_Integer(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1820))(L, idx);
}

int lua_toboolean (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D17C0))(L, idx);
}

const char* lua_tolstring (lua_State *L, int idx, size_t *len)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int idx, size_t * len)>(PlusBase(0x1D18A0))(L, idx, len);
}

size_t lua_objlen (lua_State *L, int idx)
{
    return reinterpret_cast<size_t(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0890))(L, idx);
}

lua_CFunction lua_tocfunction (lua_State *L, int idx)
{
    return nullptr;
}

void* lua_touserdata (lua_State *L, int idx)
{
    return reinterpret_cast<void* (__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1A10))(L, idx);
}

lua_State* lua_tothread (lua_State *L, int idx)
{
    return reinterpret_cast<lua_State * (__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D19F0))(L, idx);
}

const void* lua_topointer (lua_State *L, int idx)
{
    return reinterpret_cast<const void* (__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1980))(L, idx);
}

void lua_pushnil (lua_State *L)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L)>(PlusBase(0x1D0C10))(L);
}

void lua_pushnumber (lua_State *L, lua_Number n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, lua_Number n)>(PlusBase(0x1D0C30))(L, n);
}

void lua_pushinteger (lua_State *L, lua_Integer n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, lua_Number n)>(PlusBase(0x1D0B40))(L, n);
}

void lua_pushlstring (lua_State *L, const char *s, size_t l)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, const char* s, size_t l)>(PlusBase(0x1D0B90))(L, s, l);
}

void lua_pushstring (lua_State *L, const char *s)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, const char* s)>(PlusBase(0x1D0C50))(L, s);
}

const char* lua_pushvfstring (lua_State *L, const char *fmt, va_list argp)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, const char* fmt, va_list argp)>(PlusBase(0x1D0DC0))(L, fmt, argp);
}

void lua_pushcclosure(lua_State* L, lua_CFunction fn, const int n)
{
    const auto tEnd = *reinterpret_cast<uintptr_t*>(PlusBase(Offsets::InvalidFunctionPtr));
    const auto fnAddress = reinterpret_cast<uintptr_t>(fn);
    if (fnAddress >= tEnd)
    {
        const auto dif = fnAddress - tEnd;
        *reinterpret_cast<uintptr_t*>(PlusBase(Offsets::InvalidFunctionPtr)) = tEnd + dif + 1;
    }
    return reinterpret_cast<void(__cdecl*)(lua_State*, lua_CFunction, int)>(PlusBase(0x1D09D0))(L, fn, n);
}

void lua_pushboolean (lua_State *L, int b)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int b)>(PlusBase(Offsets::lua_pushboolean))(L, b);
}

void lua_pushlightuserdata (lua_State *L, void *p)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, void* p)>(PlusBase(0x1D0B70))(L, p);
}

int lua_pushthread (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0x1D0D00))(L);
}

void lua_gettable (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0360))(L, idx);
}

void lua_getfield (lua_State *L, int idx, const char *k)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx, const char* k)>(PlusBase(0x1D0270))(L, idx, k);
}

void lua_rawget (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0E60))(L, idx);
}

void lua_rawgeti (lua_State *L, int idx, int n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx, int n)>(PlusBase(0x1D0EF0))(L, idx, n);
}

void lua_createtable (lua_State *L, int narr, int nrec)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int narr, int nrec)>(PlusBase(0x1CFC90))(L, narr, nrec);
}

void* lua_newuserdata (lua_State *L, size_t sz)
{
    return reinterpret_cast<void* (__fastcall*)(lua_State * L, size_t sz)>(PlusBase(0x1D07D0))(L, sz);
}

int lua_getmetatable (lua_State *L, int objindex)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int objindex)>(PlusBase(0x1D02F0))(L, objindex);
}

void lua_getfenv (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D00B0))(L, idx);
}

void lua_settable (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1590))(L, idx);
}

void lua_setfield (lua_State *L, int idx, const char *k)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx, const char* k)>(PlusBase(0x1D1440))(L, idx, k);
}

void lua_rawset (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0F90))(L, idx);
}

void lua_rawseti (lua_State *L, int idx, int n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx, int n)>(PlusBase(0x1D1070))(L, idx, n);
}

int lua_setmetatable (lua_State *L, int objindex)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int objindex)>(PlusBase(0x1D14D0))(L, objindex);
}

int lua_setfenv (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D1360))(L, idx);
}

void lua_call (lua_State *L, int nargs, int nresults)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int nargs, int nresults)>(PlusBase(0x1CF9F0))(L, nargs, nresults);
}

int lua_pcall (lua_State *L, int nargs, int nresults, int errfunc)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int nargs, int nresults, int errfunc)>(PlusBase(0x1D0910))(L, nargs, nresults, errfunc);
}

int lua_cpcall (lua_State *L, lua_CFunction func, void *ud) //should never be called
{
    return 0;
}

int lua_load (lua_State *L, lua_Reader reader, void *dt, const char *chunkname)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, lua_Reader reader, void* dt, const char* chunkname)>(PlusBase(0x1D0730))(L, reader, dt, chunkname);
}

int lua_dump (lua_State *L, lua_Writer writer, void *data) //prolly removed
{
    return 0;
}

int lua_yield (lua_State *L, int nresults)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int nresults)>(PlusBase(0x1C9FB0))(L, nresults);
}

int lua_resume (lua_State *L, int narg)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int narg)>(PlusBase(0x1C9E60))(L, narg);
}

int lua_status (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0x1D17B0))(L);
}

int lua_gc(lua_State* L, int what, int data)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int what, int data)>(PlusBase(0x1CFDC0))(L, what, data);
}

int lua_error (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0x1CFDB0))(L);
}

int lua_next (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0x1D0850))(L, idx);
}

void lua_concat (lua_State *L, int n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int n)>(PlusBase(0x1CFB10))(L, n);
}

lua_Alloc lua_getallocf (lua_State *L, void **ud)
{
    return nullptr;
}

void lua_setallocf (lua_State *L, lua_Alloc f, void *ud)
{
    return;
}

/* hack */
void lua_setlevel (lua_State *from, lua_State *to)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * from, lua_State * to)>(PlusBase(0x1D14C0))(from, to);
}

int lua_getstack (lua_State *L, int level, lua_Debug *ar)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int level, lua_Debug * ar)>(PlusBase(0x1C83D0))(L, level, ar);
}

int lua_getinfo (lua_State *L, const char *what, lua_Debug *ar)
{
    return 0;
}

const char *lua_getlocal (lua_State *L, const lua_Debug *ar, int n)
{
    return "";
}

const char *lua_setlocal (lua_State *L, const lua_Debug *ar, int n)
{
    return "";
}

const char *lua_getupvalue (lua_State *L, int funcindex, int n)
{
    return "";
}

const char *lua_setupvalue (lua_State *L, int funcindex, int n)
{
    return "";
}

int lua_sethook (lua_State *L, lua_Hook func, int mask, int count)
{
    return 0;
}

lua_Hook lua_gethook (lua_State *L)
{
    return nullptr;
}

int lua_gethookmask (lua_State *L)
{
    return 0;
}

int lua_gethookcount(lua_State* L)
{
    return 0;
}