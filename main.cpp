#include <iostream>
#include "SFML/Graphics.hpp"
#include "Grid.h"


int main() {
    Grid grid(32, 18);

    sf::RenderWindow window(sf::VideoMode(), "Pathfinder", sf::Style::Fullscreen);

    sf::Event event{};

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
                if(event.key.code == sf::Keyboard::Escape)
                    window.close();
        }

        // Clearing the old frame and preparing for drawing the new one
        window.clear(sf::Color::White);

        // project update and draw
        grid.update(window);
        grid.findPath();
        grid.draw(window);


        // Bring to screen and display the new frame just drawn
        window.display();
    }

}
