//
// Created by anton on 11/02/2023.
//
#include "gtest/gtest.h"
#include "../Cell.h"


//test to see if each cell type has its correct color
TEST(Cell, BlankColor) {
    Cell cell;
    sf::RenderWindow window;
    cell.draw(window);
    sf::Color color;
    color = sf::Color{242,244,255}; //blank cell color
    ASSERT_EQ(cell.shape.getFillColor(),color);
}

TEST(Cell, ObstacleColor) {
    Cell cell;
    sf::RenderWindow window;
    cell.draw(window);
    sf::Color color;
    cell.setObstacle(true);
    cell.draw(window);
    color = sf::Color{43, 48, 58}; //obstacle color
    ASSERT_EQ(cell.shape.getFillColor(),color);
}

TEST(Cell, StartColor) {
    Cell cell;
    sf::RenderWindow window;
    cell.draw(window);
    sf::Color color;
    cell.makeStart();
    cell.draw(window);
    color = sf::Color{79, 157, 105}; //start color
    ASSERT_EQ(cell.shape.getFillColor(), color);
}

TEST(Cell, TargetColor) {
    Cell cell;
    sf::RenderWindow window;
    cell.draw(window);
    sf::Color color;
    cell.makeTarget();
    cell.draw(window);
    color = sf::Color{213, 87, 59}; //target color
    ASSERT_EQ(cell.shape.getFillColor(), color);
}

TEST(Cell, EvaluatedColor) {
    Cell cell;
    sf::RenderWindow window;
    cell.draw(window);
    sf::Color color;
    cell.evaluate();
    cell.draw(window);
    color = sf::Color{169, 211, 255}; //evaluated color
    ASSERT_EQ(cell.shape.getFillColor(), color);
}

TEST(Cell, VisitedColor){
    Cell cell;
    sf::RenderWindow window;
    cell.draw(window);
    sf::Color color;
    cell.visit();
    cell.draw(window);
    color = sf::Color{44, 82, 118}; //visited color
    ASSERT_EQ(cell.shape.getFillColor(), color);
}