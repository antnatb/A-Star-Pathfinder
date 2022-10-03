//
// Created by anton on 03/10/2022.
//

#include "Cell.h"
#include <cmath>

Cell::Cell(int x, int y, int side): x(x), y(y), side(side) {
    shape.setSize({float(side), float(side)});
    shape.setPosition(float(x), float(y));
    shape.setOutlineThickness(2);
    shape.setOutlineColor(sf::Color::Black);
}

void Cell::update(sf::RenderWindow &window) {
    if (shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !isStart() && !isTarget())
            obstacle = true;
        else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
            obstacle = false;
    }
}

void Cell::draw(sf::RenderWindow &window) {
    if (obstacle)
        shape.setFillColor(sf::Color{43, 48, 58});
    else if (start)
        shape.setFillColor(sf::Color{37, 78, 112});
    else if (target)
        shape.setFillColor(sf::Color{195, 60, 84});
    else if (visited)
        shape.setFillColor(sf::Color{177, 177, 6});
    else if (evaluated)
        shape.setFillColor(sf::Color{249, 249, 98});
    else
        shape.setFillColor(sf::Color{245, 235, 255});
    window.draw(shape);

}

void Cell::computeCosts(Cell &start, Cell &target) {
    GCost = abs(x - start.x) + abs(y - start.y);
    HCost = abs(x - target.x) + abs(y - target.y);
    FCost = HCost + GCost;
}

void Cell::addNeighbor(Cell &cell) {
    neighbors.push_back(&cell);
}

void Cell::reset() {
    evaluated = false;
    visited = false;
    parent = nullptr;
    GCost = 0;
    HCost = 0;
    FCost = 0;
}


