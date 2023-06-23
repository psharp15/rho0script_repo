project(rho0repo)

cmake_minimum_required (VERSION 2.6)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules")

find_package(ROOT REQUIRED)

add_subdirectory(compiled_programs)
