luaV_execute(){
     reentry:
     while(读取指令){
          OP_XXX:do_XXX;
          OP_CALL：保存当前现场，将被调用的函数(闭包)加载，然后goto reentry, 继续while循环执行指令；
          OP_RETURN：恢复上层调用相关现场，然后goto reentry，继续while循环执行调用的下一条指令；
     }
}

lua_settop(lua_State *L, int idx)



lua_pcallk
=====================================
lua_pcallk(L, ..., errfunc, ...)
	[CallS c]
	index2addr(L, errfunc)
	savestack(L, o)
	luaD_pcall(L, f_call, &c, ...)
		luaD_rawrunprotected(L, f_call, &c)
			_setjmp(...)
			f_call(L, &c)
				luaD_call(L, c->func, c->nresult, 0)
					luaD_precall(L, c->func, c->nresult)     // Note 1
					luaV_execute(...)                        //
	adjustresults(...)




Note 1: A normal call purely in byte-code invoke "luaD_precall()" and
        re-enter the exec-loop by a "goto".



lua_pcallk (with continuation)
=====================================
lua_pcallk(L, ..., errfunc, ctx, k)
	[CallS c]
		index2addr(L, errfunc)
		savestack(L, o)



luaD_precall (lua_State *L, StkId func, int nresults)
=====================================
(C Closure) (return 1 for C-closure)
-------------------------
luaD_precall(L, func, nresult)
	savestack(L, func)						// ==> funcr
	clCvalue(func)
	next_ci(L)
	restorestack(L, funcr)					// ==> ci->func, same to "func ==> ci->func"
	luaC_checkGC(L)
	(*f)(...)								// ==> n
	luaD_poscall(L, L->top - n)
		L->ci->func ==> res
		[Loop from "L->top - n" to "L->top"]
			setobjs2s(L, ...)
		[Loop]
			setnilvalue(...)
