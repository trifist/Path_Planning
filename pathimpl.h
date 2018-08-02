#ifndef PATHIMPL_H
#define PATHIMPL_H

namespace Raiboo {

class PathImpl
{
public:
    virtual void loadMap(int* rawMap, int row, int col) = 0;
    virtual void planning() = 0;
    virtual void printPath() = 0;
};

}

#endif // PATHIMPL_H
