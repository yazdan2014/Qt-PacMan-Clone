#ifndef COIN_H
#define COIN_H


#include <QWidget>
#include <QPoint>

class Coin : public QWidget
{
    Q_OBJECT
public:
    explicit Coin(QWidget *parent = nullptr);
    explicit Coin(int , int);
    QPoint location;
    bool is_collected;
    void draw(QPainter* painter);

};

#endif // COIN_H
