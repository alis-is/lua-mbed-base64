#include "mbedtls/base64.h"
#include <stdlib.h>
#include "base64.h"
#include "lauxlib.h"
#include "lua.h"
#include "luaconf.h"
#include "mbedtls/error.h"

int
l_mbed_base64_encode(lua_State* L) {
    size_t dlen;
    size_t olen;
    size_t slen;
    char error_buf[100];
    const unsigned char* src;
    unsigned char* dst;

    src = (const unsigned char*)luaL_checklstring(L, 1, &slen);

    // get dlen from mbedtls_base64_encode
    mbedtls_base64_encode(NULL, 0, &dlen, src, slen);

    dst = (unsigned char*)malloc(dlen);
    if (NULL == dst) {
        lua_pushnil(L);
        lua_pushstring(L, "out of memory");
        return 2;
    }

    int ret = mbedtls_base64_encode(dst, dlen, &olen, src, slen);
    if (ret != 0) {
        free(dst);
        lua_pushnil(L);
        mbedtls_strerror(ret, error_buf, sizeof(error_buf));
        lua_pushstring(L, error_buf);
        return 2;
    }
    lua_pushlstring(L, (const char*)dst, olen);
    free(dst);
    return 1;
}

int
l_mbed_base64_decode(lua_State* L) {
    size_t dlen;
    size_t olen;
    size_t slen;
    char error_buf[100];
    const unsigned char* src;
    unsigned char* dst;

    src = (const unsigned char*)luaL_checklstring(L, 1, &slen);
    // is slen a multiple of 4?
    if (slen % 4 != 0) {
        lua_pushnil(L);
        lua_pushstring(L, "invalid base64 length");
        return 2;
    }
    // get dlen from mbedtls_base64_decode
    mbedtls_base64_decode(NULL, 0, &dlen, src, slen);

    dst = (unsigned char*)malloc(dlen);
    if (NULL == dst) {
        lua_pushnil(L);
        lua_pushstring(L, "out of memory");
        return 2;
    }

    int ret = mbedtls_base64_decode(dst, dlen, &olen, src, slen);
    if (ret == MBEDTLS_ERR_BASE64_INVALID_CHARACTER) {
        free(dst);
        lua_pushnil(L);
        mbedtls_strerror(ret, error_buf, sizeof(error_buf));
        lua_pushstring(L, error_buf);
        return 2;
    }
    lua_pushlstring(L, (const char*)dst, olen);
    free(dst);
    return 1;
}
