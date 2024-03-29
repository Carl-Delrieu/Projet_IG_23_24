project(TP-anim)

cmake_minimum_required(VERSION 2.8.11)

if (APPLE)
# CMake 2.8.12 and newer has support for using @rpath in a target’s install
# name. This was enabled by setting the target property MACOSX_RPATH. The
# @rpath in an install name is a more flexible and powerful mechanism than
# @executable_path or @loader_path for locating shared libraries.

# CMake 3.0 and later prefer this property to be ON by default. Projects wanting
# @rpath in a target’s install name may remove any setting of the
# INSTALL_NAME_DIR and CMAKE_INSTALL_NAME_DIR variables.

# This policy was introduced in CMake version 3.0. CMake version 3.0.2 warns
# when the policy is not set and uses OLD behavior. Use the cmake_policy command
# to set it to OLD or NEW explicitly.
    cmake_policy(SET CMP0042 NEW)
endif(APPLE)

# CMake setups
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Build options options.

if ( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif()


# These paths need to be synchronized with FindRadium.cmake
set(BUNDLE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bundle-${CMAKE_CXX_COMPILER_ID})
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUNDLE_DIRECTORY}/${CMAKE_BUILD_TYPE}/bin)
set(EXECUTABLE_OUTPUT_PATH         ${BUNDLE_DIRECTORY}/${CMAKE_BUILD_TYPE}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUNDLE_DIRECTORY}/${CMAKE_BUILD_TYPE}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUNDLE_DIRECTORY}/${CMAKE_BUILD_TYPE}/lib)

# guard against in-source builds (source: Eigen)
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()


# Set the compiler flags.
include(CompileFlags)

if ( NOT CMAKE_PREFIX_PATH )
  set( CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR} )
endif()


# Win32 stuff
if (MSVC OR MSVC_IDE)
  # Use November CTP 2013 (constexpr and other non implemented stuff in the 2013 version)
    if (MSVC_VERSION LESS 1800)
        message(FATAL_ERROR
                "This project requires C++11 stuff provided only with "
                "Microsoft Visual C++ Compiler Nov 2013 CTP (v120_CTP_Nov2013).")
    endif(MSVC_VERSION LESS 1800)

    if (MSVC_VERSION EQUAL 1800)
        #set(CMAKE_GENERATOR_TOOLSET "CTP_Nov2013" CACHE STRING "Platform Toolset" FORCE)
    endif (MSVC_VERSION EQUAL 1800)

    # Copy libs / targets in the correct directories
    if ("${CMAKE_GENERATOR}" STREQUAL "NMake Makefiles")
        set(PDB_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    else()
        foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
            string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
            set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
            set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
            set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
        endforeach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    endif()
endif(MSVC OR MSVC_IDE)


# ----------------------------------------------------------------------------------------------------------------------
#   Main Libraries

################################################################################
# Assets                                                                       #
################################################################################
#
set(SHADER_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Shaders")

if(MSVC OR MSVC_IDE OR MINGW)
add_custom_target( main-assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${SHADER_DIR} "${EXECUTABLE_OUTPUT_PATH}/Shaders"
    COMMENT "Copying shaders and other ressources" VERBATIM
)
else()
    add_custom_target( main-assets
            COMMAND ${CMAKE_COMMAND} -E create_symlink ${SHADER_DIR} "${EXECUTABLE_OUTPUT_PATH}/Shaders"
            COMMENT "Linking (symlink) shaders and other ressources" VERBATIM
            )
endif()



set(app_target main-app)

find_package(OpenGL     REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm  REQUIRED)
find_package(glbinding  REQUIRED)
find_package(globjects  REQUIRED)
 
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB app_sources *.cpp)
file(GLOB app_headers *.h *.hpp)
file(GLOB app_inlines *.inl)

add_executable(
    ${app_target}
    ${app_sources}
    ${app_headers}
    ${app_inlines}
    )

target_link_libraries(
    ${app_target}
    PUBLIC
    glfw   globjects::globjects
    )

    add_dependencies( ${app_target} main-assets)



if (MSVC)
    #This will work from CMake 3.6
    set_property( DIRECTORY ${CMAKE_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${app_target})
    set_property( TARGET ${app_target} PROPERTY IMPORTED_LOCATION "${BINARY_OUTPUT_PATH}" )
endif(MSVC)
