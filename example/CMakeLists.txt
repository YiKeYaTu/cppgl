add_executable( dev dev/main.cpp)
add_executable( alphaBlend alphaBlend/main.cpp )

target_link_libraries( dev cppgl )
target_link_libraries( alphaBlend cppgl )