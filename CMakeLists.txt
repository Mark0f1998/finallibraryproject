cmake_minimum_required(VERSION 3.8 FATAL_ERROR)
project(FinalLibraryProject)

add_executable(${PROJECT_NAME} main.cpp cpu_info.cpp cpu_info.hpp)

include(FindPkgConfig)
pkg_check_modules(LIBCPUID REQUIRED IMPORTED_TARGET libcpuid)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::LIBCPUID)
pkg_check_modules(NCURSES REQUIRED IMPORTED_TARGET ncurses)
target_link_libraries(${PROJECT_NAME} PRIVATE PkgConfig::NCURSES)

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_EXTENSIONS OFF)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
