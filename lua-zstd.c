#ifndef _LUA_ZSTD_H_
#define _LUA_ZSTD_H_

#include <lua.h>
#include <lauxlib.h>
#include "zstd.h"

/* compress without dictionary */
static int
lcompress(lua_State *L) {
    size_t len;
    const char *str = luaL_checklstring(L, 1, &len);
    int level = luaL_optinteger(L, 2, 1);
    size_t dst_size = ZSTD_compressBound(len);
    luaL_Buffer lbuf;
    char *buf = luaL_buffinitsize(L, &lbuf, dst_size);
    size_t result = ZSTD_compress(buf, dst_size, str, len, level);
    if (ZSTD_isError(result))
    {
        lua_pushliteral(L, "call to ZSTD_compress failed");
        lua_error(L);
    }
    luaL_pushresultsize(&lbuf, result);
    return 1;
}

/* decompress without dictionary */
static int
ldecompress(lua_State *L) {
    size_t len;
    const char *str = luaL_checklstring(L, 1, &len);
    size_t src_size = luaL_checkinteger(L, 2);
    luaL_Buffer lbuf;
    char *buf = luaL_buffinitsize(L, &lbuf, src_size);
    size_t result = ZSTD_decompress(buf, src_size, str, len);
    if (ZSTD_isError(result))
    {
        lua_pushliteral(L, "call to ZSTD_decompress failed");
        lua_error(L);
    }
    luaL_pushresultsize(&lbuf, result);
    return 1;
}

LUAMOD_API int
luaopen_zstd(lua_State *L) {
    luaL_checkversion(L);
    luaL_Reg l[] = {
        { "compress", lcompress },
        { "decompress", ldecompress },
        { NULL, NULL },
    };
    luaL_newlib(L, l);
    return 1;
}

#endif
