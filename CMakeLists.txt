cmake_minimum_required (VERSION 3.8)

project ("FroggerGame")

set(gtest_force_shared_crt ON CACHE BOOL [FORCE])

enable_testing()

set(FROGGER_HEADERS
	"dependencies/stb_image.h"
)

set(FROGGER_SOURCES
	
	${FROGGER_HEADERS}
	#engine/actors folder
	"src/engine/actors/game_object.c"
	"src/engine/actors/update_manager.c"
	#engine/gfx folder
	"src/engine/gfx/image_info.c"
	"src/engine/gfx/sprite.c"
	"src/engine/gfx/draw_manager.c"
	#engine/physics folder
	"src/engine/physics/physics_manager.c"
	"src/engine/physics/rigid_body.c"
	#engine/utilities folder
	"src/engine/utilities/game_clock.c"
	"src/engine/utilities/collision_info.c"
	"src/engine/utilities/texture_manager.c"
	#math folder
	"src/math/vector2.c"
	"src/math/rect.c"
	#frogger folder 
	"src/frogger/background.c"
	"src/frogger/obstacle.c"
	"src/frogger/player.c"
)

add_executable(FroggerExecutable "src/main.c")

add_library(FroggerLib STATIC ${FROGGER_SOURCES})

target_link_libraries(FroggerLib PUBLIC SDL2main SDL2)
target_include_directories(FroggerLib PUBLIC SDL2main SDL2 PUBLIC "$<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>")

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