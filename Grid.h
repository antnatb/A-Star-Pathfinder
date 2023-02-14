//
// Created by anton on 03/10/2022.
//

#ifndef PATHFINDER_GRID_H
#define PATHFINDER_GRID_H

#include "Cell.h"

#include <vector>
#include <list>
#include "SFML/Graphics.hpp"
#include <cmath>


using namespace std;


class Grid {
public:

    explicit Grid(int x, int y);
    Grid();
    ~Grid() = default;

    void update(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);

    void findPath();
    void getSolution() const;

    bool isPath() const;


private:
    void reset();

    void traceBackPath();

    void addNeighbors(Cell &cell);

    Cell* findFreeCell();

    Cell* findLowestCostCell();

    void evaluateNeighbors(Cell &cell);

    void setStart();
    void setTarget();
    //dimensions of the grid
    int width, height;

    //length of the side of each cell
    int cellSide;

    //pointers to key cells
    Cell* start = nullptr;
    Cell* target = nullptr;
    Cell* current = nullptr;

    //our main data structure, a sort of matrix of cells
    vector<vector<Cell>> cells;

    //list of the "reachable" cells, aka cells which can be visited by the pathfinder at a given time
    list<Cell*> availableCells;

    //list of the evaluated cells, aka cells which have been visited by the pathfinder at a given time
    list<Cell*> evaluatedCells;

    //list of the cells that actually make the path
    list<Cell*> visitedCells;

    //boolean attribute that indicates whether there is a path or not
    bool path;

    //bool variable to enable diagonal movement
    bool diagonalMovement = false;
};


#endif //PATHFINDER_GRID_H
