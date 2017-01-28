//
// Created by moran on 19/11/16.
//

#ifndef TEST1_MATRIX_H
#define TEST1_MATRIX_H

#include <iostream>
#include <vector>
#include "Map.h"
#include "Block.h"


using std::vector;

/**
 * create 2d matrix pointer of Block - the map of the city.
 * block road drived from map - abstract class.
 */
class Matrix : public Map {
private:
    int sizeX;
    int sizeY;
    vector<vector<Block *> > map;
public:
    Matrix(int x, int y);

    void createMap();

    int getRowsSize();

    int getColumnsSize();

    vector<vector<Block *> > getMap();

    Block *getBlock(Point point);

    Block *getBlock(int x, int y);

    ~Matrix();

    void setObstacles(int x, int y);

    int mapSize();
};


#endif //TEST1_MATRIX_H
