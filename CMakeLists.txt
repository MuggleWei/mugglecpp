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

# mugglec
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/mugglec)

# cmake
include(${CMAKE_CURRENT_LIST_DIR}/thirdparty/mugglec/cmake/muggle_utils.cmake)

# options
option(MUGGLE_CPP_ABANDON_LOG_MACRO "mugglecpp don't define LOG_* macro" OFF)
option(MUGGLE_CPP_BUILD_SHARED_LIB "mugglecpp build shared library" ON)
option(MUGGLE_CPP_BUILD_STATIC_PIC "mugglecpp build static library with position independent code flag" ON)
option(MUGGLE_CPP_BUILD_EXAMPLE "mugglecpp build examples" OFF)

if (MUGGLE_CPP_BUILD_SHARED_LIB)
	set(MUGGLE_CPP_LIB_TYPE SHARED)
else()
	set(MUGGLE_CPP_LIB_TYPE STATIC)
endif()

if (MUGGLE_CPP_ABANDON_LOG_MACRO)
	set(MUGGLE_CPP_USE_LOG_MACRO 0)
else()
	set(MUGGLE_CPP_USE_LOG_MACRO 1)
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
message("-- option MUGGLE_CPP_ABANDON_LOG_MACRO ${MUGGLE_CPP_ABANDON_LOG_MACRO}")
message("-- option MUGGLE_CPP_BUILD_SHARED_LIB ${MUGGLE_CPP_BUILD_SHARED_LIB}")
message("-- option MUGGLE_CPP_BUILD_STATIC_PIC ${MUGGLE_CPP_BUILD_STATIC_PIC}")
message("-- option MUGGLE_CPP_BUILD_EXAMPLE ${MUGGLE_CPP_BUILD_EXAMPLE}")

# include directories
include_directories(
	${CMAKE_CURRENT_LIST_DIR}
	${CMAKE_CURRENT_LIST_DIR}/thirdparty/mugglec/
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
	MUGGLE_CPP_USE_LOG_MACRO=${MUGGLE_CPP_USE_LOG_MACRO}
)
if (MUGGLE_CPP_BUILD_SHARED_LIB)
	target_compile_definitions(${muggle_cpp}
		PUBLIC MUGGLE_CPP_USE_DLL
		PRIVATE MUGGLE_CPP_EXPORTS 
	)
endif()

target_link_libraries(${muggle_cpp} ${muggle_c})
add_dependencies(${muggle_cpp} ${muggle_c})

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
endfunction()

# example
if (${MUGGLE_CPP_BUILD_EXAMPLE})
	message("---------------------- example ----------------------")
	SUBDIRLIST(example_dirs ${CMAKE_CURRENT_LIST_DIR}/example)
	FOREACH(subdir ${example_dirs})
		add_example(${subdir} ${CMAKE_CURRENT_LIST_DIR}/example/${subdir})
	ENDFOREACH()
endif()
