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
  ins.add("world", "reload", boost::bind(reload, &lua), "reload world.lua");

  ins.add("world", "basic", boost::bind(&Lua::callStringFunc, &lua, "basic"), "basic info");
  ins.add("world", "stat", boost::bind(&Lua::callStringFunc, &lua, "stat"), "/proc/stat");
  ins.add("world", "loadavg", boost::bind(&Lua::callStringFunc, &lua, "loadavg"), "/proc/loadavg");
  ins.add("world", "cpuinfo", boost::bind(&Lua::callStringFunc, &lua, "cpuinfo"), "/proc/cpuinfo");
  ins.add("world", "version", boost::bind(&Lua::callStringFunc, &lua, "version"), "/proc/version");

  ins.add("world", "tcp",
      boost::bind(&Lua::callStringFunc, &lua, "readall", "/proc/net/tcp"), "/proc/net/tcp");

  loop.loop();
}
