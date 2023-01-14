//
// Created by andyroiiid on 1/13/2023.
//

#pragma once

#include <lua.hpp>

#include <vector>

class LuaVector : public std::vector<float> {
public:
    static constexpr const char *LUA_TYPE_NAME = "vector";

    static void RegisterMetaTable(lua_State *L);

    static LuaVector *CheckArg(lua_State *L, int arg);

private:
    static int New(lua_State *L);

    static int GarbageCollect(lua_State *L);

    static int ToString(lua_State *L);

    static int Index(lua_State *L);

    static int NewIndex(lua_State *L);

    static int Len(lua_State *L);

    static int Append(lua_State *L);

    static int Pop(lua_State *L);

    static int Extend(lua_State *L);

    static int Insert(lua_State *L);

    static int Erase(lua_State *L);

    static int Sort(lua_State *L);
};
