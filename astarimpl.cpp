#include "astarimpl.h"
#include <cmath>
#include <iostream>
#include <algorithm>

bool contains(std::list<Raiboo::Point*> &list, const Raiboo::Point* point) {
    std::list<Raiboo::Point*>::iterator it = std::find(list.begin(), list.end(), point);
    if(it != list.end()) {
        return true;
    } else {
        return false;
    }
}

void remove(std::list<Raiboo::Point*> &list, const Raiboo::Point* point) {
    std::list<Raiboo::Point*>::iterator it = std::find(list.begin(), list.end(), point);
    if(it != list.end()) {
        list.erase(it);
    }
}

void Raiboo::AStarImpl::release() {
    for(int i=0;i<(this->row)*(this->col);i++) {
        delete this->map[i];
    }
    delete this->map;
}

void Raiboo::AStarImpl::loadMap(int *rawMap, int row, int col) {
    this->map = new Point*[row*col];
    this->row = row;
    this->col = col;
    for(int i=0; i<row; i++) {
        for(int j=0;j<col;j++) {
            Point* p = new Point(i, j);
            p->setPointType(*(rawMap+i*col+j));
            this->map[i*col + j] = p;
            if(p->getPointType() == POINT_START) {
                orderedAddToOpenList(p);
            } else if(p->getPointType() == POINT_END){
                this->endPoint = p;
            }
        }
    }
}

void Raiboo::AStarImpl::planning() {
    while(true) {
        Point* focusPoint = getFromOpenList();
        if(focusPoint == NULL) {
            std::cout << "no path exists!" << std::endl;
            this->release();
            return;
        }
        this->closeList.push_back(focusPoint);
        std::vector<Point*> neighbors;
        initNeighbors(&neighbors, focusPoint);
        while(!neighbors.empty()) {
            Point* neighbor = neighbors.back();
            neighbors.pop_back();
            if(!contains(this->closeList, neighbor) && neighbor->getPointType() != POINT_OBSTACLE) {
                if(!contains(this->openList, neighbor)) {
                    neighbor->setgValue(focusPoint->getgValue() + calcGValue(neighbor, focusPoint));
                    neighbor->sethValue(calcHValue(neighbor));
                    neighbor->setfValue(calcFValue(neighbor));
                    neighbor->setParent(focusPoint);
                    orderedAddToOpenList(neighbor);
                    if(neighbor->getPointType() == POINT_END) {
                        std::cout << "path found:" << std::endl;
                        printPath();
                        this->release();
                        return;
                    }
                } else {
                    int newGValue = focusPoint->getgValue() + calcGValue(neighbor, focusPoint);
                    if(newGValue < neighbor->getgValue()) {
                        neighbor->setParent(focusPoint);
                        neighbor->setgValue(newGValue);
                        neighbor->setfValue(calcFValue(neighbor));
                        remove(this->openList, neighbor);
                        orderedAddToOpenList(neighbor);
                    }
                }
            }
        }
    }
}

void Raiboo::AStarImpl::printPath() {
    Point* point = this->endPoint;
    std::cout << "(" << point->x << "," << point->y << ")";
    while((point = point->getParent()) != NULL) {
        std::cout << "--->(" << point->x << "," << point->y << ")";
    }
    std::cout << std::endl;
}

int Raiboo::AStarImpl::calcGValue(Point *child, Point *parent) {
    return std::sqrt((child->x - parent->x)*(child->x - parent->x)+(child->y - parent->y)*(child->y - parent->y)) * 100;
}

int Raiboo::AStarImpl::calcHValue(Point *point) {
    return (std::abs(this->endPoint->x - point->x) + std::abs(this->endPoint->y - point->y)) * 100;
}

int Raiboo::AStarImpl::calcFValue(Point *point) {
    return point->getgValue() + point->gethValue();
}

void Raiboo::AStarImpl::initNeighbors(std::vector<Point *> *container, Point *parent) {
    for (int i = parent->x - 1; i <= parent->x + 1; i++) {
        for (int j = parent->y - 1; j <= parent->y + 1; j++) {
            if (i == parent->x && j == parent->y) {
                continue;
            }

            if (!this->diagonalPath) {
                if (i == parent->x - 1 && j == parent->y - 1) {
                    continue;
                }
                if (i == parent->x - 1 && j == parent->y + 1) {
                    continue;
                }
                if (i == parent->x + 1 && j == parent->y - 1) {
                    continue;
                }
                if (i == parent->x + 1 && j == parent->y + 1) {
                    continue;
                }
            }

            if(i >= 0 && i < this->row && j >= 0 && j < this->col) {
                container->push_back(this->map[i * col + j]);
            }
        }
    }
}

void Raiboo::AStarImpl::orderedAddToOpenList(Point *point) {
    if(this->openList.size()==0) {
        this->openList.push_back(point);
    } else {
        int pos = findAddPos(0, this->openList.size() - 1, point);
        std::list<Point*>::iterator it = this->openList.begin();
        for(int i=0;i<pos;i++) {
            ++it;
        }
        this->openList.insert(it, point);
    }
}

Raiboo::Point* Raiboo::AStarImpl::getFromOpenList() {
    if(this->openList.size() > 0) {
        Point* point = this->openList.front();
        this->openList.pop_front();
        return point;
    } else {
        return NULL;
    }
}

Raiboo::Point* Raiboo::AStarImpl::getFromOpenList(int index) {
    std::list<Point*>::iterator it = this->openList.begin();
    for(int i=0;i<index;i++) {
        ++it;
    }
    return *it;
}

int Raiboo::AStarImpl::findAddPos(int start, int end, Point *point) {
    if((end - start) <= 1) {
        if(point->getfValue() <= getFromOpenList(start)->getfValue()) {
            return start;
        } else if(point->getfValue() >= getFromOpenList(end)->getfValue()) {
            return end + 1;
        } else {
            return end;
        }
    }
    int middle = (start + end) / 2;
    if(point->getfValue() < getFromOpenList(middle)->getfValue()) {
        return findAddPos(start, middle, point);
    } else if(point->getfValue() > getFromOpenList(middle)->getfValue()) {
        return findAddPos(middle, end, point);
    } else {
        return middle;
    }
}



bool Raiboo::AStarImpl::isDiagonalPath() {
    return this->diagonalPath;
}

void Raiboo::AStarImpl::enableDiagonalPath(bool diagonalPath) {
    this->diagonalPath = diagonalPath;
}
