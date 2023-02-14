//
// Created by anton on 11/02/2023.
//

#include "gtest/gtest.h"
#include "../Grid.h"

TEST(Grid, NoPath) {
    ::srand(16); // a default dimensions grid with seed #16 should have no path available
    Grid grid;
    grid.findPath();
    ASSERT_EQ(grid.isPath(), false);
    grid.getSolution();
}

TEST(Grid, Path) {
    ::srand(18); // a default dimensions grid with seed #18 should have a path available
    Grid grid;
    grid.findPath();
    ASSERT_EQ(grid.isPath(), true);
    grid.getSolution();
}

