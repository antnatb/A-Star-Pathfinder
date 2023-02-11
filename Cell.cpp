//
// Created by anton on 03/10/2022.
//

#include "Cell.h"


Cell::Cell(int x, int y, int side): x(x), y(y), side(side) {
    shape.setSize({float(side), float(side)});
    shape.setPosition(float(x), float(y));
    shape.setOutlineThickness(0);
    shape.setOutlineColor(sf::Color::Black);
    GCost = 999;
    HCost = 999;
    FCost = 999;
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
        shape.setFillColor(sf::Color{43, 48, 58}); // gunmetal
    else if (start)
        shape.setFillColor(sf::Color{79, 157, 105}); // forest green crayola
    else if (target)
        shape.setFillColor(sf::Color{213, 87, 59}); // cedar chest
    else if (visited)
        shape.setFillColor(sf::Color{44, 82, 118}); // yale blue
    else if (evaluated)
        shape.setFillColor(sf::Color{169, 211, 255}); // baby blue eyes
    else
        shape.setFillColor(sf::Color{242, 244, 255}); // ghost white
    window.draw(shape);

}

void Cell::addNeighbor(Cell &cell) {
    neighbors.push_back(&cell);
}

void Cell::reset() {
    available = false;
    evaluated = false;
    visited = false;
    parent = nullptr;
    GCost = 999;
    HCost = 999;
    FCost = 999;
}

Cell::Cell(): Cell(0, 0, 20) {}


