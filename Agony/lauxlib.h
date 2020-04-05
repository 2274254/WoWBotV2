/*
** $Id: lauxlib.h,v 1.88.1.1 2007/12/27 13:02:25 roberto Exp $
** Auxiliary functions for building Lua libraries
** See Copyright Notice in lua.h
*/

#ifndef lauxlib_h
#define lauxlib_h

#include <stddef.h>
#include <stdio.h>
#include "lua.h"

#if defined(LUA_COMPAT_GETN)
int luaL_getn)(lua_State* L, int t);
int luaL_setn)(lua_State* L, int t, int n);
#else
#define luaL_getn(L,i)          ((int)lua_objlen(L, i))
#define luaL_setn(L,i,j)        ((void)0)  /* no op! */
#endif

#if defined(LUA_COMPAT_OPENLIB)
#define luaI_openlib	luaL_openlib
#endif

/* extra error code for `luaL_load' */
#define LUA_ERRFILE     (LUA_ERRERR+1)

typedef struct luaL_Reg {
    const char* name;
    lua_CFunction func;
} luaL_Reg;

int luaI_openlib(lua_State* L, const char* libname, const luaL_Reg* l, int nup)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, const char* libname, const luaL_Reg * l, int nup)>(PlusBase(0))(L, libname, l, nup);
}

//so this is what u do with all these functions
void luaL_register (lua_State* L, const char* libname, const luaL_Reg* l)
{
    //moonshadow told me no matter what convertion you give it in 64 bit its always fastcall
    return reinterpret_cast<void(__fastcall*)(lua_State * L, const char* libname, const luaL_Reg * l)>(PlusBase(0))(L, libname, l);
}

int luaL_getmetafield(lua_State* L, int obj, const char* e)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int obj, const char* e)>(PlusBase(0))(L, obj, e);
}

int luaL_callmeta(lua_State* L, int obj, const char* e)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int obj, const char* e)>(PlusBase(0))(L, obj, e);
}

int luaL_typerror (lua_State *L, int narg, const char *tname)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int narg, const char* tname)>(PlusBase(0))(L, narg, tname);
}

int luaL_argerror (lua_State *L, int numarg, const char *extramsg)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int numarg, const char* extramsg)>(PlusBase(0))(L, numarg, extramsg);
}

const char* luaL_checklstring (lua_State *L, int numArg, size_t *l)
{
    return reinterpret_cast<const char*(__fastcall*)(lua_State * L, int numArg, size_t * l)>(PlusBase(0))(L, numArg, l);
}

const char* luaL_optlstring (lua_State *L, int numArg, const char *def, size_t *l)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int numArg, const char* def, size_t * l)>(PlusBase(0))(L, numArg, def, l);
}

lua_Number luaL_checknumber (lua_State *L, int numArg)
{
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int numArg)>(PlusBase(0))(L, numArg);
}

lua_Number luaL_optnumber (lua_State *L, int nArg, lua_Number def)
{
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int nArg, lua_Number def)>(PlusBase(0))(L, nArg, def);
}

lua_Integer luaL_checkinteger (lua_State *L, int numArg)
{
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int numArg)>(PlusBase(0))(L, numArg);
}

lua_Integer luaL_optinteger (lua_State *L, int nArg, lua_Integer def)
{
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int nArg, lua_Integer def)>(PlusBase(0))(L, nArg, def);
}

int luaL_checkstack (lua_State *L, int sz, const char *msg)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int sz, const char* msg)>(PlusBase(0))(L, sz, msg);
}

int luaL_checktype (lua_State *L, int narg, int t)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int narg, int t)>(PlusBase(0))(L, narg, t);
}

int luaL_checkany (lua_State *L, int narg)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int narg)>(PlusBase(0))(L, narg);
}

int luaL_newmetatable (lua_State *L, const char *tname)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, const char* tname)>(PlusBase(0))(L, tname);
}

void* luaL_checkudata (lua_State *L, int ud, const char *tname)
{
    return reinterpret_cast<void*(__fastcall*)(lua_State * L, int ud, const char* tname)>(PlusBase(0))(L, ud, tname);
}

int luaL_where (lua_State *L, int lvl)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int lvl)>(PlusBase(0))(L, lvl);
}

template<typename... Args>
int luaL_error(lua_State* L, const char* fmt, Args&&... args)
{
    //std::cout << "Sol called function " << __FUNCTION__ << "\n";
    return reinterpret_cast<int(__fastcall*)(lua_State*, const char*, ...)>(PlusBase(0))(L, fmt, std::forward<Args>(args) ...);
};

int luaL_checkoption (lua_State *L, int narg, const char *def, const char *const lst[])
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int narg, const char* def, const char* const lst[])>(PlusBase(0))(L, narg, def, lst);
}

int luaL_ref (lua_State *L, int t)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int t)>(PlusBase(0))(L, t);
}

int luaL_unref (lua_State *L, int t, int ref)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int t, int ref)>(PlusBase(0))(L, t, ref);
}

int luaL_loadfile (lua_State *L, const char *filename)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, const char* filename)>(PlusBase(0))(L, filename);
}

int luaL_loadbuffer (lua_State *L, const char *buff, size_t sz, const char *name)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, const char* buff, size_t sz, const char* name)>(PlusBase(0))(L, buff, sz, name);
}

int luaL_loadstring (lua_State *L, const char *s)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, const char* s)>(PlusBase(0))(L, s);
}

lua_State *luaL_newstate (void)
{
    return reinterpret_cast<lua_State*(__fastcall*)()>(PlusBase(0))();
}

const char *luaL_gsub (lua_State *L, const char *s, const char *p, const char *r)
{
    return reinterpret_cast<const char*(__fastcall*)(lua_State * L, const char* s, const char* p, const char* r)>(PlusBase(0))(L, s, p, r);
}

const char* luaL_findtable (lua_State *L, int idx, const char *fname, int szhint)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int idx, const char* fname, int szhint)>(PlusBase(0))(L, idx, fname, szhint);
}

/*
** ===============================================================
** some useful macros
** ===============================================================
*/

#define luaL_argcheck(L, cond,numarg,extramsg) ((void)((cond) || luaL_argerror(L, (numarg), (extramsg))))
#define luaL_checkstring(L,n)	(luaL_checklstring(L, (n), NULL))
#define luaL_optstring(L,n,d)	(luaL_optlstring(L, (n), (d), NULL))
#define luaL_checkint(L,n)	((int)luaL_checkinteger(L, (n)))
#define luaL_optint(L,n,d)	((int)luaL_optinteger(L, (n), (d)))
#define luaL_checklong(L,n)	((long)luaL_checkinteger(L, (n)))
#define luaL_optlong(L,n,d)	((long)luaL_optinteger(L, (n), (d)))
#define luaL_typename(L,i)	lua_typename(L, lua_type(L,(i)))
#define luaL_dofile(L, fn) (luaL_loadfile(L, fn) || lua_pcall(L, 0, LUA_MULTRET, 0))
#define luaL_dostring(L, s) (luaL_loadstring(L, s) || lua_pcall(L, 0, LUA_MULTRET, 0))
#define luaL_getmetatable(L,n)	(lua_getfield(L, LUA_REGISTRYINDEX, (n)))
#define luaL_opt(L,f,n,d)	(lua_isnoneornil(L,(n)) ? (d) : f(L,(n)))

/*
** {======================================================
** Generic Buffer manipulation
** =======================================================
*/

typedef struct luaL_Buffer {
    char *p;			/* current position in buffer */
    int lvl;  /* number of strings in the stack (level) */
    lua_State *L;
    char buffer[LUAL_BUFFERSIZE];
} luaL_Buffer;

#define luaL_addchar(B,c) ((void)((B)->p < ((B)->buffer+LUAL_BUFFERSIZE) || luaL_prepbuffer(B)), (*(B)->p++ = (char)(c)))

/* compatibility only */
#define luaL_putchar(B,c)	luaL_addchar(B,c)
#define luaL_addsize(B,n)	((B)->p += (n))

int luaL_buffinit (lua_State *L, luaL_Buffer *B)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, luaL_Buffer * B)>(PlusBase(0))(L, B);
}

char* luaL_prepbuffer (luaL_Buffer *B)
{
    return reinterpret_cast<char* (__fastcall*)(luaL_Buffer * B)>(PlusBase(0))(B);
}

int luaL_addlstring (luaL_Buffer *B, const char *s, size_t l)
{
    return reinterpret_cast<int(__fastcall*)(luaL_Buffer * B, const char* s, size_t l)>(PlusBase(0))(B, s, l);
}

int luaL_addstring (luaL_Buffer *B, const char *s)
{
    return reinterpret_cast<int(__fastcall*)(luaL_Buffer * B, const char* s)>(PlusBase(0))(B, s);
}

int luaL_addvalue (luaL_Buffer *B)
{
    return reinterpret_cast<int(__fastcall*)(luaL_Buffer * B)>(PlusBase(0))(B);
}

int luaL_pushresult (luaL_Buffer *B)
{
    return reinterpret_cast<int(__fastcall*)(luaL_Buffer * B)>(PlusBase(0))(B);
}

/* }====================================================== */

/* compatibility with ref system */

/* pre-defined references */
#define LUA_NOREF       (-2)
#define LUA_REFNIL      (-1)
#define lua_ref(L,lock) ((lock) ? luaL_ref(L, LUA_REGISTRYINDEX) : (lua_pushstring(L, "unlocked references are obsolete"), lua_error(L), 0))
#define lua_unref(L,ref)        luaL_unref(L, LUA_REGISTRYINDEX, (ref))
#define lua_getref(L,ref)       lua_rawgeti(L, LUA_REGISTRYINDEX, (ref))
#define luaL_reg	luaL_Reg
#endif