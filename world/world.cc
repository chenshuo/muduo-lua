#include <Lua.h>

#include <muduo/base/FileUtil.h>
#include <muduo/base/Logging.h>
#include <muduo/net/inspect/Inspector.h>
#include <muduo/net/EventLoop.h>

#include <boost/bind.hpp>
#include <stdio.h>

using namespace muduo;
using namespace muduo::net;

string loadFile(const char* filename)
{
  string content;
  FileUtil::readFile(filename, 100*1024*1024, &content);
  return content;
}

string reload(Lua* lua)
{
  string luaprogram = loadFile("world.lua");
  if (luaprogram.empty())
  {
    return "Can not read world.lua";
  }
  else
  {
    if (lua->loadstring(luaprogram) == 0 &&
        lua->pcall(0, LUA_MULTRET) == 0)
    {
      return "ok";
    }
    else
    {
      return lua->popstring();
    }
  }
}

int main(int argc, char* argv[])
{
  Lua lua;
  reload(&lua);
  EventLoop loop;
  Inspector ins(&loop, InetAddress(12345), "world");
  ins.add("world", "basic", boost::bind(&Lua::callStringFunc, &lua, "basic"), "basic info");
  ins.add("world", "reload", boost::bind(reload, &lua), "reload world.lua");
  loop.loop();
}
