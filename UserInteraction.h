//
// Created by anton on 15/02/2023.
//

#ifndef PATHFINDER_USERINTERACTION_H
#define PATHFINDER_USERINTERACTION_H

#include "Grid.h"
#include "SFML/Graphics.hpp"


class UserInteraction {
public:

    explicit UserInteraction(Grid *grid);

    void update(sf::RenderWindow& window);


private:
    Grid* grid;
};


#endif //PATHFINDER_USERINTERACTION_H
