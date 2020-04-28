cmake_minimum_required(VERSION 3.17)

# set the project name and version
project(unity_test VERSION 1.0 LANGUAGES C ASM)


add_subdirectory(app)
add_subdirectory(app/include/version)
add_subdirectory(libraries)
#add_subdirecotry(extern)

