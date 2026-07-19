cmake_minimum_required(VERSION 3.28)

project(kv-store)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(kv-store src/main.cpp src/storage_engine.cpp src/wal.cpp)
add_executable(correctness_test tests/correctness_test.cpp src/storage_engine.cpp src/wal.cpp)
add_executable(recovery_write tests/recovery_write.cpp src/storage_engine.cpp src/wal.cpp)
add_executable(recovery_read tests/recovery_read.cpp src/storage_engine.cpp src/wal.cpp)
add_executable(bench benchmarks/bench.cpp src/storage_engine.cpp src/wal.cpp)

option(ENABLE_TSAN "Enable ThreadSanitizer" OFF)

if(ENABLE_TSAN)
    target_compile_options(kv-store PRIVATE -fsanitize=thread)
    target_link_options(kv-store PRIVATE -fsanitize=thread)
endif()

