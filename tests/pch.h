#pragma once

//#include <SDL.h>
#include <gtest/gtest.h>

#ifdef __cplusplus 
extern "C" {
#endif
#include <engine/actors/game_object.h>
#include <engine/actors/update_manager.h>

#include <engine/gfx/sprite.h>
#include <engine/gfx/draw_manager.h>

#include <engine/utilities/game_clock.h>
#include <engine/utilities/collision_info.h>
#include <engine/utilities/texture_manager.h>

#include <engine/physics/physics_manager.h>
#include <engine/physics/rigid_body.h>

#include <math/rect.h>
#include <math/vector2.h>

#ifdef __cplusplus 
}
#endif