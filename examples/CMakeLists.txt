set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

set (PROJECT_LINK_LIBS /lib/tstcrc.a)

include_directories(inc)
link_directories(${CMAKE_SOURCE_DIR}/lib)
file(GLOB SOURCES "*.cpp")

find_package(SDL2 REQUIRED)
include(FindPkgConfig)
pkg_check_modules(SDL2_Image REQUIRED IMPORTED_TARGET SDL2_image)
pkg_check_modules(SDL2_ttf REQUIRED IMPORTED_TARGET SDL2_ttf)

add_executable (${PROJECT_NAME}.out ${SOURCES})

TARGET_LINK_LIBRARIES(${PROJECT_NAME}.out PUBLIC crc PkgConfig::SDL2_Image PkgConfig::SDL2_ttf)
