cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)


project(CloudPan)

# add_library(CloudPan SHARED 
#                 CloudPan.cpp)

add_executable(CloudPan CloudPan.cpp)
                
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")
find_package(MySQL REQUIRED)

target_include_directories(CloudPan PUBLIC  ${PROJECT_BINARY_DIR} ${MYSQL_INCLUDE_DIR})

target_link_libraries(CloudPan  ${MYSQL_LIB_DIR})

execute_process(COMMAND mysql_config --cflags
    OUTPUT_VARIABLE MYSQL_CFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND mysql_config --libs
    OUTPUT_VARIABLE MYSQL_LIBS OUTPUT_STRIP_TRAILING_WHITESPACE)

target_compile_options(CloudPan PUBLIC ${MYSQL_CFLAGS})

