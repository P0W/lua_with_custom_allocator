# lua_with_custom_allocator

Used release lua 5.3.4 
* Modified src/make file to add custom allocator CMemPool.cpp/.h
* Modified luaconf.h for lua_getlocaledecpoint() at Line No. 673
* Added a sample script foo.lua and embedded this in foo.c

* For old compilers use following to get liblua.a (ignore warnings)
make c89
