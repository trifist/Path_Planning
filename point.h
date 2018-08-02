#ifndef POINT_H
#define POINT_H

#include <cstdlib>

#define POINT_START 2
#define POINT_END 3
#define POINT_ROAD 0
#define POINT_OBSTACLE 1

namespace Raiboo
{

class Point
{
private:
    int fValue;
    int gValue;
    int hValue;
    int pointType;
    Point *parent = NULL;

public:
    Point(int x, int y, int fValue = 0, int gValue = 0, int hValue = 0);
    Point();
    ~Point();

    int x;
    int y;

    int getPointType();
    int getfValue();
    int getgValue();
    int gethValue();
    Point* getParent();

    void setPointType(int pointType);
    void setfValue(int fValue);
    void setgValue(int gValue);
    void sethValue(int hValue);
    void setParent(Point *parent);
};

}

#endif // POINT_H
