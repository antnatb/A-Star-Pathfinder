//
// Created by anton on 11/02/2023.
//

#include "gtest/gtest.h"
#include "../Grid.h"

TEST(Grid, NoPath) {
    ::srand(16); // a default dimensions grid with seed #16 should have no path available
    Grid grid;
    grid.findPath();
    ASSERT_FALSE(grid.isPath());
    ASSERT_TRUE(grid.getSolution().empty());
}

TEST(Grid, Path) {
    ::srand(18); // a default dimensions grid with seed #18 should have a path available
    Grid grid1;
    grid1.findPath();
    ASSERT_TRUE(grid1.isPath()); //check if the path has been found
    list<Cell*> solution1 = grid1.getSolution(); //store this path
    ::srand(18); //create another grid with seed 18
    Grid grid2;
    grid2.findPath();
    ASSERT_TRUE(grid2.isPath()); //check if the path has been found
    list<Cell*> solution2 = grid2.getSolution(); //store this other path
    ASSERT_EQ(solution1.size(),solution2.size()); //check if the two solutions have the same length
    auto itr1 = solution1.begin();
    auto itr2 = solution2.begin();
    while (itr1 != solution1.end() && itr2 != solution2.end()) { //iterate through the two solutions in order to compare the cells that compose them
        ASSERT_EQ((*itr1)->getX(), (*itr2)->getX()); //check x
        ASSERT_EQ((*itr1)->getY(), (*itr2)->getY()); //check y
        itr1++;
        itr2++;
    }

}

