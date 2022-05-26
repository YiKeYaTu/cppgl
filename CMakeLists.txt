cmake_minimum_required(VERSION 3.21)
project(cppgl)

set(CMAKE_CXX_STANDARD 17)

include_directories( src )
include_directories( 3rdparty/glad/include )

add_subdirectory( 3rdparty )
add_subdirectory( example )
