cmake_minimum_required (VERSION 3.8)

set(FROGGER_HEADERS
	#including in ordine di gerarchia
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
	##physics
	"src/engine/physics/collision_info.h"
	"src/engine/physics/rect.h"
	"src/engine/physics/rigid_body.h"
	"src/engine/physics/vector2.h"
	##utility
	"src/engine/utility/game_clock.h"
	#engine folder
	"src/engine/draw_manager.h"
	"src/engine/physics_manager.h"
	"src/engine/texture_manager.h"
	"src/engine/update_manager.h"
)

set(FROGGER_SOURCES
	
	${FROGGER_HEADERS}
	#including in ordine di gerarchia
	#actors folder
	"src/actors/background.c"
	"src/actors/game_object.c"
	"src/actors/obstacle.c"
	"src/actors/player.c"
	#folders inside engine folder
	##gfx folder
	"src/engine/gfx/image_info.c"
	"src/engine/gfx/sprite.c"
	##physics
	"src/engine/physics/collision_info.c"
	"src/engine/physics/rect.c"
	"src/engine/physics/rigid_body.c"
	"src/engine/physics/vector2.c"
	##utility
	"src/engine/utility/game_clock.c"
	#engine folder
	"src/engine/draw_manager.c"
	"src/engine/physics_manager.c"
	"src/engine/texture_manager.c"
	"src/engine/update_manager.c"
)

add_executable(FroggerExecutable "src/main.c")#src/Frogger.c

add_library(FroggerLib STATIC ${FROGGER_SOURCES})#"src/engine/physic/vector2.c"


target_link_libraries(FroggerLib PUBLIC SDL2main SDL2)
target_include_directories(FroggerLib PUBLIC SDL2main SDL2)

target_link_libraries(FroggerExecutable PRIVATE FroggerLib)
target_include_directories(FroggerExecutable PRIVATE FroggerLib)

add_dependencies(FroggerExecutable FroggerLib)

add_subdirectory(dependencies)
add_subdirectory(tests)



#set(test "test")
#target_include_directories(${CMAKE_CURRENT_LIST_DIR})
#message(WARNING ${PROJECT_BINARY_DIR})
#install(
#    DIRECTORY "src"
#    DESTINATION "include"
#    FILES_MATCHING PATTERN "*.h"
#    )

add_custom_command(TARGET FroggerExecutable POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${PROJECT_BINARY_DIR}/_deps/sdl2-build/SDL2d.dll #<--- copy this file
		${PROJECT_BINARY_DIR}/Frogger/) #<--- into this path

#set(testsmessage)
#
#message(WARNING ${CMAKE_CURRENT_SOURCE_DIR})
#message(WARNING "cane")
#message(WARNING "cane")

add_custom_command(TARGET FroggerExecutable PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/assets #<--- copy fles in this folder
		${PROJECT_BINARY_DIR}/Frogger/assets/) #<--- into this path