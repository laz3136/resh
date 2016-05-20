project(format)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_library(format SHARED format.cpp)

install(TARGETS format DESTINATION lib)
install(FILES format.h DESTINATION include)

