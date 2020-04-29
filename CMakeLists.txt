cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(blue42_prj VERSION 1.0 LANGUAGES C ASM)



add_subdirectory(app/include/version)
add_subdirectory(libraries)
add_subdirectory(extern)

add_subdirectory(app)

add_subdirectory(test)
