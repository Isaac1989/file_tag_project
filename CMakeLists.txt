# Mininum cmake version
cmake_minimum_required(VERSION 3.11)

# set the project name and version
project(file_tag_project VERSION 1.0.0 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Debug
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()
# Set source files
set(SOURCES 
    main.cxx
    src/file.cxx
    src/folder.cxx
    src/tag.cxx
    src/utils.cxx
    src/FileSystem.cxx
   )


# Add executable from all sources
add_executable(file_tag_project ${SOURCES})

# Add include directory to search path for headers
target_include_directories(file_tag_project PUBLIC include)


