project(lua_mbed_base64)

file(GLOB lua_mbed_base64_sources ./src/**.c)
set(lua_mbed_base64 ${lua_mbed_base64_sources})

add_library(lua_mbed_base64 ${lua_mbed_base64})
target_link_libraries(lua_mbed_base64)