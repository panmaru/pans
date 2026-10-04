set(PANS_SOURCES
	src/main.cpp
)

set(PANS_HEADERS
	include/pans/macros.h
)

add_library(pans STATIC ${PANS_SOURCES})

target_sources(pans PUBLIC
	FILE_SET HEADERS
	BASE_DIRS include
	FILES ${PANS_HEADERS}
)

target_include_directories(pans
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(pans PRIVATE
	pans_options
)

# TODO: Add support for other compilers
target_compile_options(pans PRIVATE
	-Werror
)

install(TARGETS pans
	EXPORT pansTargets
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
