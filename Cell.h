//
// Created by anton on 03/10/2022.
//

#ifndef PATHFINDER_CELL_H
#define PATHFINDER_CELL_H

#include "SFML/Graphics.hpp"
#include <list>

using namespace std;


class Cell {
public:
    Cell(int x, int y, int side);
    ~Cell() = default;

    void update(sf::RenderWindow &window);

    void draw(sf::RenderWindow &window);

    void computeCosts(Cell &start, Cell &target);

    void computeFCost(){
        FCost = GCost + HCost;
    }

    void addNeighbor(Cell &cell);

    void reset();

    list<Cell*> getNeighbors(){
        return neighbors;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    bool isStart() const {
        return start;
    }

    void makeStart() {
        start = true;
    }

    bool isTarget() const {
        return target;
    }

    void makeTarget() {
        target = true;
    };

    bool isObstacle() const {
        return obstacle;
    }

    float getFCost () const {
        return FCost;
    }

    float getHCost() const {
        return HCost;
    }
    void setGCost(float value) {
        GCost = value;
    }

    float getGCost() const {
        return GCost;
    }

    Cell* getParent() const {
        return parent;
    }

    void setParent(Cell &cell){
        parent = &cell;
    }

    void evaluate() {
        evaluated = true;
    }

    void visit() {
        visited = true;
    }

    sf::RectangleShape shape;

private:
    int x, y;
    int side;

    float GCost = 0;
    float HCost = 0;
    float FCost = 0;

    list<Cell*> neighbors = {};

    Cell *parent = nullptr;

    bool start = false;
    bool target = false;
    bool obstacle = false;
    bool evaluated = false;
    bool visited = false;


};


#endif //PATHFINDER_CELL_H
