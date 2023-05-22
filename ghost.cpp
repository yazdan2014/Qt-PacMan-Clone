
#include "ghost.h"
#include <QPainter>


#include <ctime>
#include <cstdlib>

Ghost::Ghost(QWidget *parent)
    : QWidget{parent}
{
    this->location.setX(858);
    this->location.setY(297);
    this->direction = Left;
}


void Ghost::directionHandler(){
    srand(time(0));
    if(current_destination->location.x() == this->location.x()){
        if(current_destination->location.y() > this->location.y()){
            this->direction = Down;
        }else if(current_destination->location.y() < this->location.y()){
            this->direction = Up;
        }
    }else{
        if(current_destination->location.x() > this->location.x()){
            this->direction = Right;
        }else if(current_destination->location.x() < this->location.x()){
            this->direction = Left;
        }
    }
}

void Ghost::randomNewDestination(){
    switch((rand() % 4) + 1){
    case 1:
        if(this->current_destination->up != NULL){

            this->current_destination = this->current_destination->up;

        }else if(this->current_destination->right != NULL){

            this->current_destination = this->current_destination->right;

        }else if(this->current_destination->down != NULL){

            this->current_destination = this->current_destination->down;

        }else if (this->current_destination->left != NULL){

            this->current_destination = this->current_destination->left;
        }
        break;


    case 2:
        if(this->current_destination->right != NULL){

            this->current_destination = this->current_destination->right;

        }else if(this->current_destination->down != NULL){

            this->current_destination = this->current_destination->down;

        }else if(this->current_destination->left != NULL){

            this->current_destination = this->current_destination->left;

        }else if (this->current_destination->up != NULL){

            this->current_destination = this->current_destination->up;
        }
        break;


    case 3:
        if(this->current_destination->down != NULL){

            this->current_destination = this->current_destination->down;

        }else if(this->current_destination->left != NULL){

            this->current_destination = this->current_destination->left;

        }else if (this->current_destination->up != NULL){

            this->current_destination = this->current_destination->up;

        }else if(this->current_destination->right != NULL){

            this->current_destination = this->current_destination->right;

        }
        break;

    case 4:
        if(this->current_destination->left != NULL){

            this->current_destination = this->current_destination->left;

        }else if (this->current_destination->up != NULL){

            this->current_destination = this->current_destination->up;

        }else if(this->current_destination->right != NULL){

            this->current_destination = this->current_destination->right;

        }else if(this->current_destination->down != NULL){

            this->current_destination = this->current_destination->down;

        }
        break;
    }
}
void Ghost::moveToDestination(){
    switch(this->direction){
    case Up:
        if(this->location.y() - this->movementScale < this->current_destination->location.y()){
            this->location.setY(this->current_destination->location.y());
            this->randomNewDestination();
            this->directionHandler();

        }else{
            this->location.setY(this->location.y() - this->movementScale);
        }

        break;

    case Right:
        if(this->location.x() + this->movementScale > this->current_destination->location.x()){
            this->location.setX(this->current_destination->location.x());
            this->randomNewDestination();
            this->directionHandler();
        }else{
            this->location.setX(this->location.x() + this->movementScale);
        }

        break;

    case Down:
        if(this->location.y() + this->movementScale > this->current_destination->location.y()){
            this->location.setY(this->current_destination->location.y());
            this->randomNewDestination();
            this->directionHandler();
        }else{
            this->location.setY(this->location.y() + this->movementScale);
        }

        break;

    case Left:
        if(this->location.x() - this->movementScale < this->current_destination->location.x()){
            this->location.setX(this->current_destination->location.x());
            this->randomNewDestination();
            this->directionHandler();
        }else{
            this->location.setX(this->location.x() - this->movementScale);
        }

        break;
    }
}

void Ghost::draw(QPainter* painter){
    QPixmap pixmap;
    switch(direction){
    case Left:
        pixmap.load("media/ghosts/red/left.png");
        break;

    case Up:
        pixmap.load("media/ghosts/red/up.png");
        break;

    case Right:
        pixmap.load("media/ghosts/red/right.png");
        break;

    case Down:
        pixmap.load("media/ghosts/red/down.png");
        break;
    }

    painter->drawPixmap(location.x(),location.y(),50,50,pixmap);
}
