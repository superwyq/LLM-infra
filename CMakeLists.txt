cmake_minimum_required(VERSION 3.10)
project(matrix_multiplication  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_BUILD_TYPE "Debug")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O1")


set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

include_directories(/usr/local/include ./include)
link_directories(/usr/local/lib ./lib)

# 查找项目目录下所有的 cpp 文件并将它们存储在一个变量中
aux_source_directory(${PROJECT_SOURCE_DIR}/src SRCS)
file(GLOB INC_PATH ${PROJECT_SOURCE_DIR}/include/*)
list(APPEND INCS ${INC_PATH})


execute_process(COMMAND mkdir -p ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${CMAKE_BUILD_TYPE})

# 添加一个可执行文件的目标，并链接所有找到的源文件
add_executable(matrix_multiplication main.cpp ${INCS} ${SRCS})
target_link_libraries(matrix_multiplication pthread)
