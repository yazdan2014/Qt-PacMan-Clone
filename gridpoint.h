
#ifndef GRIDPOINT_H
#define GRIDPOINT_H


#include <QObject>
#include <QWidget>
#include <QPoint>

class GridPoint : public QWidget
{
    Q_OBJECT
public:
    explicit GridPoint(QWidget *parent = nullptr);
    explicit GridPoint(int , int);
    GridPoint* up = NULL;
    GridPoint* right = NULL;
    GridPoint* down = NULL;
    GridPoint* left = NULL;
    QPoint location;
};

#endif // GRIDPOINT_H
