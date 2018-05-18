
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "CmemPool.h"

static lua_State *L = NULL;

/* call a function `f' defined in Lua */
double f (double x, double y) 
{
   double z = 0.0;

   /* push functions and arguments */
   lua_getglobal(L, "lua_fun");  /* function to be called */
   lua_pushnumber(L, x);   /* push 1st argument */
   lua_pushnumber(L, y);   /* push 2nd argument */

   /* do the call (2 arguments, 1 result) */
   if (lua_pcall(L, 2, 1, 0) != 0)
      fprintf(stderr, "error running function `lua_fun': %s",
      lua_tostring(L, -1));

   /* retrieve result */
   if (!lua_isnumber(L, -1))
      fprintf(stderr, "function `f' must return a number");
   z = lua_tonumber(L, -1);
   lua_pop(L, 1);  /* pop returned value */
   return z;
}


/** 
* Referenced  from https://www.lua.org/pil/25.3.html 
*/
void call_va (const char *func, const char *sig, ...) {
   va_list vl;
   int narg, nres;  /* number of arguments and results */

   //lua_settop(L, 0); /* Clear lua stack */

   va_start(vl, sig);
   lua_getglobal(L, func);  /* get function */
   if(!lua_isfunction(L, -1 ))
   {
      return ;
   }

   /* push arguments */
   narg = 0;
   while (*sig) {  /* push arguments */
      switch (*sig++) {

      case 'd':  /* double argument */
         lua_pushnumber(L, va_arg(vl, double));
         break;

      case 'i':  /* int argument */
         lua_pushnumber(L, va_arg(vl, int));
         break;

      case 's':  /* string argument */
         lua_pushstring(L, va_arg(vl, char *));
         break;

      case '>':
         goto endwhile;

      default:
         fprintf(stderr, "invalid option (%c)", *(sig - 1));
      }
      narg++;
      luaL_checkstack(L, 1, "too many arguments");
   } endwhile:

   /* do the call */
   nres = strlen(sig);  /* number of expected results */
   if (lua_pcall(L, narg, nres, 0) != 0)  /* do the call */
      fprintf(stderr, "error running function `%s': %s\n",
      func, lua_tostring(L, -1));

   /* retrieve results */
   nres = -nres;  /* stack index of first result */
   while (*sig) {  /* get results */
      switch (*sig++) {

      case 'd':  /* double result */
         if (!lua_isnumber(L, nres))
            fprintf(stderr, "wrong result type\n");
         *va_arg(vl, double *) = lua_tonumber(L, nres);
         break;

      case 'i':  /* int result */
         if (!lua_isnumber(L, nres))
            fprintf(stderr, "wrong result type\n");
         *va_arg(vl, int *) = (int)lua_tonumber(L, nres);
         break;

      case 's':  /* string result */
         if (!lua_isstring(L, nres))
            fprintf(stderr, "wrong result type\n");
         *va_arg(vl, const char **) = lua_tostring(L, nres);
         break;

      default:
         fprintf(stderr, "invalid option (%c)\n", *(sig - 1));
      }
      nres++;
   }
   va_end(vl);
}

void bail(lua_State *L, char *msg)
{
   fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
      msg, lua_tostring(L, -1));
   exit(1);
}

static int l_doubler (lua_State *L) 
{
   double d = lua_tonumber(L, 1);  /* get argument */
   lua_pushnumber(L, d*2);  /* push result */
   return 1;  /* number of results */
}

static int l_registerButonClick(lua_State* L )
{
   size_t len = 0;
   const char* callbk = lua_tolstring(L, 1, &len);
   int widgetId = (int)lua_tointeger(L,2 );

   call_va(callbk,"i>", widgetId );

   return 0;  /* number of results */
}

typedef struct Tracker 
{
   size_t m_usage;
}Tracker;


static Tracker g_tracker;

static void *custom_lua_alloc (void *ud, void *ptr, size_t osize, size_t nsize)
{
   Tracker* pTracker = (Tracker*)ud;

   if (nsize == 0) 
   {
      if( osize != 0 )
      {
         pTracker->m_usage -= osize;
         //printf("Freed %d bytes\n", osize );
         luaReleaseMem(ptr);
      }
      return NULL;
   }
   else
   {
      pTracker->m_usage -= osize;
      pTracker->m_usage += nsize;
      //printf("Rellocation for %d bytes\n", nsize );
      return    luaReallocMem(ptr, nsize ); 
   }
}

int main(void)
{
   int status = -1;
   double sum = 0.0;
   double x = 2, y = 4.0;
   const char* str ="Prashant P0W";

   luaCreateMem(512, 2048);

   g_tracker.m_usage = 0;

   L = lua_newstate(custom_lua_alloc, &g_tracker );

   printf("current usage: %d bytes \n", g_tracker.m_usage);

   luaL_openlibs(L); /* Load Lua libraries */

   printf("current usage: %d bytes \n", g_tracker.m_usage);

   status = luaL_loadfile(L, "D:/lua-5.3.4/src/foo.lua");
   if (status) 
   {   
      bail( L, "Script Load Error luaL_loadfile failed" );
   }
   printf("current usage: %d bytes \n", g_tracker.m_usage);

   if (lua_pcall(L, 0, 0, 0))
   {  /* PRIMING RUN. FORGET THIS AND YOU'RE TOAST */
      /* Error out if Lua file has an error */
      bail(L, "lua_pcall() failed");          
   }

   printf("current usage: %d bytes \n", g_tracker.m_usage);

   lua_pushcfunction(L, l_doubler);
   lua_setglobal(L, "mydoubler");

   lua_pushcfunction(L, l_registerButonClick);
   lua_setglobal(L, "registerButonClick");

   call_va( "lua_fun",  "dd>d", x, y, &sum) ;
   printf( "Result %.6f\n",sum);

   call_va( "lua_test", "s>", str );

   printf("current usage: %d bytes \n", g_tracker.m_usage);

   lua_close(L);   /* Cya, Lua */

   printf("current usage: %d bytes \n", g_tracker.m_usage);

   luaDestroyMem();

   return 0;
}