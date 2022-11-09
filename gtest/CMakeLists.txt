
enable_testing()

# add_test(NAME template_test
#     COMMAND template_test --gtest_output=xml:test_results.xml)

add_executable(template_test template_test.cpp)
target_link_libraries(template_test PUBLIC gtest gmock gtest_main)

target_include_directories(template_test
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)
