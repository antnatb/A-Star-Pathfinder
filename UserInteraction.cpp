//
// Created by anton on 15/02/2023.
//

#include "UserInteraction.h"
#include "Cell.h"

void UserInteraction::update(sf::RenderWindow &window) {
    int x = grid->getWidth();
    int y = grid->getHeight();
    Cell* cell;
    for (int i = 0; i < x; i++){
        for (int j = 0; j < y; j++){
            cell = grid->getCell(i,j);
            if (cell->shape.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))){
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    cell->setObstacle(true);
                else if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
                    cell->setObstacle(false);
            }
        }
    }
}

UserInteraction::UserInteraction(Grid *grid) : grid(grid) {}
