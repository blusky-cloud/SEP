#copy pasted from XMLAdapterBranch tests/dcn/Cmakelists.txt

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        master
)

FetchContent_Declare(
  flecs
  GIT_REPOSITORY https://github.com/SanderMertens/flecs.git
  GIT_TAG        v2.3.2
)

FetchContent_MakeAvailable(googletest flecs)

add_executable (test_executable
    main.cpp
    wrap.cpp
)

target_link_libraries(test_executable gtest gtest_main Model XML flecs pthread)
target_include_directories(
    test_executable PUBLIC 
    ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
    ${flecs_INCLUDE_DIRS}
    ${googletest_INCLUDE_DIRS}
)