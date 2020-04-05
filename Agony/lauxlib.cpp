#include "lauxlib.h"
#include "lua.h"

void luaL_register (lua_State* L, const char* libname, const luaL_Reg* l)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, const char* libname, const luaL_Reg * l)>(PlusBase(0x1996AA0))(L, libname, l);
}

int luaL_getmetafield(lua_State* L, int obj, const char* e)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int obj, const char* e)>(PlusBase(0x1995CF0))(L, obj, e);
}

int luaL_callmeta(lua_State* L, int obj, const char* e)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int obj, const char* e)>(PlusBase(0x19956C0))(L, obj, e);
}

int luaL_typerror (lua_State *L, int narg, const char *tname)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int narg, const char* tname)>(PlusBase(0x1996EA0))(L, narg, tname);
}

int luaL_argerror (lua_State *L, int numarg, const char *extramsg)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int numarg, const char* extramsg)>(PlusBase(0x19955B0))(L, numarg, extramsg);
}

const char* luaL_checklstring (lua_State *L, int numArg, size_t *l)
{
    return reinterpret_cast<const char*(__fastcall*)(lua_State * L, int numArg, size_t * l)>(PlusBase(0x1995810))(L, numArg, l);
}

const char* luaL_optlstring (lua_State *L, int numArg, const char *def, size_t *l)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int numArg, const char* def, size_t * l)>(PlusBase(0x19966F0))(L, numArg, def, l);
}

lua_Number luaL_checknumber (lua_State *L, int numArg)
{
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int numArg)>(PlusBase(0x19958A0))(L, numArg);
}

lua_Number luaL_optnumber (lua_State *L, int nArg, lua_Number def)
{
    return luaL_opt(L, luaL_checknumber, nArg, def);
}

lua_Integer luaL_checkinteger (lua_State *L, int numArg)
{
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int numArg)>(PlusBase(0x19957C0))(L, numArg);
}

lua_Integer luaL_optinteger (lua_State *L, int nArg, lua_Integer def)
{
    //return luaL_opt(L, luaL_checkinteger, nArg, def);
    return reinterpret_cast<lua_Number(__fastcall*)(lua_State * L, int nArg, lua_Integer def)>(PlusBase(0x1996690))(L, nArg, def);
}

void luaL_checkstack (lua_State *L, int sz, const char *msg)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int sz, const char* msg)>(PlusBase(0x19959C0))(L, sz, msg);
}

void luaL_checktype (lua_State *L, int narg, int t)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int narg, int t)>(PlusBase(0x1995A10))(L, narg, t);
}

void luaL_checkany (lua_State *L, int narg)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int narg)>(PlusBase(0x1995780))(L, narg);
}

int luaL_newmetatable (lua_State *L, const char *tname)
{
    lua_getfield(L, LUA_REGISTRYINDEX, tname);  /* get registry.name */
    if (!lua_isnil(L, -1))  /* name already in use? */
        return 0;  /* leave previous value on top, but return 0 */
    lua_pop(L, 1);
    lua_newtable(L);  /* create metatable */
    lua_pushvalue(L, -1);
    lua_setfield(L, LUA_REGISTRYINDEX, tname);  /* registry.name = metatable */
    return 1;
}

void* luaL_checkudata (lua_State *L, int ud, const char *tname)
{
    void* p = lua_touserdata(L, ud);
    if (p != NULL) {  /* value is a userdata? */
        if (lua_getmetatable(L, ud)) {  /* does it have a metatable? */
            lua_getfield(L, LUA_REGISTRYINDEX, tname);  /* get correct metatable */
            if (lua_rawequal(L, -1, -2)) {  /* does it have the correct mt? */
                lua_pop(L, 2);  /* remove both metatables */
                return p;
            }
        }
    }
    luaL_typerror(L, ud, tname);  /* else error */
    return NULL;  /* to avoid warnings */
}

void luaL_where (lua_State *L, int lvl)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int lvl)>(PlusBase(0x1996DF0))(L, lvl);
}

int luaL_checkoption (lua_State *L, int narg, const char *def, const char *const lst[])
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int narg, const char* def, const char* const lst[])>(PlusBase(0x1995900))(L, narg, def, lst);
}

int luaL_ref (lua_State *L, int t)//2args
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, int t)>(PlusBase(0x1996890))(L, t);
}

void luaL_unref (lua_State *L, int t, int ref)//3args
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, int t, int ref)>(PlusBase(0x1996C50))(L, t, ref);
}

int luaL_loadfile (lua_State *L, const char *filename)
{
    return 0;//Removed by blizzard.
}

int luaL_loadbuffer (lua_State *L, const char *buff, size_t sz, const char *name)
{
    return reinterpret_cast<int(__fastcall*)(lua_State * L, const char* buff, size_t sz, const char* name)>(PlusBase(0x19961C0))(L, buff, sz, name);
}

int luaL_loadstring (lua_State *L, const char *s)
{
    return 0;//Blizzard uses Framescript::Execute, not needed for us.
}

lua_State* luaL_newstate (void)
{
    return nullptr;//Blizzard already handle this
}

const char *luaL_gsub (lua_State *L, const char *s, const char *p, const char *r)
{
    const char* wild;
    size_t l = strlen(p);
    luaL_Buffer b;
    luaL_buffinit(L, &b);
    while ((wild = strstr(s, p)) != NULL)
    {
        luaL_addlstring(&b, s, wild - s);  /* push prefix */
        luaL_addstring(&b, r);  /* push replacement in place of pattern */
        s = wild + l;  /* continue after `p' */
    }
    luaL_addstring(&b, s);  /* push last suffix */
    luaL_pushresult(&b);
    return lua_tostring(L, -1);
}

const char* luaL_findtable (lua_State *L, int idx, const char *fname, int szhint)
{
    return reinterpret_cast<const char* (__fastcall*)(lua_State * L, int idx, const char* fname, int szhint)>(PlusBase(0x1995BC0))(L, idx, fname, szhint);
}

void luaL_buffinit (lua_State *L, luaL_Buffer *B)
{
    return reinterpret_cast<void(__fastcall*)(lua_State * L, luaL_Buffer * B)>(PlusBase(0x19956A0))(L, B);
}

char* luaL_prepbuffer (luaL_Buffer *B)
{
    return reinterpret_cast<char* (__fastcall*)(luaL_Buffer * B)>(PlusBase(0x19967E0))(B);
}

void luaL_addlstring (luaL_Buffer *B, const char *s, size_t l)
{
    return reinterpret_cast<void(__fastcall*)(luaL_Buffer * B, const char* s, size_t l)>(PlusBase(0x1995430))(B, s, l);
}

void luaL_addstring (luaL_Buffer *B, const char *s)
{
    luaL_addlstring(B, s, strlen(s));
}

void luaL_addvalue (luaL_Buffer *B)
{
    return reinterpret_cast<void(__fastcall*)(luaL_Buffer * B)>(PlusBase(0x19954F0))(B);
}

void luaL_pushresult (luaL_Buffer *B)
{
    return reinterpret_cast<void(__fastcall*)(luaL_Buffer * B)>(PlusBase(0x1996830))(B);
}