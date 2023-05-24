#include "coin.h"
#include <QPixmap>
#include <QPainter>
#include "pacman.h"

Coin::Coin(QWidget *parent)
    : QWidget{parent}
{

}

void Coin::draw(QPainter* painter){
    QPixmap pixmap;
    pixmap.load("media/coin.png");
    painter->drawPixmap(location.x(),location.y(),pixmap);

}

Coin::Coin(int x, int y){
    this->location.setX(x);
    this->location.setY(y);
}
