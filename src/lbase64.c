#include "base64.h"
#include "lauxlib.h"
#include "lua.h"

static const struct luaL_Reg luaBase64[] = {
    {"encode", l_mbed_base64_encode},
    {"decode", l_mbed_base64_decode},
    {NULL, NULL},
};

int
luaopen_l_mbed_base64(lua_State* L) {
    lua_newtable(L);
    luaL_setfuncs(L, luaBase64, 0);
    return 1;
}