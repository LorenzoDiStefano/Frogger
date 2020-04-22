cmake_minimum_required (VERSION 3.8)

include(FetchContent)

#downloading SDL2 via mercurial
FetchContent_Declare(
	SDL2
	HG_REPOSITORY	http://hg.libsdl.org/SDL
	HG_TAG			release-2.0.10
)

FetchContent_GetProperties(SDL2)
if(NOT SDL2_POPULATED)
	FetchContent_Populate(SDL2)
	add_subdirectory(${sdl2_SOURCE_DIR} ${sdl2_BINARY_DIR})
endif()

#downloading googletest via git
FetchContent_Declare(
	googletest
	GIT_REPOSITORY	http://github.com/google/googletest.git
	GIT_TAG			release-1.10.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()