cmake_minimum_required (VERSION 3.8)

project ("FroggerGame")

enable_testing()

add_subdirectory ("Frogger")

#CMakeCache.txt
#//Use shared (DLL) run-time lib even when Google Test is built
#// as static lib.
#gtest_force_shared_crt:BOOL=ON