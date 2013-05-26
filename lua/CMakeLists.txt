set(lua_SRCS
  lapi.c
  lcode.c
  lctype.c
  ldebug.c
  ldo.c
  ldump.c
  lfunc.c
  lgc.c
  llex.c
  lmem.c
  lobject.c
  lopcodes.c
  lparser.c
  lstate.c
  lstring.c
  ltable.c
  ltm.c
  lundump.c
  lvm.c
  lzio.c
  lauxlib.c
  lbaselib.c
  lbitlib.c
  lcorolib.c
  ldblib.c
  liolib.c
  lmathlib.c
  loslib.c
  lstrlib.c
  ltablib.c
  loadlib.c
  linit.c
  )
 
SET_SOURCE_FILES_PROPERTIES(${lua_SRCS} PROPERTIES LANGUAGE CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-conversion -Wno-old-style-cast ")
add_library(lua ${lua_SRCS})
target_link_libraries(lua dl)

SET_SOURCE_FILES_PROPERTIES(lua.c PROPERTIES LANGUAGE CXX)
add_executable(luai lua.c)
target_link_libraries(luai lua readline)

SET_SOURCE_FILES_PROPERTIES(luac.c PROPERTIES LANGUAGE CXX)
add_executable(luac luac.c)
target_link_libraries(luac lua)
