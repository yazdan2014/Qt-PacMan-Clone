
#ifndef GAMEPANEL_H
#define GAMEPANEL_H


#include <QWidget>
#include <QPainter>

#include <thread>
#include <chrono>

#include "pacman.h"
#include "gridpoint.h"
#include "ghost.h"

class GamePanel : public QWidget
{

public:
    explicit GamePanel(QWidget* parent = nullptr);

    void paintEvent(QPaintEvent* event) override;
    void keyPressEvent(QKeyEvent *event) override;


    int getScore();
    void setScore(int);

    void gridPointsLocator();
    GridPoint* first_gridpoint = new GridPoint(165,297);
    GridPoint* ghost_first_gridpoint;



private:
    PacMan pacman;
    Ghost red_ghost;
    Ghost blue_ghost;

    int score = 0;
    std::thread* movementThread;
    std::thread* animationThread;
    std::thread* repaintThread;
Q_OBJECT

};

#endif // GAMEPANEL_H
