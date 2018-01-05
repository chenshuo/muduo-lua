
add_executable(hello hello.cc)
target_link_libraries(hello ${muduo_net})
target_link_libraries(hello ${muduo_base})
target_link_libraries(hello ${LUA_LIBRARIES})
target_link_libraries(hello pthread rt)

