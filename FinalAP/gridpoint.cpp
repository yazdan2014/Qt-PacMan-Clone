
#include "gridpoint.h"

GridPoint::GridPoint(QWidget *parent)
    : QWidget{parent}
{
}

GridPoint::GridPoint(int x, int y){
    this->location.setX(x);
    this->location.setY(y);
}
