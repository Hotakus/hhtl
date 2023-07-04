cmake_minimum_required(VERSION 3.20)
project(hhtl
        LANGUAGES C
        VERSION 1.0.0.0
        DESCRIPTION "Hotakus' Hash Table Lite"
        HOMEPAGE_URL https://github.com/Hotakus/hhtl
        )
set(CMAKE_C_STANDARD 11)

# 指定版本号的配置文件
configure_file(${PROJECT_SOURCE_DIR}/version.h.in ${PROJECT_SOURCE_DIR}/version.h)

#设置输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib) # 设置静态库文件目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib) # 动态库文件目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin) # 可执行文件目录

add_subdirectory(./src)
aux_source_directory(. SRC_ROOT)

if (HHTL_TEST)
    add_executable(hhtl ${SRC_ROOT})
else ()
    add_library(hhtl ${SRC_ROOT})
endif ()

target_link_libraries(hhtl htsrc)