function readall(filename)
  local f = assert(io.open(filename, "r"))
  local t = f:read("*all")
  f:close()
  return t
end

function hello()
  return "Hello, " .. _VERSION
end

function basic()
  return "Hello, " .. readproc("/proc/cpuinfo")
end

function stat()
  local stat = readall("/proc/stat")
  return stat
end

function loadavg()
  return readall("/proc/loadavg")
end

function cpuinfo()
  return readall("/proc/cpuinfo")
end

function version()
  return readall("/proc/version") .. readall("/proc/cmdline")
end
