cmake_minimum_required(VERSION 3.13)

# set the project name and version
project(blue42_prj VERSION 1.0 LANGUAGES C ASM)

#Location of version file based on blue42_prj VERSION number
add_subdirectory(app/include/version)

# Location of application specific code
add_subdirectory(app)

# Location of test code. These will be run on every deploy.
add_subdirectory(test)

#Location of standalone/reusable modules
add_subdirectory(modules)

#Location of third party modules such as SDKs or RTOSs
add_subdirectory(third_party)
