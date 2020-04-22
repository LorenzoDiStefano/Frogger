﻿cmake_minimum_required (VERSION 3.8)

project ("FroggerGame")

enable_testing()

#//Use shared (DLL) run-time lib even when Google Test is built
#// as static lib.
#gtest_force_shared_crt:BOOL=ON
#se the above option in "CMakeCache.txt" to on to make tests work
#TODO
#find a better way to do this

set(FROGGER_HEADERS
	#including in hierarchy order
	#dependencies
	"dependencies/stb_image.h"
	#actors folder
	"src/actors/background.h"
	"src/actors/game_object.h"
	"src/actors/obstacle.h"
	"src/actors/player.h"
	#folders inside engine folder
	##gfx folder
	"src/engine/gfx/image_info.h"
	"src/engine/gfx/sprite.h"
	##physics folder
	"src/engine/physics/collision_info.h"
	"src/engine/physics/rect.h"
	"src/engine/physics/rigid_body.h"
	"src/engine/physics/vector2.h"
	##utility folder
	"src/engine/utility/game_clock.h"
	#engine folder
	"src/engine/draw_manager.h"
	"src/engine/physics_manager.h"
	"src/engine/texture_manager.h"
	"src/engine/update_manager.h"
)

set(FROGGER_SOURCES
	
	${FROGGER_HEADERS}
	#including in hierarchy order
	#actors folder
	"src/actors/background.c"
	"src/actors/game_object.c"
	"src/actors/obstacle.c"
	"src/actors/player.c"
	#folders inside engine folder
	##gfx folder
	"src/engine/gfx/image_info.c"
	"src/engine/gfx/sprite.c"
	##physics folder
	"src/engine/physics/collision_info.c"
	"src/engine/physics/rect.c"
	"src/engine/physics/rigid_body.c"
	"src/engine/physics/vector2.c"
	##utility folder
	"src/engine/utility/game_clock.c"
	#engine folder
	"src/engine/draw_manager.c"
	"src/engine/physics_manager.c"
	"src/engine/texture_manager.c"
	"src/engine/update_manager.c"
)

add_executable(FroggerExecutable "src/main.c")

add_library(FroggerLib STATIC ${FROGGER_SOURCES})


target_link_libraries(FroggerLib PUBLIC SDL2main SDL2)
target_include_directories(FroggerLib PUBLIC SDL2main SDL2)

target_link_libraries(FroggerExecutable PRIVATE FroggerLib)
target_include_directories(FroggerExecutable PRIVATE FroggerLib)

add_dependencies(FroggerExecutable FroggerLib)

add_subdirectory(dependencies)
add_subdirectory(tests)

add_custom_command(TARGET FroggerExecutable POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${PROJECT_BINARY_DIR}/_deps/sdl2-build/SDL2d.dll #<--- copy this file
		${PROJECT_BINARY_DIR}/) #<--- into this path

add_custom_command(TARGET FroggerExecutable PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/assets #<--- copy files in this folder
		${PROJECT_BINARY_DIR}/assets/) #<--- into this path