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
    ~Grid() = default;

    void update(sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

    void reset();

    void traceBackPath();

    void addNeighbors(Cell &cell);

    Cell* findFreeCell();

    void findPath();

    Cell* findLowestCostCell();

    void setStart();
    void setTarget();

private:
    int width, height;

    int cellSide;

    Cell* start = nullptr;
    Cell* target = nullptr;
    Cell* current = nullptr;

    vector<vector<Cell>> cells;

    list<Cell*> availableCells;
    list<Cell*> evaluatedCells;

    bool diagonalMovement = false;
};


#endif //PATHFINDER_GRID_H
