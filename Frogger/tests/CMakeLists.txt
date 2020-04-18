cmake_minimum_required (VERSION 3.8)

set(SOURCEST
	#actor folder
	"actors/test_game_object.cpp"
	#folders in "engine" folder
	##gfx folder
	"engine/gfx/test_sprite.cpp"
	##physics folder
	"engine/physic/test_collision_info.cpp"
	"engine/physic/test_rect.cpp"
	"engine/physic/test_rigid_body.cpp"
	"engine/physic/test_vector2.cpp"
	#engine folder
	"engine/test_draw_manager.cpp"
	"engine/test_physics_manager.cpp"
	"engine/test_texture_manager.cpp"
	"engine/test_update_manager.cpp"

)

add_executable(Frogger_Tests ${SOURCEST})

target_link_libraries(Frogger_Tests PUBLIC gtest_main FroggerLib)

add_test(
	NAME Frogger_Tests
	COMMAND Frogger_Tests
)

add_custom_command(TARGET Frogger_Tests POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different
		${PROJECT_BINARY_DIR}/_deps/sdl2-build/SDL2d.dll #<--- copy this file
		${PROJECT_BINARY_DIR}/Frogger/tests/) #<--- into this path