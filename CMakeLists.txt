cmake_minimum_required(VERSION 3.17)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)
cmake_minimum_required(VERSION 2.8)
find_package( Boost COMPONENTS filesystem system REQUIRED )

SET(BOOST_ROOT "/usr/local")
add_executable(untitled1 main.cpp)
