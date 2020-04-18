cmake_minimum_required (VERSION 3.8)

project ("FroggerGame")

enable_testing()

add_subdirectory ("Frogger")

#//Use shared (DLL) run-time lib even when Google Test is built
#// as static lib.
#gtest_force_shared_crt:BOOL=ON
#se the above option in "CMakeCache.txt" to on to make tests work
#TODO
#find a better way to do this