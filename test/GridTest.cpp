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
    Grid grid;
    grid.findPath();
    ASSERT_TRUE(grid.isPath()); //check if the path has been found
    list<Cell *> solution = grid.getSolution(); //store this path
    //these are the precalculated coordinates of the cells that compose the path generated by seed 18
    int precalculatedSolution_X[] = {1320, 1320, 1260, 1260, 1200, 1140, 1080, 1020,
                                     1020, 1020, 1020, 960, 900, 900, 900, 900,
                                     840, 780, 780, 780, 720, 660};
    int precalculatedSolution_Y[] = {420, 360, 360, 300, 300, 300, 300, 300, 360,
                                     420, 480, 480, 480, 540, 600, 660, 660,
                                     660, 720, 780, 780, 780};
    int precalculatedSize = 22; //number of cells of the precalculated path
    ASSERT_EQ(solution.size(), precalculatedSize);
    auto itr = solution.begin();
    int i = 0;
    while(itr != solution.end() && i < precalculatedSize){
        ASSERT_EQ((*itr)->getX(), precalculatedSolution_X[i]); //check x
        ASSERT_EQ((*itr)->getY(), precalculatedSolution_Y[i]); //check y
        itr++;
        i++;
    }
}

