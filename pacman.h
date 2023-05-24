
#ifndef PACMAN_H
#define PACMAN_H


#include <QObject>
#include <QWidget>
#include <QPoint>

#include "gridpoint.h"

enum Direction {
    Left,
    Right,
    Up,
    Down
};

class PacMan : public QWidget
{
    Q_OBJECT
public:
    explicit PacMan(QWidget *parent = nullptr);
    void moveToDestination();
    void draw(QPainter* painter);
    void animation_state_handler();

    QPoint location;
    Direction direction;
    GridPoint* current_destination;
    GridPoint* next_destination;
    Direction last_clicked_button;

    void nextDestinationHandler();
    void directionHandler();

    int movementScale = 1;
    bool is_moving = true;


private:
    int animation_state;
};

#endif // PACMAN_H
