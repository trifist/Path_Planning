#include "point.h"

Raiboo::Point::Point(int x, int y, int fValue, int gValue, int hValue) {
    this->x = x;
    this->y = y;
    this->fValue = fValue;
    this->gValue = gValue;
    this->hValue = hValue;
}

Raiboo::Point::Point() {
    this->x = 0;
    this->y = 0;
    this->fValue = 0;
    this->gValue = 0;
    this->hValue = 0;
}

Raiboo::Point::~Point() {

}

int Raiboo::Point::getfValue() {
    return this->fValue;
}

int Raiboo::Point::getgValue() {
    return this->gValue;
}

int Raiboo::Point::gethValue() {
    return this->hValue;
}

int Raiboo::Point::getPointType() {
    return this->pointType;
}

Raiboo::Point* Raiboo::Point::getParent() {
    return this->parent;
}

void Raiboo::Point::setfValue(int fValue) {
    this->fValue = fValue;
}

void Raiboo::Point::setgValue(int gValue) {
    this->gValue = gValue;
}

void Raiboo::Point::sethValue(int hValue) {
    this->hValue = hValue;
}

void Raiboo::Point::setPointType(int pointType) {
    this->pointType = pointType;
}

void Raiboo::Point::setParent(Point *parent) {
    this->parent = parent;
}
