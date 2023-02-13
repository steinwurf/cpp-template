cmake_minimum_required(VERSION 3.12)
project({{cookiecutter.name}} VERSION 0.0.0)

find_package(Python COMPONENTS Interpreter)

if(NOT DEFINED STEINWURF_RESOLVE)
    message(STATUS "Resolving dependencies...")
    set(RESOLVE_CMD ${Python_EXECUTABLE} waf resolve ${STEINWURF_RESOLVE_OPTIONS})

    message(STATUS "Running: ${RESOLVE_CMD}")
    execute_process(
        COMMAND ${RESOLVE_CMD}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        RESULT_VARIABLE STATUS)

    if(STATUS AND NOT STATUS EQUAL 0)
        message(FATAL_ERROR "Failed: ${STATUS}")
    endif()

    set(STEINWURF_RESOLVE "${CMAKE_CURRENT_SOURCE_DIR}/resolve_symlinks")
    set(STEINWURF_TOP_NAME {{cookiecutter.name}})
endif()

file(GLOB_RECURSE project_sources ./src/*.cpp)


if(${PROJECT_NAME} STREQUAL ${STEINWURF_TOP_NAME})
    # Create static library
    add_library({{cookiecutter.binary_name}} STATIC ${project_sources})

    # Install library
    install(
        FILES $<TARGET_FILE:{{cookiecutter.binary_name}}>
        DESTINATION lib
        COMPONENT library)
else()
     # Create object library
     add_library({{cookiecutter.binary_name}} OBJECT ${project_sources})

     # Add this library to a global list of steinwurf object libraries
     set_property(GLOBAL APPEND PROPERTY steinwurf::object_libraries
         steinwurf::{{cookiecutter.name}}) # Create object library


endif()

target_include_directories({{cookiecutter.name}} INTERFACE src)
target_compile_features({{cookiecutter.name}} PUBLIC cxx_std_14)
add_library(steinwurf::{{cookiecutter.name}} ALIAS {{cookiecutter.name}})

install(
    DIRECTORY ./src/{{cookiecutter.name}}
    DESTINATION include
    COMPONENT headers
    FILES_MATCHING
    PATTERN *.hpp
    PATTERN ./src/{{cookiecutter.name}}/detail EXCLUDE)

# Is top level project?
if(${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
    # Build testing
    option(BUILD_TESTING "Build tests" ON)

    if(${BUILD_TESTING})
        # gtest
        if(NOT TARGET steinwurf::gtest)
            add_subdirectory("${STEINWURF_RESOLVE}/gtest" EXCLUDE_FROM_ALL)
        endif()

        file(GLOB_RECURSE test_sources test/*.cpp)
        add_executable({{cookiecutter.binary_name}}_test ${test_sources})
        target_link_libraries({{cookiecutter.binary_name}}_test
                steinwurf::gtest
                steinwurf::{{cookiecutter.name}})
    endif()

    add_executable(example examples/example.cpp)
    target_link_libraries(example steinwurf::{{cookiecutter.name}})
endif()
