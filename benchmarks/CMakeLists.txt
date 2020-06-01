add_executable(benchAllocator benchmark.cpp)
target_compile_features(benchAllocator PRIVATE cxx_std_17)
target_link_libraries(benchAllocator PRIVATE CONAN_PKG::benchmark ArenaAllocator)

add_executable(access access.cpp)
target_compile_features(access PRIVATE cxx_std_17)
target_link_libraries(access PRIVATE CONAN_PKG::benchmark ArenaAllocator)

