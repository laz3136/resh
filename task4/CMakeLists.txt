project(ifmo_cpp_format)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_library(format format.cpp)
install(TARGETS format DESTINATION lib)
install(FILES format.h DESTINATION include)
