include_directories(${ROOT_INCLUDE_DIR})
# pulling all root

add_executable(analysis_1p analysis_1p.cpp) #build program by compiling that program

target_link_libraries(analysis_1p ${ROOT_LIBRARIES})
