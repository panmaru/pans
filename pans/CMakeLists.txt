set(PANS_SOURCES
	src/main.cpp
)

set(PANS_PUBLIC_HEADERS
	include/pans/macros.h
)

set(PANS_PRIVATE_HEADERS
)

add_library(pans STATIC ${PANS_SOURCES})

include(GenerateExportHeader)
generate_export_header(pans
	EXPORT_FILE_NAME ${CMAKE_CURRENT_BINARY_DIR}/include/pans/pans_export.h
)

target_sources(pans
	PUBLIC
		FILE_SET public_headers
		TYPE HEADERS
		BASE_DIRS
			${CMAKE_CURRENT_SOURCE_DIR}/include
			${CMAKE_CURRENT_BINARY_DIR}/include
		FILES
			${PANS_PUBLIC_HEADERS}
			${CMAKE_CURRENT_BINARY_DIR}/include/pans/pans_export.h
	PRIVATE
		FILE_SET private_headers
		TYPE HEADERS
		BASE_DIRS
			${CMAKE_CURRENT_SOURCE_DIR}/src
		FILES
			${PANS_PRIVATE_HEADERS}
)

target_include_directories(pans
	PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
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
	FILE_SET public_headers DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
