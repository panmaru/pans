include(FetchContent)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG 063de7e9578f82b369302001269680b4b1553359 # v1.18.0
	FIND_PACKAGE_ARGS NAMES GTest
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(pans_tests
	macros_test.cpp
)

target_link_libraries(pans_tests PRIVATE
	pans
	pans_options
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(pans_tests)
