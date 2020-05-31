add_executable(allocator allocator.cpp)
target_compile_features(allocator PRIVATE cxx_std_17)
target_link_libraries(allocator PRIVATE CONAN_PKG::gtest BlockAllocator)
add_test(NAME allocatorTest WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/bin COMMAND allocator ${CMAKE_CURRENT_LIST_DIR})
