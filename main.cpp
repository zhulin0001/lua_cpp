//
//  main.cpp
//  demo
//
//  Created by Julin on 14-9-1.
//  Copyright (c) 2014Äê Boyaa. All rights reserved.
//

#include <stdio.h>
#include "include/lua.hpp"

lua_State *L;
int luaAdd(int x, int y){
	int sum;
	lua_getglobal(L, "add");
	lua_pushnumber(L, x);
	lua_pushnumber(L, y);
	lua_call(L, 2, 1);
	sum = (int)lua_tonumber(L, -1);
	lua_pop(L, 1);
	return sum;
}

int main(int argc, char *argv[]){
	int sum = 0;
	L = lua_open();
	luaopen_base(L);
	luaL_openlibs(L);
	luaL_loadfile(L, "add.lua");
	lua_pcall(L, 0, LUA_MULTRET, 0);
	sum = luaAdd(10, 15);
	printf("The sum is %d\n", sum);
	lua_close(L);
	return 0;
}
