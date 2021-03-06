cmake_minimum_required (VERSION 3.0.2)
project(mugglecpp)

# set compile parameter
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -Wno-missing-field-initializers")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_UNICODE -DUNICODE)
endif()

# set standard and print features
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# for vim plugin - YCM
if (NOT ${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# set output directory
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# set use folder in vs
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# options
option(MUGGLE_CPP_BUILD_SHARED_LIB "mugglecpp build shared library" ON)
option(MUGGLE_CPP_BUILD_STATIC_PIC "mugglecpp build static library with position independent code flag" ON)
option(MUGGLE_CPP_BUILD_EXAMPLE "mugglecpp build examples" OFF)
option(MUGGLE_CPP_DOWNLOAD_MUGGLEC "mugglecpp download mugglec" ON)

################################
# mugglec

if (MUGGLE_CPP_DOWNLOAD_MUGGLEC)
	# Download and unpack mugglec at configure time
	configure_file(
		${CMAKE_CURRENT_LIST_DIR}/cmake/mugglec.cmake.in
		${CMAKE_BINARY_DIR}/_deps/mugglec-download/CMakeLists.txt)
	execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/_deps/mugglec-download)
	if (result)
		message(FATAL_ERROR "cmake step for mugglec failed: ${result}")
	endif()
	execute_process(COMMAND ${CMAKE_COMMAND} --build .
		RESULT_VARIABLE result
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/_deps/mugglec-download)
	if (result)
		message(FATAL_ERROR "build step for mugglec failed: ${result}")
	endif()

	# set mugglec compile options
	set(MUGGLE_BUILD_TRACE OFF CACHE BOOL "")
	set(MUGGLE_BUILD_SHARED_LIB ON CACHE BOOL "")
	set(MUGGLE_BUILD_STATIC_PIC ON CACHE BOOL "")
	set(MUGGLE_BUILD_BENCHMARK OFF CACHE BOOL "")
	set(MUGGLE_BUILD_TESTING OFF CACHE BOOL "")
	set(MUGGLE_BUILD_EXAMPLE OFF CACHE BOOL "")

	# add mugglec to build
	add_subdirectory(
		${CMAKE_BINARY_DIR}/_deps/mugglec-src
		${CMAKE_BINARY_DIR}/_deps/mugglec-build)

	# include directories
	include_directories(
		${CMAKE_BINARY_DIR}/_deps/mugglec-src
	)
endif()

################################
# projects

# cmake
include(${CMAKE_CURRENT_LIST_DIR}/cmake/muggle_utils.cmake)

if (MUGGLE_CPP_BUILD_SHARED_LIB)
	set(MUGGLE_CPP_LIB_TYPE SHARED)
else()
	set(MUGGLE_CPP_LIB_TYPE STATIC)
endif()

# version
file(STRINGS "version.txt" mugglecpp_version)

string(REPLACE "-" ";" mugglecpp_semver_ext ${mugglecpp_version})
list(GET mugglecpp_semver_ext 0 mugglecpp_semver)
string(REPLACE "." ";" mugglecpp_semver_list ${mugglecpp_semver})

list(GET mugglecpp_semver_list 0 MUGGLE_CPP_VER_MAJOR)
list(GET mugglecpp_semver_list 1 MUGGLE_CPP_VER_MINOR)
list(GET mugglecpp_semver_list 2 MUGGLE_CPP_VER_PATCH)

set(MUGGLE_CPP_VERSION "${mugglecpp_version}")
set(MUGGLE_CPP_SOVERSION "${MUGGLE_CPP_VER_MAJOR}")

# output options
message("-- mugglecpp version: ${MUGGLE_CPP_VERSION}")
message("-- option MUGGLE_CPP_BUILD_SHARED_LIB ${MUGGLE_CPP_BUILD_SHARED_LIB}")
message("-- option MUGGLE_CPP_BUILD_STATIC_PIC ${MUGGLE_CPP_BUILD_STATIC_PIC}")
message("-- option MUGGLE_CPP_BUILD_EXAMPLE ${MUGGLE_CPP_BUILD_EXAMPLE}")
message("-- option MUGGLE_CPP_DOWNLOAD_MUGGLEC ${MUGGLE_CPP_DOWNLOAD_MUGGLEC}")

# include directories
include_directories(
	${CMAKE_CURRENT_LIST_DIR}
)

# mugglecpp
set(muggle_c mugglec)
set(muggle_cpp mugglecpp)
muggle_add_project(${muggle_cpp} ${CMAKE_CURRENT_LIST_DIR}/muggle ${MUGGLE_CPP_LIB_TYPE})

set_target_properties(${muggle_cpp} PROPERTIES 
	VERSION ${MUGGLE_CPP_VERSION}
	SOVERSION ${MUGGLE_CPP_SOVERSION}
	DEBUG_POSTFIX d
)
if ((NOT ${MUGGLE_CPP_BUILD_SHARED_LIB}) AND (${MUGGLE_CPP_BUILD_STATIC_PIC}))
	set_target_properties(${muggle_cpp} PROPERTIES
		POSITION_INDEPENDENT_CODE ON
	)
endif()

target_compile_definitions(${muggle_cpp} PUBLIC
	MUGGLE_CPP_SEMVER=${MUGGLE_CPP_VERSION}
	PRIVATE MUGGLE_CPP_USE_LOG_MACRO=1
)
if (MUGGLE_CPP_BUILD_SHARED_LIB)
	target_compile_definitions(${muggle_cpp}
		PUBLIC MUGGLE_CPP_USE_DLL
		PRIVATE MUGGLE_CPP_EXPORTS 
	)
endif()

target_link_libraries(${muggle_cpp} ${muggle_c})
add_dependencies(${muggle_cpp} ${muggle_c})
install(TARGETS ${muggle_cpp}
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib/static
)
muggle_install_headers(${CMAKE_CURRENT_LIST_DIR}/muggle include/muggle)

# functions
function(add_example name folder)
	message("add example ${name} ${folder}")
	
	set(name example_${name})

	file(GLOB tmp_h ${folder}/*.h)
	file(GLOB tmp_c ${folder}/*.c)
	file(GLOB tmp_cpp ${folder}/*.cpp)
	file(GLOB tmp_cc ${folder}/*.cc)

	if (WIN32)
		add_executable(${name} ${tmp_h} ${tmp_c} ${tmp_cpp} ${tmp_cc})
		set_target_properties(${name}
			PROPERTIES
			FOLDER "example"
			VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)"
		)
	else()
		add_executable(${name} ${tmp_c} ${tmp_cpp} ${tmp_cc})
	endif(WIN32)
	add_dependencies(${name} ${muggle_cpp})
	target_link_libraries(${name}
		${muggle_cpp}
	)
	target_compile_definitions(${name}
		PRIVATE MUGGLE_CPP_USE_LOG_MACRO=1
	)
endfunction()

# example
if (${MUGGLE_CPP_BUILD_EXAMPLE})
	message("---------------------- example ----------------------")
	SUBDIRLIST(example_dirs ${CMAKE_CURRENT_LIST_DIR}/example)
	FOREACH(subdir ${example_dirs})
		add_example(${subdir} ${CMAKE_CURRENT_LIST_DIR}/example/${subdir})
	ENDFOREACH()
endif()
