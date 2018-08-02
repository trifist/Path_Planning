#ifndef ASTARIMPL_H
#define ASTARIMPL_H

#include<vector>
#include<list>
#include<pathimpl.h>
#include<point.h>

namespace Raiboo {

class AStarImpl : public PathImpl
{
private:
    Point** map;
    int row;
    int col;
    std::list<Point*> openList;
    std::list<Point*> closeList;
    Point* endPoint;
    bool diagonalPath = true;

    int calcGValue(Point* child, Point* parent);
    int calcHValue(Point* point);
    int calcFValue(Point* point);
    void initNeighbors(std::vector<Point*>* container, Point* parent);
    void orderedAddToOpenList(Point* point);
    Point* getFromOpenList();
    Point* getFromOpenList(int index);
    int findAddPos(int start, int end, Point* point);
    void release();

public:
    void loadMap(int* rawMap, int row, int col);
    void planning();
    void printPath();
    bool isDiagonalPath();
    void enableDiagonalPath(bool diagonalPath);

};

}


#endif // ASTARIMPL_H
