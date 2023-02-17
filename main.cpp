
#include <iostream>
#include "SFML/Graphics.hpp"
#include "UserInteraction.h"


int main() {
    ::srand(::time(nullptr));

    Grid myGrid(48, 27);

    UserInteraction interaction(&myGrid);

    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pathfinder",sf::Style::Fullscreen);

    sf::Event event{};

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::Space)
                    myGrid.findPath();
            }
        }

        // Clearing the old frame and preparing for drawing the new one
        window.clear(sf::Color::White);

        // project update and draw
        //myGrid.update(window);
        interaction.update(window);
        myGrid.findPath();
        myGrid.draw(window);


        // Bring to screen and display the new frame just drawn
        window.display();
    }

}
