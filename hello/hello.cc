#include <Lua.h>

#include <muduo/base/FileUtil.h>
#include <muduo/base/Logging.h>

#include <stdio.h>

using namespace muduo;

string loadFile(const char* filename)
{
  string content;
  FileUtil::readFile(filename, 1024*1024, &content);
  return content;
}

int l_now(lua_State* L)
{
  lua_pushstring(L, Timestamp::now().toFormattedString().c_str());
  return 1;
}

int main()
{
  Lua lua;
  string luaprogram = loadFile("hello.lua");
  if (luaprogram.empty())
  {
    LOG_ERROR << "Can not read hello.lua";
  }
  else
  {
    // int top = lua.gettop();
    lua_register(lua.state(), "now", l_now);

    if (lua.loadstring(luaprogram) == 0 &&
        lua.pcall(0, LUA_MULTRET) == 0)
    {
      LOG_INFO << lua.callStringFunc("hello");
      LOG_INFO << lua.callStringFunc("callback");
    }
    else
    {
      LOG_ERROR << lua.popstring();
    }
    // assert(lua.gettop() == top);
  }

}
