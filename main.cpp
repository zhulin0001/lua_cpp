//
//  main.cpp
//  demo
//
//  Created by Julin on 14-9-1.
//  Copyright (c) 2014Äê Boyaa. All rights reserved.
//

#include <stdio.h>
#include <cstdint>
#include "include/lua.hpp"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
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

uint8_t hexCharToData(const uint8_t cChar){
	if ( cChar >= '0' && cChar <= '9') {
		return (uint8_t)(cChar - '0');
	}
	if ( cChar >= 'a' && cChar <= 'f') {
		return (uint8_t)(cChar - 'a' + 0x0a);
	}
	if ( cChar >= 'A' && cChar <= 'F') {
		return (uint8_t)(cChar - 'A' + 0x0A);
	}
	return 0xff;
}

uint8_t dataToHexChar(const uint8_t cChar){
	if (cChar <= 0x09) {
		return (uint8_t)(cChar + '0');
	}
	if ( cChar >= 0x0A && cChar <= 0x0F) {
		return (uint8_t)(cChar + 'A' - 0x0A);
	}
	return 0xff;
}

int main(int argc, char *argv[]){

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


void parseEncoding(){
	string result;
	char line[255] = {};
	fstream out;
	out.open("test.lua",ios::in);
	while(!out.eof()){
		out.getline(line,255,'\r');
		uint8_t num = 0;
		printf("Read: %c %c\n", line[0], line[1]);
		num = num | hexCharToData(line[0]) << 4;
		num = num | hexCharToData(line[1]) & 0x0f;
		printf("[len:%d]num is %d|%02x\n", strlen(line), num, num);
		char temp[4] = {};
		sprintf(temp, "\\%03d", num);
		result += temp;
	}
	out.close();
	cout << result << endl;
}