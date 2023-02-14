//
// Created by anton on 03/10/2022.
//

#include <iostream>
#include "Grid.h"

//Ctor; we decide the dimensions of the grid
Grid::Grid(int x, int y):width(x), height(y) {
    //compute the side of the cells based on the display's dimensions
    cellSide = int(sf::VideoMode::getDesktopMode().width) / x;
    for (int i = 0; i < x; i++) {
        cells.emplace_back();
        for (int j = 0; j < y ; j++){
            Cell cell(i * cellSide, j * cellSide, cellSide);
            int randomNumber = rand() % 10;
            if (randomNumber < 4)
                cell.makeObstacle();
            cells[i].push_back(cell);
        }
    }
    //set two random cells as start and target
    setStart();
    setTarget();
}

Grid::Grid(): Grid(32,18) {}

//function that returns a random free cell on the grid; we use it to set start and target
Cell *Grid::findFreeCell() {
    bool found = false;
    Cell *cell = nullptr;
    while (!found) {
        int x = rand() % width;
        int y = rand() % height;
        cell = &cells[x][y];
        if (!cell->isStart() && !cell->isObstacle() && !cell->isTarget())
            found = true;
    }
    return cell;
}

void Grid::setStart() {
    start = findFreeCell();
    start->makeStart();
}

void Grid::setTarget() {
    target = findFreeCell();
    target->makeTarget();
}

void Grid::update(sf::RenderWindow &window) {
    for (auto &row : cells)
        for (auto &cell : row)
            cell.update(window);
}

void Grid::draw(sf::RenderWindow &window) {
    for (auto &row : cells)
        for (auto &cell : row)
            cell.draw(window);
}

void Grid::findPath() {
    //reset the grid
    reset();
    //we begin from the start cell
    availableCells.push_back(start);
    start->setAvailable(true);
    path = true;
    //loop; we visit cells until we find the target, or until there's no cell available to visit
    while (current != target && path) {
        current = findLowestCostCell();
        addNeighbors(*current);
        evaluateNeighbors(*current);
        if (availableCells.empty())
            path = false;
    }
    if (path)
        traceBackPath();
}


Cell *Grid::findLowestCostCell() {
    float lowestCost = 9999.9;
    Cell *lowestCostCell = nullptr;
    for (auto &cell: availableCells) {
        if (cell->getFCost() < lowestCost || (cell->getFCost() == lowestCost && cell->getHCost() < lowestCostCell->getHCost())) {
            lowestCostCell = cell;
            lowestCost = cell->getFCost();
        }
    }
    availableCells.remove(lowestCostCell);
    lowestCostCell->setAvailable(false);
    evaluatedCells.push_back(lowestCostCell);
    lowestCostCell->evaluate();
    return lowestCostCell;
}

void Grid::addNeighbors(Cell &cell) {
    int x = cell.getX() / cellSide;
    int y = cell.getY() / cellSide;

    //top
    if (y + 1 < height)
        if (!cells[x][y + 1].isStart() && !cells[x][y + 1].isObstacle()) {
            cell.addNeighbor(cells[x][y + 1]);
        }

    //right
    if (x + 1 < width)
        if (!cells[x + 1][y].isStart() && !cells[x + 1][y].isObstacle()) {
            cell.addNeighbor(cells[x + 1][y]);
        }

    //bottom
    if (y - 1 >= 0)
        if (!cells[x][y - 1].isStart() && !cells[x][y - 1].isObstacle()) {
            cell.addNeighbor(cells[x][y - 1]);
        }

    //left
    if (x - 1 >= 0)
        if (!cells[x - 1][y].isStart() && !cells[x - 1][y].isObstacle()) {
            cell.addNeighbor(cells[x - 1][y]);
        }

    if (diagonalMovement) {
        //top right
        if (y + 1 < height && x + 1 < width)
            if (!cells[x + 1][y + 1].isStart() && !cells[x + 1][y + 1].isObstacle() && !(cells[x][y+1].isObstacle() && cells[x+1][y].isObstacle())) {
                cell.addNeighbor(cells[x + 1][y + 1]);
            }

        //bottom right
        if (y - 1 >= 0 && x + 1 < width)
            if (!cells[x + 1][y - 1].isStart() && !cells[x + 1][y - 1].isObstacle() && !(cells[x][y-1].isObstacle() && cells[x+1][y].isObstacle())) {
                cell.addNeighbor(cells[x + 1][y - 1]);
            }

        //bottom left
        if (y - 1 >= 0 && x - 1 >= 0)
            if (!cells[x - 1][y - 1].isStart() && !cells[x - 1][y - 1].isObstacle() && !(cells[x][y-1].isObstacle() && cells[x-1][y].isObstacle())) {
                cell.addNeighbor(cells[x - 1][y - 1]);
            }

        //top left
        if (x - 1 >= 0 && y + 1 < height)
            if (!cells[x - 1][y + 1].isStart() && !cells[x - 1][y + 1].isObstacle() && !(cells[x][y-1].isObstacle() && cells[x-1][y].isObstacle())) {
                cell.addNeighbor(cells[x - 1][y + 1]);
            }
    }
}

void Grid::reset() {
    for (auto &row : cells)
        for (auto &cell: row)
            cell.reset();
    availableCells.clear();
    evaluatedCells.clear();
    current = nullptr;
}

void Grid::traceBackPath() {
    current = target->getParent();
    while (current != start) {
        current->visit();
        visitedCells.push_back(current);
        current = current->getParent();
    }
}

void Grid::evaluateNeighbors(Cell &cell) {
    for (auto neighbor : cell.getNeighbors()) {
        if (neighbor->isObstacle() || neighbor->isEvaluated())
            continue;
        float newGCost = cell.getGCost() + sqrtf(pow(cell.getX() - neighbor->getX(), 2) +
                                                     pow(cell.getY() - neighbor->getY(), 2));
        if (newGCost < neighbor->getGCost() || !neighbor->isAvailable()) {
            neighbor->setGCost(newGCost);
            neighbor->computeHCost(*target);
            neighbor->computeFCost();
            neighbor->setParent(cell);
            if (!neighbor->isAvailable()) {
                availableCells.push_back(neighbor);
                neighbor->setAvailable(true);
            }
        }

    }
}

bool Grid::isPath() const {
    return path;
}

void Grid::getSolution() const {
    if (!path)
        std::cout << "There is no path available in this map." << std::endl;
    else {
        std::cout << "The cells that compose the path are:" << std::endl;
        int i = 1;
        for (auto cell: visitedCells) {
            int x = cell->getX() / cellSide;
            int y = cell->getY() / cellSide;
            std::cout << "Cell #" << i << ": x=" << x << ", y=" << y << std::endl;
            i++;
        }
    }
}





