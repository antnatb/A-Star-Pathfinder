//
// Created by anton on 03/10/2022.
//

#include "Grid.h"

Grid::Grid(int x, int y):width(x), height(y) {
    cellSide = int(sf::VideoMode::getDesktopMode().width) / (x * 2);
    for (int i = 0; i < x; i++) {
        cells.emplace_back();
        for (int j = 0; j < y; j++){
            Cell cell(i * cellSide, j * cellSide, cellSide);
            cells[i].push_back(cell);
        }
    }
    setStart();
    setTarget();
}

Cell *Grid::findFreeCell() {
    srand(time(0));
    bool found = false;
    while (!found) {
        int x = rand() % width;
        int y = rand() % height;
        Cell *cell = &cells[x][y];
        if (!cell->isStart() && !cell->isObstacle() && !cell->isTarget()){
            found = true;
            return cell;
        }
    }
    return nullptr;
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
    reset();
    availableCells.push_back(start);
    while (current != target) {
        current = findLowestCostCell();
        availableCells.remove(current);
        evaluatedCells.push_back(current);
        current->evaluate();
        addNeighbors(*current);
        for (auto neighbor: current->getNeighbors()) {
            if (neighbor->isObstacle() ||
                std::find(evaluatedCells.begin(), evaluatedCells.end(), neighbor) != evaluatedCells.end())
                continue;
            if (current->getGCost() + abs(current->getX() - neighbor->getX()) +
                abs(current->getY() - neighbor->getY()) < neighbor->getGCost()) {
                neighbor->setGCost(current->getGCost() + abs(current->getX() - neighbor->getX()) +
                                   abs(current->getY() - neighbor->getY()));
                neighbor->computeFCost();
                neighbor->setParent(*current);
            }
            if (std::find(availableCells.begin(), availableCells.end(), neighbor) == availableCells.end()){
                neighbor->computeCosts(*start, *target);
                neighbor->setParent(*current);
                availableCells.push_back(neighbor);
            }
        }
    }
    traceBackPath();
}

Cell *Grid::findLowestCostCell() {
    Cell *lowestCostCell = availableCells.back();
    for (auto &cell: availableCells) {
        if (!cell->getFCost())
            cell->computeCosts(*start, *target);
        if (cell->getFCost() < lowestCostCell->getFCost() ||
            (cell->getFCost() == lowestCostCell->getFCost() && cell->getHCost() < lowestCostCell->getHCost()))
            lowestCostCell = cell;
    }
    return lowestCostCell;
}

void Grid::addNeighbors(Cell &cell) {
    int x = cell.getX() / cellSide;
    int y = cell.getY() / cellSide;

    //right
    if (x+1 < width)
        if (!cells[x+1][y].isStart() && !cells[x+1][y].isObstacle()){
            cell.addNeighbor(cells[x+1][y]);
            //cells[x+1][y].setParent(cell);
        }

    //left
    if (x-1 >= 0)
        if (!cells[x-1][y].isStart() && !cells[x-1][y].isObstacle()){
            cell.addNeighbor(cells[x-1][y]);
            //cells[x-1][y].setParent(cell);
        }

    //up
    if (y+1 < height)
        if (!cells[x][y+1].isStart() && !cells[x][y+1].isObstacle()){
            cell.addNeighbor(cells[x][y+1]);
            //cells[x][y+1].setParent(cell);
        }

    //down
    if (y-1 >= 0 )
        if (!cells[x][y-1].isStart() && !cells[x][y-1].isObstacle()){
            cell.addNeighbor(cells[x][y-1]);
            //cells[x][y-1].setParent(cell);
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
        current = current->getParent();
    }
}


