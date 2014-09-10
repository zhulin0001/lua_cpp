//
//  main.cpp
//  demo
//
//  Created by Julin on 14-9-1.
//  Copyright (c) 2014Äê Boyaa. All rights reserved.
//

#include <stdio.h>
#include "include/lua.hpp"
#include <string>
lua_State *L;

char binArray[] = {0x49, 0x43, 0x1d, 0x40, 0x02, 0x01, 0x04, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x2f, 0x70, 0x70, 0x70};

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

void luaParse(char *s, int len){
    lua_getglobal(L, "parse");
    lua_pushlstring(L, s, len);
    lua_call(L, 1, 0); 
	lua_pop(L, 0);
}

int main(int argc, char *argv[]){
	char line[255] = {};
	FILE *fr = fopen("test.lua", "r");
	//FILE *fw = fopen("out.txt", "w");
	int pos = 0;
	for(int i=0; i<256; i++){
		fgets(line, 255, fr);
		short num = 0;
		num |= line[0];
		num << 8;
		num |= line[1];
		printf("num is %d %02x %c.\n", num, num, num);
		pos += strlen(line);
		fseek(fr, pos, SEEK_SET);
	}
	fclose(fr);
	return 0;
	
	
	
	printf("len is %d.\n", sizeof(binArray));
	int sum = 0;
	L = lua_open();
	luaopen_base(L);
	luaL_openlibs(L);
	luaL_loadfile(L, "add.lua");
	lua_pcall(L, 0, LUA_MULTRET, 0);
    luaParse(binArray, sizeof(binArray));
	lua_close(L);
	return 0;
}
