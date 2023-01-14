# LuaVector

A simple utility class mainly designed for C++/Lua interop

```c
local a = vector.new()
print(a)
-- vector{}
print(type(a))
-- userdata

print(a[1])
-- nil

a[1] = 3.14
print(a)
-- vector{3.140000}
print(a[1], a[2])
-- 3.1400001049042 nil
print(#a)
-- 1

a[2] = 6.28
print(a)
-- vector{3.140000, 6.280000}
print(a[1], a[2])
-- 3.1400001049042 6.2800002098083
print(#a)
-- 2

for i, v in ipairs(a) do
    print(i, v)
end
-- 1       3.1400001049042
-- 2       6.2800002098083

a:append(9.42)
print(a)
-- vector{3.140000, 6.280000, 9.420000}

a:extend(1, 2, 3)
print(a)
-- vector{3.140000, 6.280000, 9.420000, 1.000000, 2.000000, 3.000000}

a:insert(2, 0.1234)
print(a)
-- vector{3.140000, 0.123400, 6.280000, 9.420000, 1.000000, 2.000000, 3.000000}

a:sort()
print(a)
-- vector{0.123400, 1.000000, 2.000000, 3.000000, 3.140000, 6.280000, 9.420000}

a:erase(2)
print(a)
-- vector{0.123400, 2.000000, 3.000000, 3.140000, 6.280000, 9.420000}

while #a > 0 do
    local b = a:pop()
    print(a, b)
end
-- vector{0.123400, 2.000000, 3.000000, 3.140000, 6.280000}        9.4200000762939
-- vector{0.123400, 2.000000, 3.000000, 3.140000}  6.2800002098083
-- vector{0.123400, 2.000000, 3.000000}    3.1400001049042
-- vector{0.123400, 2.000000}      3.0
-- vector{0.123400}        2.0
-- vector{}        0.12340000271797
```

## C++/Lua Interop
```c++
int Test(lua_State *L) {
    LuaVector *v = LuaVector::CheckArg(L, 1);
    v->push_back(1);
    return 0;
}
```

```c
test(a)
print(a)
-- vector{1.000000}
```
