#ifndef MUDUO_LUA_WORLD_PROCFS_H
#define MUDUO_LUA_WORLD_PROCFS_H

#include <boost/noncopyable.hpp>
namespace boost
{
  std::size_t hash_value(const muduo::string& x);
}
#include <boost/ptr_container/ptr_unordered_map.hpp>

#include <muduo/base/FileUtil.h>
#include <muduo/base/Logging.h>

using muduo::string;

namespace boost
{
  inline std::size_t hash_value(const muduo::string& x)
  {
      return hash_range(x.begin(), x.end());
  }
}

// FIXME: close files when not used.
class ProcFs : boost::noncopyable
{
 public:
  const char* readall(const char* filename, int* size)
  {
    muduo::FileUtil::ReadSmallFile* file = getFile(filename);
    if (file->readToBuffer(size) == 0)
    {
      return file->buffer();
    }
    else
    {
      *size = 0;
      return "";
    }
  }

 private:
  muduo::FileUtil::ReadSmallFile* getFile(string filename) // for insert(string&, T*)
  {
    ProcFileMap::iterator it = procFiles_.find(filename);
    if (it == procFiles_.end())
    {
      procFiles_.insert(filename, new muduo::FileUtil::ReadSmallFile(filename));
    }
    it = procFiles_.find(filename);
    assert(it != procFiles_.end());
    return it->second;
  }

  typedef boost::ptr_unordered_map<string, muduo::FileUtil::ReadSmallFile> ProcFileMap;
  ProcFileMap procFiles_;
};
#endif
