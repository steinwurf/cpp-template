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

file(GLOB_RECURSE {{cookiecutter.name}}_sources ./src/*.cpp)

add_executable({{cookiecutter.name}} ${{{cookiecutter.name}}_sources})
