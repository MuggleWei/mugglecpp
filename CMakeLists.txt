cmake_minimum_required (VERSION 3.0.2)
project(mugglecpp)

# set compile parameter
if (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra")
elseif (${CMAKE_CXX_COMPILER_ID} MATCHES Clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -Wall -Wextra -Wno-missing-field-initializers")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS=1 -D_UNICODE -DUNICODE)
	add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
	add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
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
if (BUILD_SHARED_LIBS)
	set(MUGGLE_CPP_BUILD_SHARED_LIB_DEFAULT ON)
else(BUILD_SHARED_LIBS)
	set(MUGGLE_CPP_BUILD_SHARED_LIB_DEFAULT OFF)
endif()

option(MUGGLE_CPP_BUILD_SHARED_LIB "mugglecpp build shared library" ${MUGGLE_CPP_BUILD_SHARED_LIB_DEFAULT})
option(MUGGLE_CPP_BUILD_STATIC_PIC "mugglecpp build static library with position independent code flag" ON)
option(MUGGLE_CPP_BUILD_EXAMPLE "mugglecpp build examples" OFF)
option(MUGGLE_CPP_DOWNLOAD_MUGGLEC "mugglecpp build with download mugglec source" OFF)

################################
# mugglec
set(mugglec_ver 1.0.2)
if (MUGGLE_CPP_DOWNLOAD_MUGGLEC)
	include(FetchContent)
	set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/_deps)

	set(MUGGLE_BUILD_TRACE OFF CACHE BOOL "")
	set(MUGGLE_BUILD_SHARED_LIB ${MUGGLE_CPP_BUILD_SHARED_LIB_DEFAULT} CACHE BOOL "")
	set(MUGGLE_BUILD_STATIC_PIC ON CACHE BOOL "")
	set(MUGGLE_BUILD_BENCHMARK OFF CACHE BOOL "")
	set(MUGGLE_BUILD_TESTING OFF CACHE BOOL "")
	set(MUGGLE_BUILD_EXAMPLE OFF CACHE BOOL "")

	message("# fetch mugglec")
	FetchContent_Declare(
		mugglec
		GIT_REPOSITORY https://github.com/MuggleWei/mugglec.git
		GIT_TAG v${mugglec_ver}
		GIT_SHALLOW TRUE
		)
	FetchContent_MakeAvailable(mugglec)
	set(MUGGLEC_LIBRARIES mugglec)
else()
	message("# find package mugglec")
	find_package(mugglec ${mugglec_ver} REQUIRED)
	if (NOT mugglec_FOUND)
		message(FATAL_ERROR "failed found mugglec")
	endif()
endif()

# cmake
include(${CMAKE_CURRENT_LIST_DIR}/cmake/muggle_utils.cmake)

################################
# projects
if (MUGGLE_CPP_BUILD_SHARED_LIB)
	set(MUGGLE_CPP_LIB_TYPE SHARED)
	set(MUGGLE_CPP_USE_DLL ON)
else()
	set(MUGGLE_CPP_LIB_TYPE STATIC)
	set(MUGGLE_CPP_USE_DLL OFF)
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

# mugglecpp
set(muggle_cpp mugglecpp)

set(mugglecpp_generated_dir ${CMAKE_CURRENT_BINARY_DIR}/generated)
configure_file(
	"${CMAKE_CURRENT_LIST_DIR}/muggle/cpp/mugglecpp_config.h.in"
	"${mugglecpp_generated_dir}/muggle/cpp/mugglecpp_config.h")

muggle_add_project(${muggle_cpp} ${CMAKE_CURRENT_LIST_DIR}/muggle ${MUGGLE_CPP_LIB_TYPE})
target_include_directories(${muggle_cpp} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>
	$<BUILD_INTERFACE:${mugglecpp_generated_dir}>
	$<INSTALL_INTERFACE:include>)

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
)
if (MUGGLE_CPP_BUILD_SHARED_LIB)
	target_compile_definitions(${muggle_cpp}
		#PUBLIC MUGGLE_CPP_USE_DLL
		PRIVATE MUGGLE_CPP_EXPORTS 
	)
endif()

target_link_libraries(${muggle_cpp} mugglec)
if (MUGGLE_CPP_DOWNLOAD_MUGGLEC)
	add_dependencies(${muggle_cpp} mugglec)
endif()

# install and add export configuration
include(GNUInstallDirs)

set(mugglecpp_export_dir "${CMAKE_INSTALL_LIBDIR}/cmake/mugglecpp")
install(TARGETS ${muggle_cpp}
	EXPORT mugglecppTargets
	RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
	ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
	LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}")
install(EXPORT mugglecppTargets
	FILE mugglecppTargets.cmake
	DESTINATION ${mugglecpp_export_dir})
muggle_install_headers(
	"${CMAKE_CURRENT_LIST_DIR}/muggle" "include/muggle")
muggle_install_headers(
	"${mugglecpp_generated_dir}/muggle" "include/muggle")

include(CMakePackageConfigHelpers)
configure_package_config_file(
	"${CMAKE_CURRENT_LIST_DIR}/cmake/mugglecppConfig.cmake.in"
    "${mugglecpp_generated_dir}/mugglecppConfig.cmake"
    INSTALL_DESTINATION ${mugglecpp_export_dir}
    NO_SET_AND_CHECK_MACRO
    NO_CHECK_REQUIRED_COMPONENTS_MACRO)
write_basic_package_version_file(
    "${mugglecpp_generated_dir}/mugglecppConfigVersion.cmake"
	VERSION ${MUGGLE_CPP_VERSION}
    COMPATIBILITY SameMajorVersion
)
install(FILES
	"${mugglecpp_generated_dir}/mugglecppConfig.cmake"
	"${mugglecpp_generated_dir}/mugglecppConfigVersion.cmake"
	DESTINATION ${mugglecpp_export_dir})

# configure and install pkgconfig file
configure_file(
	"${CMAKE_CURRENT_LIST_DIR}/cmake/mugglecpp.pc.in"
	"${mugglecpp_generated_dir}/mugglecpp.pc" @ONLY)
install(FILES
	"${mugglecpp_generated_dir}/mugglecpp.pc"
	DESTINATION "${CMAKE_INSTALL_LIBDIR}/pkgconfig")

# cpack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_LIST_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${MUGGLE_CPP_VER_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${MUGGLE_CPP_VER_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${MUGGLE_CPP_VER_PATCH})
set(CPACK_PACKAGE_CONTACT "Muggle Wei <mugglewei@gmail.com>")
set(CPACK_SOURCE_GENERATOR "TGZ")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE "https://github.com/MuggleWei/mugglecpp")
include(CPack)

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
		PRIVATE MUGGLE_HOLD_LOG_MACRO
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
