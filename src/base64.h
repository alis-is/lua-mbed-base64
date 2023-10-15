#ifndef LUA_MBED_BASE64_H__
#define LUA_MBED_BASE64_H__
#include "lua.h"

/*
---#DES 'base64.encode'
---
---Encodes a string to base64.
---@param data string: bytes to encode
---@return string?, string?: encoded bytes, error
*/
int l_mbed_base64_encode(lua_State* L);
/*
---#DES 'base64.decode'
---
---Decodes a base64 encoded string.
---@param encoded string: encoded bytes.
---@return string?, string?: decoded bytes, error message
*/
int l_mbed_base64_decode(lua_State* L);

#endif // LUA_MBED_BASE64_H__