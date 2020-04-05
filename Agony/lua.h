/*
** $Id: lua.h,v 1.218.1.5 2008/08/06 13:30:12 roberto Exp $
** Lua - An Extensible Extension Language
** Lua.org, PUC-Rio, Brazil (http://www.lua.org)
** See Copyright Notice at the end of this file
*/

#ifndef lua_h
#define lua_h

#include <stdarg.h>
#include <stddef.h>
#include "luaconf.h"
#include "Offsets.h"

#define PlusBase(offset) (Offsets::Base + offset)

#define LUA_VERSION	"Lua 5.1"
#define LUA_RELEASE	"Lua 5.1.4"
#define LUA_VERSION_NUM	501
#define LUA_COPYRIGHT	"Copyright (C) 1994-2008 Lua.org, PUC-Rio"
#define LUA_AUTHORS 	"R. Ierusalimschy, L. H. de Figueiredo & W. Celes"

/* mark for precompiled code (`<esc>Lua') */
#define	LUA_SIGNATURE	"\033Lua"

/* option for multiple returns in `lua_pcall' and `lua_call' */
#define LUA_MULTRET	(-1)

/*
** pseudo-indices
*/
#define LUA_REGISTRYINDEX	(-10000)
#define LUA_ENVIRONINDEX	(-10001)
#define LUA_GLOBALSINDEX	(-10002)
#define lua_upvalueindex(i)	(LUA_GLOBALSINDEX-(i))

/* thread status; 0 is OK */
#define LUA_YIELD	1
#define LUA_ERRRUN	2
#define LUA_ERRSYNTAX	3
#define LUA_ERRMEM	4
#define LUA_ERRERR	5

typedef struct lua_State lua_State;
typedef int (*lua_CFunction) (lua_State* L);

/*
** functions that read/write blocks when loading/dumping Lua chunks
*/
typedef const char* (*lua_Reader) (lua_State* L, void* ud, size_t* sz);
typedef int (*lua_Writer) (lua_State* L, const void* p, size_t sz, void* ud);

/*
** prototype for memory-allocation functions
*/
typedef void* (*lua_Alloc) (void* ud, void* ptr, size_t osize, size_t nsize);

/*
** basic types
*/
#define LUA_TNONE		(-1)
#define LUA_TNIL		0
#define LUA_TBOOLEAN		1
#define LUA_TLIGHTUSERDATA	2
#define LUA_TNUMBER		3
#define LUA_TSTRING		4
#define LUA_TTABLE		5
#define LUA_TFUNCTION		6
#define LUA_TUSERDATA		7
#define LUA_TTHREAD		8

/* minimum Lua stack available to a C function */
#define LUA_MINSTACK	20

/*
** generic extra include file
*/
#if defined(LUA_USER_H)
#include LUA_USER_H
#endif
/* type of numbers in Lua */
typedef LUA_NUMBER lua_Number;


/* type for integer functions */
typedef LUA_INTEGER lua_Integer;

/*
** state manipulation
*/
lua_State* lua_newstate (lua_Alloc f, void *ud)
{
    return reinterpret_cast<lua_State*(__fastcall*)(lua_Alloc f, void* ud)>(PlusBase(0))(f, ud);
}

void lua_close (lua_State *L)
{
    return reinterpret_cast<void(__fastcall*)(lua_State* L)>(PlusBase(0))(L);
}

lua_State* lua_newthread (lua_State *L)
{
    return reinterpret_cast<lua_State*(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}


lua_CFunction lua_atpanic (lua_State *L, lua_CFunction panicf)
{
    return reinterpret_cast<lua_CFunction(__fastcall*)(lua_State * L, lua_CFunction panicf)>(PlusBase(0))(L, panicf);
}


/*
** basic stack manipulation
*/
int lua_gettop (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}

void lua_settop (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void lua_pushvalue (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void lua_remove (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void lua_insert (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void lua_replace (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

int lua_checkstack (lua_State *L, int sz)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int sz)>(PlusBase(0))(L, sz);
}

void lua_xmove (lua_State *from, lua_State *to, int n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * from, lua_State * to, int n)>(PlusBase(0))(from, to, n);
}


/*
** access functions (stack -> C)
*/

int lua_isnumber (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

int lua_isstring (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

int lua_iscfunction (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

int lua_isuserdata (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

int lua_type (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

const char* lua_typename (lua_State *L, int tp)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int tp)>(PlusBase(0))(L, tp);
}


int lua_equal (lua_State *L, int idx1, int idx2)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx1, int idx2)>(PlusBase(0))(L, idx1, idx2);
}

int lua_rawequal (lua_State *L, int idx1, int idx2)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx1, int idx2)>(PlusBase(0))(L, idx1, idx2);
}

int lua_lessthan (lua_State *L, int idx1, int idx2)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx1, int idx2)>(PlusBase(0))(L, idx1, idx2);
}


lua_Number lua_tonumber (lua_State *L, int idx)
{
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

lua_Integer lua_tointeger (lua_State *L, int idx)
{
    return reinterpret_cast<lua_Integer(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

int lua_toboolean (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

const char* lua_tolstring (lua_State *L, int idx, size_t *len)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int idx, size_t * len)>(PlusBase(0))(L, idx, len);
}

size_t lua_objlen (lua_State *L, int idx)
{
    return reinterpret_cast<size_t(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

lua_CFunction lua_tocfunction (lua_State *L, int idx)
{
    return reinterpret_cast<lua_CFunction(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void* lua_touserdata (lua_State *L, int idx)
{
    return reinterpret_cast<void* (__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

lua_State* lua_tothread (lua_State *L, int idx)
{
    return reinterpret_cast<lua_State * (__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

const void* lua_topointer (lua_State *L, int idx)
{
    return reinterpret_cast<const void* (__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}


/*
** push functions (C -> stack)
*/
void lua_pushnil (lua_State *L)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}

void lua_pushnumber (lua_State *L, lua_Number n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, lua_Number n)>(PlusBase(0))(L, n);
}

void lua_pushinteger (lua_State *L, lua_Integer n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, lua_Number n)>(PlusBase(0))(L, n);
}

void lua_pushlstring (lua_State *L, const char *s, size_t l)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, const char* s, size_t l)>(PlusBase(0))(L, s, l);
}

void lua_pushstring (lua_State *L, const char *s)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, const char* s)>(PlusBase(0))(L, s);
}

const char* lua_pushvfstring (lua_State *L, const char *fmt, va_list argp)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, const char* fmt, va_list argp)>(PlusBase(0))(L, fmt, argp);
}

template<typename... Args>
const char* lua_pushfstring (lua_State* L, const char* fmt, Args&&... args)
{
    //std::cout << "Sol called function " << __FUNCTION__ << "\n";
    return reinterpret_cast<const char*(__fastcall*)(lua_State*, const char*, ...)>(PlusBase(0))(L, fmt, std::forward<Args>(args) ...);
};

inline void lua_pushcclosure(lua_State* L, lua_CFunction fn, const int n)
{
    //std::cout << "Sol called function " << __FUNCTION__ << "\n";
    const auto tEnd = *reinterpret_cast<unsigned int*>(0xD415BC);
    const auto fnAddress = reinterpret_cast<unsigned int>(fn);
    if (fnAddress >= tEnd)
        *reinterpret_cast<unsigned int*>(0xD415BC) = fnAddress + 1;
    return reinterpret_cast<void(__cdecl*)(lua_State*, lua_CFunction, int)>(0x84E400)(L, fn, n);
}

void lua_pushboolean (lua_State *L, int b)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int b)>(PlusBase(0))(L, b);
}

void lua_pushlightuserdata (lua_State *L, void *p)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, void* p)>(PlusBase(0))(L, p);
}

int lua_pushthread (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}

/*
** get functions (Lua -> stack)
*/
void lua_gettable (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void lua_getfield (lua_State *L, int idx, const char *k)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx, const char* k)>(PlusBase(0))(L, idx, k);
}

void lua_rawget (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void lua_rawgeti (lua_State *L, int idx, int n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx, int n)>(PlusBase(0))(L, idx, n);
}

void lua_createtable (lua_State *L, int narr, int nrec)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int narr, int nrec)>(PlusBase(0))(L, narr, nrec);
}

void* lua_newuserdata (lua_State *L, size_t sz)
{
    return reinterpret_cast<void* (__fastcall*)(lua_State * L, size_t sz)>(PlusBase(0))(L, sz);
}

int lua_getmetatable (lua_State *L, int objindex)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int objindex)>(PlusBase(0))(L, objindex);
}

void lua_getfenv (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}


/*
** set functions (stack -> Lua)
*/
void lua_settable (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void lua_setfield (lua_State *L, int idx, const char *k)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx, const char* k)>(PlusBase(0))(L, idx, k);
}

void lua_rawset (lua_State *L, int idx)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

void lua_rawseti (lua_State *L, int idx, int n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int idx, int n)>(PlusBase(0))(L, idx, n);
}

int lua_setmetatable (lua_State *L, int objindex)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int objindex)>(PlusBase(0))(L, objindex);
}

int lua_setfenv (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}

/*
** `load' and `call' functions (load and run Lua code)
*/
void lua_call (lua_State *L, int nargs, int nresults)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int nargs, int nresults)>(PlusBase(0))(L, nargs, nresults);
}

int lua_pcall (lua_State *L, int nargs, int nresults, int errfunc)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int nargs, int nresults, int errfunc)>(PlusBase(0))(L, nargs, nresults, errfunc);
}

int lua_cpcall (lua_State *L, lua_CFunction func, void *ud)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, lua_CFunction func, void* ud)>(PlusBase(0))(L, func, ud);
}

int lua_load (lua_State *L, lua_Reader reader, void *dt, const char *chunkname)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, lua_Reader reader, void* dt, const char* chunkname)>(PlusBase(0))(L, reader, dt, chunkname);
}

int lua_dump (lua_State *L, lua_Writer writer, void *data)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, lua_Writer writer, void* data)>(PlusBase(0))(L, writer, data);
}


/*
** coroutine functions
*/
int lua_yield (lua_State *L, int nresults)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int nresults)>(PlusBase(0))(L, nresults);
}

int lua_resume (lua_State *L, int narg)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int narg)>(PlusBase(0))(L, narg);
}

int lua_status (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}

/*
** garbage-collection function and options
*/

#define LUA_GCSTOP		0
#define LUA_GCRESTART		1
#define LUA_GCCOLLECT		2
#define LUA_GCCOUNT		3
#define LUA_GCCOUNTB		4
#define LUA_GCSTEP		5
#define LUA_GCSETPAUSE		6
#define LUA_GCSETSTEPMUL	7

int lua_gc(lua_State* L, int what, int data)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int what, int data)>(PlusBase(0))(L, what, data);
}


/*
** miscellaneous functions
*/

int lua_error (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}

int lua_next (lua_State *L, int idx)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int idx)>(PlusBase(0))(L, idx);
}


void lua_concat (lua_State *L, int n)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int n)>(PlusBase(0))(L, n);
}

lua_Alloc lua_getallocf (lua_State *L, void **ud)
{
    return reinterpret_cast<lua_Alloc(__fastcall*)(lua_State * L, void** ud)>(PlusBase(0))(L, ud);
}

void lua_setallocf (lua_State *L, lua_Alloc f, void *ud)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, lua_Alloc f, void* ud)>(PlusBase(0))(L, f, ud);
}

/*
** ===============================================================
** some useful macros
** ===============================================================
*/
#define lua_pop(L,n)		lua_settop(L, -(n)-1)
#define lua_newtable(L)		lua_createtable(L, 0, 0)
#define lua_register(L,n,f) (lua_pushcfunction(L, (f)), lua_setglobal(L, (n)))
#define lua_pushcfunction(L,f)	lua_pushcclosure(L, (f), 0)
#define lua_strlen(L,i)		lua_objlen(L, (i))
#define lua_isfunction(L,n)	(lua_type(L, (n)) == LUA_TFUNCTION)
#define lua_istable(L,n)	(lua_type(L, (n)) == LUA_TTABLE)
#define lua_islightuserdata(L,n)	(lua_type(L, (n)) == LUA_TLIGHTUSERDATA)
#define lua_isnil(L,n)		(lua_type(L, (n)) == LUA_TNIL)
#define lua_isboolean(L,n)	(lua_type(L, (n)) == LUA_TBOOLEAN)
#define lua_isthread(L,n)	(lua_type(L, (n)) == LUA_TTHREAD)
#define lua_isnone(L,n)		(lua_type(L, (n)) == LUA_TNONE)
#define lua_isnoneornil(L, n)	(lua_type(L, (n)) <= 0)
#define lua_pushliteral(L, s) lua_pushlstring(L, "" s, (sizeof(s)/sizeof(char))-1)
#define lua_setglobal(L,s)	lua_setfield(L, LUA_GLOBALSINDEX, (s))
#define lua_getglobal(L,s)	lua_getfield(L, LUA_GLOBALSINDEX, (s))
#define lua_tostring(L,i)	lua_tolstring(L, (i), NULL)

/*
** compatibility macros and functions
*/
#define lua_open()	luaL_newstate()
#define lua_getregistry(L)	lua_pushvalue(L, LUA_REGISTRYINDEX)
#define lua_getgccount(L)	lua_gc(L, LUA_GCCOUNT, 0)
#define lua_Chunkreader		lua_Reader
#define lua_Chunkwriter		lua_Writer


/* hack */
void lua_setlevel (lua_State *from, lua_State *to)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * from, lua_State * to)>(PlusBase(0))(from, to);
}

/*
** {======================================================================
** Debug API
** =======================================================================
*/

/*
** Event codes
*/
#define LUA_HOOKCALL	0
#define LUA_HOOKRET	1
#define LUA_HOOKLINE	2
#define LUA_HOOKCOUNT	3
#define LUA_HOOKTAILRET 4

/*
** Event codes
*/
#define LUA_HOOKCALL	0
#define LUA_HOOKRET	1
#define LUA_HOOKLINE	2
#define LUA_HOOKCOUNT	3
#define LUA_HOOKTAILRET 4

/*
** Event masks
*/
#define LUA_MASKCALL	(1 << LUA_HOOKCALL)
#define LUA_MASKRET	(1 << LUA_HOOKRET)
#define LUA_MASKLINE	(1 << LUA_HOOKLINE)
#define LUA_MASKCOUNT	(1 << LUA_HOOKCOUNT)
typedef struct lua_Debug lua_Debug;  /* activation record */
/* Functions to be called by the debuger in specific events */
typedef void (*lua_Hook) (lua_State* L, lua_Debug* ar);

int lua_getstack (lua_State *L, int level, lua_Debug *ar)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int level, lua_Debug * ar)>(PlusBase(0))(L, level, ar);
}

int lua_getinfo (lua_State *L, const char *what, lua_Debug *ar)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, const char* what, lua_Debug * ar)>(PlusBase(0))(L, what, ar);
}

const char *lua_getlocal (lua_State *L, const lua_Debug *ar, int n)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, const lua_Debug * ar, int n)>(PlusBase(0))(L, ar, n);
}

const char *lua_setlocal (lua_State *L, const lua_Debug *ar, int n)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, const lua_Debug * ar, int n)>(PlusBase(0))(L, ar, n);
}

const char *lua_getupvalue (lua_State *L, int funcindex, int n)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int funcindex, int n)>(PlusBase(0))(L, funcindex, n);
}

const char *lua_setupvalue (lua_State *L, int funcindex, int n)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int funcindex, int n)>(PlusBase(0))(L, funcindex, n);
}


int lua_sethook (lua_State *L, lua_Hook func, int mask, int count)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, lua_Hook func, int mask, int count)>(PlusBase(0))(L, func, mask, count);
}

lua_Hook lua_gethook (lua_State *L)
{
    return reinterpret_cast<lua_Hook(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}

int lua_gethookmask (lua_State *L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}

int lua_gethookcount(lua_State* L)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L)>(PlusBase(0))(L);
}

struct lua_Debug {
    int event;
    const char *name;	/* (n) */
    const char *namewhat;	/* (n) `global', `local', `field', `method' */
    const char *what;	/* (S) `Lua', `C', `main', `tail' */
    const char *source;	/* (S) */
    int currentline;	/* (l) */
    int nups;		/* (u) number of upvalues */
    int linedefined;	/* (S) */
    int lastlinedefined;	/* (S) */
    char short_src[LUA_IDSIZE]; /* (S) */
    /* private part */
    int i_ci;  /* active function */
};

/* }====================================================================== */

/******************************************************************************
* Copyright (C) 1994-2008 Lua.org, PUC-Rio.  All rights reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/

#endif