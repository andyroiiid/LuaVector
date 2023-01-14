#include <lua.hpp>

#include "LuaVector.h"

int Test(lua_State *L) {
    LuaVector *v = LuaVector::CheckArg(L, 1);
    v->push_back(1);
    return 0;
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);

    LuaVector::RegisterMetaTable(L);

    lua_register(L, "test", Test);

    const char *TEST_CODE = R"LUA(
local a = vector.new()
print(a)
print(type(a))

print(a[1])

a[1] = 3.14
print(a)
print(a[1], a[2])
print(#a)

a[2] = 6.28
print(a)
print(a[1], a[2])
print(#a)

for i, v in ipairs(a) do
    print(i, v)
end

a:append(9.42)
print(a)

a:extend(1, 2, 3)
print(a)

a:insert(2, 0.1234)
print(a)

a:sort()
print(a)

a:erase(2)
print(a)

while #a > 0 do
    local b = a:pop()
    print(a, b)
end

test(a)
print(a)
)LUA";

    if (luaL_dostring(L, TEST_CODE) != LUA_OK) {
        fprintf(stderr, "lua error: %s\n", lua_tostring(L, -1));
    }

    lua_close(L);
    return 0;
}
