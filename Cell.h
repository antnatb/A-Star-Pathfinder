//
// Created by anton on 03/10/2022.
//

#ifndef PATHFINDER_CELL_H
#define PATHFINDER_CELL_H

#include "SFML/Graphics.hpp"
#include <list>
#include <cmath>

using namespace std;


class Cell {
public:
    Cell(int x, int y, int side);
    Cell();
    ~Cell() = default;

    void draw(sf::RenderWindow &window);

    void computeHCost(Cell &target) {
        HCost = sqrt(pow(x - target.x, 2) + pow(y- target.y, 2));
    }

    void computeFCost(){
        FCost = GCost + HCost;
    }

    void addNeighbor(Cell &cell);

    void reset();

    list<Cell*> getNeighbors() const {
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
        target = false;
    }

    bool isTarget() const {
        return target;
    }

    void makeTarget() {
        start = false;
        target = true;
    };

    void setObstacle(bool b) {
        obstacle = b;
    }

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

    bool isEvaluated() const {
        return evaluated;
    };

    void setAvailable(bool av){
        available = av;
    }

    bool isAvailable() const {
        return available;
    }

    void visit() {
        visited = true;
    }

    sf::RectangleShape shape;

private:
    int x, y;
    int side;

    float GCost;
    float HCost;
    float FCost;

    list<Cell*> neighbors = {};

    Cell *parent = nullptr;

    bool start = false;
    bool target = false;
    bool obstacle = false;
    bool available = false;
    bool evaluated = false;
    bool visited = false;


};


#endif //PATHFINDER_CELL_H
