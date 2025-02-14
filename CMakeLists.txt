# CMakeList.txt : CMake project for UnityAprilTags, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.22)
project(UnityAprilTags VERSION 1.0.0 LANGUAGES C)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option(BUILD_EXAMPLES "Build example executables" OFF)
option(ASAN "Use AddressSanitizer for debug builds to detect memory issues" OFF)
option(BUILD_PYTHON_WRAPPER OFF)

include(FetchContent)
FetchContent_Declare(
	apriltag
	GIT_REPOSITORY https://github.com/AprilRobotics/apriltag.git
	GIT_TAG        v3.4.2
)
FetchContent_MakeAvailable(apriltag)
set_target_properties(apriltag PROPERTIES POSITION_INDEPENDENT_CODE ON)

if (IOS)
	set(CMAKE_XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED "NO")
	set(LIBRARY_TARGET_TYPE STATIC)
else()
	set(LIBRARY_TARGET_TYPE SHARED)
endif()

if (CMAKE_C_COMPILER_ID MATCHES "Clang")
	target_compile_options(apriltag PRIVATE -Wno-shorten-64-to-32)
endif()

# Add source to this project's executable.
add_library (UnityAprilTags ${LIBRARY_TARGET_TYPE} "UnityAprilTags.c")
set_target_properties(UnityAprilTags PROPERTIES PUBLIC_HEADER "UnityAprilTags.h")

# Embed the apriltag library directly into this one
# This is done instead of linking so that static versions of the UnityAprilTags library are standalone
target_sources(UnityAprilTags PRIVATE $<TARGET_OBJECTS:apriltag>)
target_include_directories(UnityAprilTags PRIVATE $<TARGET_PROPERTY:apriltag,INTERFACE_INCLUDE_DIRECTORIES>)

# TODO: Add tests and install targets if needed.
install(TARGETS UnityAprilTags
	EXPORT UnityAprilTagsTargets
)

install(EXPORT UnityAprilTagsTargets
	FILE UnityAprilTagsTargets.cmake
	NAMESPACE UnityAprilTags::
	DESTINATION lib/cmake/UnityAprilTags
)