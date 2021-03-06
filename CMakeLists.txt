# Work with CMake version minimum 3.10
cmake_minimum_required(VERSION 3.10)


# Project name and a few useful settings
project(algo 
	VERSION 0.0.1
	DESCRIPTION "OTUS algo homeworks"
	#LANGUAGES CXX
)

# Only do these if this is the main project, and not if it is included through add_subdirectory
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)

    # Optionally set things like CMAKE_CXX_STANDARD, CMAKE_POSITION_INDEPENDENT_CODE here
    
    # Let's ensure -std=c++xx instead of -std=g++xx
    #set(CMAKE_CXX_EXTENSIONS OFF)

    # Let's nicely support folders in IDE's
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    # Docs only available if this is the main app
    find_package(Doxygen)
    if(Doxygen_FOUND)
	add_subdirectory(docs)
    else()
	message(STATUS "Doxygen not found, not building docs")
    endif()
endif()

# add homeworks done option
set(HW_DONE 8 CACHE STRING "Fulfilled homework")
add_subdirectory(library)
add_subdirectory(hw)

