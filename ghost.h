
#ifndef GHOST_H
#define GHOST_H


#include <QObject>
#include <QWidget>
#include "gridpoint.h"
#include "pacman.h"

class Ghost : public QWidget
{
    Q_OBJECT
public:
    explicit Ghost(QWidget *parent = nullptr);
    void moveToDestination();
    void draw(QPainter* painter);

    QPoint location;
    Direction direction;
    GridPoint* current_destination;

    void directionHandler();
    void randomNewDestination();

    int movementScale = 10;
    bool is_moving = true;
    std::string color;

};

#endif // GHOST_H
