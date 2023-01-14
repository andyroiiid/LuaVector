//
// Created by andyroiiid on 1/13/2023.
//

#include "LuaVector.h"

#include <algorithm>
#include <string>

void LuaVector::RegisterMetaTable(lua_State *L) {
    if (luaL_newmetatable(L, LUA_TYPE_NAME)) {
        lua_pushcfunction(L, New);
        lua_setfield(L, 1, "new");

        lua_pushcfunction(L, GarbageCollect);
        lua_setfield(L, 1, "__gc");

        lua_pushcfunction(L, ToString);
        lua_setfield(L, 1, "__tostring");

        lua_pushcfunction(L, Index);
        lua_setfield(L, 1, "__index");

        lua_pushcfunction(L, NewIndex);
        lua_setfield(L, 1, "__newindex");

        lua_pushcfunction(L, Len);
        lua_setfield(L, 1, "__len");

        lua_pushcfunction(L, Append);
        lua_setfield(L, 1, "append");

        lua_pushcfunction(L, Pop);
        lua_setfield(L, 1, "pop");

        lua_pushcfunction(L, Extend);
        lua_setfield(L, 1, "extend");

        lua_pushcfunction(L, Insert);
        lua_setfield(L, 1, "insert");

        lua_pushcfunction(L, Erase);
        lua_setfield(L, 1, "erase");

        lua_pushcfunction(L, Sort);
        lua_setfield(L, 1, "sort");

        lua_setglobal(L, LUA_TYPE_NAME);
    }
}

LuaVector *LuaVector::CheckArg(lua_State *L, int arg) {
    return static_cast<LuaVector *>(luaL_checkudata(L, arg, LUA_TYPE_NAME));
}

int LuaVector::New(lua_State *L) {
    auto p = static_cast<LuaVector *>(lua_newuserdata(L, sizeof(LuaVector)));
    new (p) LuaVector;
    luaL_setmetatable(L, LUA_TYPE_NAME);
    return 1;
}

int LuaVector::GarbageCollect(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (p) {
        p->~LuaVector();
    }
    return 0;
}

int LuaVector::ToString(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    std::string str = "vector{";
    for (int i = 0; i < p->size(); i++) {
        if (i != 0) {
            str += ", ";
        }
        str += std::to_string(p->at(i));
    }
    str += "}";

    lua_pushstring(L, str.c_str());
    return 1;
}

int LuaVector::Index(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    switch (lua_type(L, 2)) {
        case LUA_TNUMBER: {
            lua_Integer idx = lua_tointeger(L, 2) - 1;// convert lua indices to c indices
            if (0 <= idx && idx < p->size()) {
                lua_pushnumber(L, p->at(idx));
                return 1;
            }
            lua_pushnil(L);
            return 1;
        }
        case LUA_TSTRING: {
            const char *meta = lua_tostring(L, 2);
            luaL_getmetafield(L, 1, meta);
            return 1;
        }
        default: {
            lua_pushnil(L);
            return 1;
        }
    }
}

int LuaVector::NewIndex(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    lua_Integer idx = luaL_checkinteger(L, 2) - 1;// convert lua indices to c indices
    lua_Number value = luaL_checknumber(L, 3);

    if (idx < 0) {
        return 0;
    }

    if (idx >= p->size()) {
        p->resize(idx + 1);
    }

    p->at(idx) = static_cast<float>(value);
    return 0;
}

int LuaVector::Len(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    lua_pushinteger(L, static_cast<lua_Integer>(p->size()));
    return 1;
}

int LuaVector::Append(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    lua_Number value = luaL_checknumber(L, 2);
    p->push_back(static_cast<float>(value));

    return 0;
}

int LuaVector::Pop(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    if (p->empty()) {
        lua_pushnil(L);
    } else {
        float back = p->back();
        p->pop_back();
        lua_pushnumber(L, back);
    }

    return 1;
}

int LuaVector::Extend(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    const int numParams = lua_gettop(L);
    p->reserve(p->size() + numParams - 1);
    for (int i = 2; i <= numParams; i++) {
        lua_Number value = luaL_checknumber(L, i);
        p->push_back(static_cast<float>(value));
    }

    return 0;
}

int LuaVector::Insert(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    lua_Integer idx = luaL_checkinteger(L, 2) - 1;// convert lua indices to c indices
    lua_Number value = luaL_checknumber(L, 3);

    p->insert(std::next(p->begin(), idx), static_cast<float>(value));

    return 0;
}

int LuaVector::Erase(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    lua_Integer idx = luaL_checkinteger(L, 2) - 1;// convert lua indices to c indices

    p->erase(std::next(p->begin(), idx));

    return 0;
}

int LuaVector::Sort(lua_State *L) {
    auto p = CheckArg(L, 1);
    if (!p) {
        return 0;
    }

    std::sort(p->begin(), p->end());

    return 0;
}
