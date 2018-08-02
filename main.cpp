#include <iostream>
#include <point.h>
#include <pathimpl.h>
#include <astarimpl.h>

using namespace std;

int main()
{
    int rawMap[] = {
        0, 0, 0, 0, 0, 0, 0,
        1, 0, 0, 3, 0, 0, 0,
        1, 0, 0, 1, 0, 0, 0,
        1, 0, 0, 0, 0, 0, 0,
        1, 0, 1, 1, 1, 0, 0,
        1, 0, 0, 2, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 0
    };

    Raiboo::PathImpl* algrithom = new Raiboo::AStarImpl;
    algrithom->loadMap(rawMap, 7, 7);
    algrithom->planning();
}
