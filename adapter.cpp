#include <stdio.h>
#include <string.h>
#include <include/lua.hpp>

static int add2(lua_State* L){
    double op1 = luaL_checknumber(L, 1);
    double op2 = luaL_checknumber(l, 2);
    lua_pushnumber(L, op1+op2);

    return 1;
}

static int sub2(lua_State* L){
    double op1 = luaL_checknumber(L, 1);
    double op2 = luaL_checknumber(L, 2);
    lua_pushnumber(L, op1-op2);

    return 1;
}

const char* luacode = "print(add2(1.0, 2.0)) print(sub2(3.0, 1.3))";

int main(int argc, char* argv[]){
    lua_State* L = lua_open();
    luaopen_base(L);
    luaL_openlibs(L);

    lua_register(L, "add2", add2);
    lua_register(L, "sub2", sub2);

    if(luaL_dostring(L, luacode)){
        printf("Failed to invoke.\n");
    }
    lua_close(L);
    return 0;
}
