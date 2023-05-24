#include "coin.h"
#include <QPixmap>
#include <QPainter>

Coin::Coin(QWidget *parent)
    : QWidget{parent}
{

}

void Coin::draw(QPainter* painter){
    QPixmap pixmap;
    pixmap.load("media/pacman/left/3.png");
    painter->drawPixmap(location.x(),location.y(),50,50,pixmap);
}

Coin::Coin(int x, int y){
    this->location.setX(x);
    this->location.setY(y);
}
