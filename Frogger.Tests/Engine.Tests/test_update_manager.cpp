#include "pch.h"
#include "Engine/update_manager.h"

TEST(update_manager_tests, init)
{
    update_manager_t update_manager;
    update_manager_init(&update_manager);
    EXPECT_TRUE
    (
        update_manager.go != NULL &&
        update_manager.max_go == 100 &&
        update_manager.go_count == 0
    );
}
