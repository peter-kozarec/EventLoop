include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG release-1.12.1)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_unit_tests)
target_link_libraries(${PROJECT_NAME}_unit_tests GTest::gtest_main ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_unit_tests PRIVATE ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/src)

target_sources(${PROJECT_NAME}_unit_tests
        PRIVATE
            src/ptrqueuetst.cpp)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_unit_tests)