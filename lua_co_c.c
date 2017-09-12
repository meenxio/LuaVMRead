lua_newtable

void lua_newtable (lua_State *L);
创建一个空 table ，并将之压入堆栈。 它等价于 lua_createtable(L, 0, 0) 。


lua_gettop

int lua_gettop (lua_State *L);
返回栈顶元素的索引。 因为索引是从 1 开始编号的， 所以这个结果等于堆栈上的元素个数（因此返回 0 表示堆栈为空）。

 

luaL_newmetatable

int luaL_newmetatable (lua_State *L, const char *tname);

如果注册表中已经有Key为tname的数据则返回0. 否则创建一个新表作为userdata的metatable，并在注册表中注册它然后返回1. 不过两种情况都会把注册表中tname相关的值压入堆栈。

 

luaL_checkudata

void *luaL_checkudata (lua_State *L, int narg, const char *tname);
Checks whether the function argument narg is a userdata of the type tname (see luaL_newmetatable).

 

lua_pushstring

void lua_pushstring (lua_State *L, const char *s);
把指针 s 指向的以零结尾的字符串压栈。 Lua 对这个字符串做一次内存拷贝（或是复用一个拷贝）， 因此 s 处的内存在函数返回后，可以释放掉或是重用于其它用途。 字符串中不能包含有零字符；第一个碰到的零字符会认为是字符串的结束。

 

lua_pushlstring

void lua_pushlstring (lua_State *L, const char *s, size_t len);
把指针 s 指向的长度为 len 的字符串压栈。 Lua 对这个字符串做一次内存拷贝（或是复用一个拷贝）， 因此 s 处的内存在函数返回后，可以释放掉或是重用于其它用途。 字符串内可以保存有零字符。

 

lua_pushvalue

void lua_pushvalue (lua_State *L, int index);
把堆栈上给定有效处索引处的元素作一个拷贝压栈。

 

lua_settable

void lua_settable (lua_State *L, int index);
作一个等价于 t[k] = v 的操作， 这里 t 是一个给定有效索引 index 处的值， v 指栈顶的值， 而 k 是栈顶之下的那个值。

这个函数会把键和值都从堆栈中弹出。 和在 Lua 中一样，这个函数可能触发 "newindex" 事件的元方法 （参见 §2.8）。

                                                                                                                                                                                                                                                                      

lua_pushcfunction

void lua_pushcfunction (lua_State *L, lua_CFunction f);
将一个 C 函数压入堆栈。 这个函数接收一个 C 函数指针，并将一个类型为 function 的 Lua 值 压入堆栈。当这个栈定的值被调用时，将触发对应的 C 函数。

注册到 Lua 中的任何函数都必须遵循正确的协议来接收参数和返回值 （参见 lua_CFunction）。

lua_pushcfunction 是作为一个宏定义出现的：

     #define lua_pushcfunction(L,f) lua_pushcclosure(L,f,0)
 

lua_setmetatable

int lua_setmetatable (lua_State *L, int index);
把一个 table 弹出堆栈，并将其设为给定索引处的值的 metatable 。

 

lua_pushcclosure

void lua_pushcclosure (lua_State *L, lua_CFunction fn, int n);
把一个新的 C closure 压入堆栈。

当创建了一个 C 函数后，你可以给它关联一些值，这样就是在创建一个 C closure （参见 §3.4）； 接下来无论函数何时被调用，这些值都可以被这个函数访问到。 为了将一些值关联到一个 C 函数上， 首先这些值需要先被压入堆栈（如果有多个值，第一个先压）。 接下来调用 lua_pushcclosure 来创建出 closure 并把这个 C 函数压到堆栈上。 参数 n 告之函数有多少个值需要关联到函数上。 lua_pushcclosure 也会把这些值从栈上弹出。

 

lua_newuserdata

void *lua_newuserdata (lua_State *L, size_t size);
这个函数分配分配一块指定大小的内存块， 把内存块地址作为一个完整的 userdata 压入堆栈，并返回这个地址。

userdata 代表 Lua 中的 C 值。 完整的 userdata 代表一块内存。 它是一个对象（就像 table 那样的对象）： 你必须创建它，它有着自己的元表，而且它在被回收时，可以被监测到。 一个完整的 userdata 只和它自己相等（在等于的原生作用下）。

当 Lua 通过 gc 元方法回收一个完整的 userdata 时， Lua 调用这个元方法并把 userdata 标记为已终止。 等到这个 userdata 再次被收集的时候，Lua 会释放掉相关的内存。

 

lua_touserdata

void *lua_touserdata (lua_State *L, int index);

如果给定索引处的值是一个完整的 userdata ，函数返回内存块的地址。 如果值是一个 light userdata ，那么就返回它表示的指针。 否则，返回 NULL 。
