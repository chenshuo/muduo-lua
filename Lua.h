#ifndef MUDUO_LUA_H
#define MUDUO_LUA_H

#include <lua/lua.h>
#include <lua/lualib.h>
#include <lua/lauxlib.h>

#include <muduo/base/StringPiece.h>

#include <boost/noncopyable.hpp>

using muduo::string;

class Lua : boost::noncopyable
{
 public:

  Lua()
    : l_(luaL_newstate())
  {
    luaL_openlibs(l_);
  }

  ~Lua()
  {
    lua_close(l_);
  }

  lua_State* state()
  {
    return l_;
  }

  void reset()
  {
    lua_close(l_);
    l_ = luaL_newstate();
    luaL_openlibs(l_);
  }

  int loadstring(muduo::StringPiece str)
  {
    return luaL_loadstring(l_, str.data());
  }

  int pcall(int nargs, int nresults)
  {
    return lua_pcall(l_, nargs, nresults, 0);
  }

  int gettop()
  {
    return lua_gettop(l_);
  }

  void pop(int n = 1)
  {
    lua_pop(l_, n);
  }

  string tostring(int index = -1)
  {
    return lua_tolstring(l_, -1, NULL);
  }

  string popstring()
  {
    string result = tostring();
    pop();
    return result;
  }

  string callStringFunc(const char* func)
  {
    string result;
    lua_getglobal(l_, func);
    // FIXME: check
    lua_pcall(l_, 0, 1, 0);
    // FIXME: check
    if (lua_isstring(l_, -1))
    {
      result = tostring();
    }
    pop();
    return result;
  }

  string callStringFunc(const char* func, const char* arg)
  {
    string result;
    lua_getglobal(l_, func);
    lua_pushstring(l_, arg);

    // FIXME: check
    lua_pcall(l_, 1, 1, 0);
    // FIXME: check
    if (lua_isstring(l_, -1))
    {
      result = tostring();
    }
    pop();
    return result;
  }
 private:
  lua_State* l_;
};

#endif
