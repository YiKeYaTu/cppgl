file(GLOB_RECURSE FOUNDS_FILES *.cpp)
file(GLOB_RECURSE HEADER_FILES *.hpp)

add_library( cppgl ${HEADER_FILES} ${FOUNDS_FILES} )
target_link_libraries( cppgl
    glad
    glfw
    assimp
)