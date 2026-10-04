# TODO: Add support for other compilers
add_library(pans_options INTERFACE)

target_compile_options(pans_options INTERFACE
	-Wall
	-Wextra
	-Wpedantic
)

option(PANS_ENABLE_COVERAGE "Enable code coverage" OFF)
mark_as_advanced(PANS_ENABLE_COVERAGE)

if(PANS_ENABLE_COVERAGE)
	target_compile_options(pans_options INTERFACE
		$<$<CONFIG:Debug>:--coverage>
	)
	target_link_options(pans_options INTERFACE
		$<$<CONFIG:Debug>:--coverage>
	)
endif()

# TODO: Add sanitizer options
