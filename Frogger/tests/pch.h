#pragma once

//#include <SDL.h>
#include <gtest/gtest.h>

#ifdef __cplusplus 
extern "C" {
#endif
//#actors
#include "../src/actors/game_object.h"
//#header fils inside the folder engine
//##gfx
#include "../src/engine/gfx/sprite.h"
//##physics
#include "../src/engine/physics/collision_info.h"
#include "../src/engine/physics/rect.h"
#include "../src/engine/physics/rigid_body.h"
#include "../src/engine/physics/vector2.h"
//#engine
#include "../src/engine/draw_manager.h"
#include "../src/engine/physics_manager.h"
#include "../src/engine/texture_manager.h"
#include "../src/engine/update_manager.h"

//#
#ifdef __cplusplus 
}
#endif