
#include "pacman.h"
#include <QPainter>
#include<QDebug>

PacMan::PacMan(QWidget *parent)
    : QWidget{parent}
{
    this->location.setX(165);
    this->location.setY(297);
//    this->location.setX(260);
//    this->location.setY(170);
    this->direction = Right;
    this->animation_state = 1;
    this->last_clicked_button = Right;

}

//void PacMan::keepGoingOrStop(){
//    switch (this->direction) {
//    case Up:
//        if(this->current_destination->up != NULL){
//            this->next_destination = this->current_destination->up;
//        }else{
//            this->is_moving = false;
//            this->next_destination = NULL;
//        }
//        break;

//    case Right:
//        if(this->current_destination->right != NULL){
//            this->next_destination = this->current_destination->right;
//        }else{
//            this->is_moving = false;
//            this->next_destination = NULL;
//        }
//        break;

//    case Down:
//        if(this->current_destination->down != NULL){
//            this->next_destination = this->current_destination->down;
//        }else{
//            this->is_moving = false;
//            this->next_destination = NULL;
//        }
//        break;

//    case Left:
//        if(this->current_destination->left != NULL){
//            this->next_destination = this->current_destination->left;
//        }else{
//            this->is_moving = false;
//            this->next_destination = NULL;
//        }
//        break;

//    }
//}

void PacMan::nextDestinationHandler(){
    switch(last_clicked_button){
        case Up:
            if(this->current_destination->up != NULL){
                this->is_moving = true;
                this->next_destination = this->current_destination->up;
            }
            else{
//                this->keepGoingOrStop();
            }
            break;
        case Right:
            if(this->current_destination->right != NULL){
                this->next_destination = this->current_destination->right;
                this->is_moving = true;
            }
            else{
//                this->keepGoingOrStop();
            }
            break;
        case Down:
            if(this->current_destination->down != NULL){
                this->next_destination = this->current_destination->down;
                this->is_moving = true;
            }else{
//                this->keepGoingOrStop();
            }
            break;
        case Left:
            if(this->current_destination->left != NULL){
                this->next_destination = this->current_destination->left;
                this->is_moving = true;
            }
            else{
//                this->keepGoingOrStop();
            }
            break;
    }
}

void PacMan::moveToDestination(){
    switch(this->direction){
        case Up:
            if(this->location.y() - this->movementScale < this->current_destination->location.y()){
                this->location.setY(this->current_destination->location.y());
                this->current_destination = this->next_destination;
                this->nextDestinationHandler();
                this->direction = this->last_clicked_button;
            }else{
                this->location.setY(this->location.y() - this->movementScale);
            }

            break;

        case Right:
            if(this->location.x() + this->movementScale > this->current_destination->location.x()){
                this->location.setX(this->current_destination->location.x());
                this->current_destination = this->next_destination;
                this->nextDestinationHandler();
                this->direction = this->last_clicked_button;
            }else{
                this->location.setX(this->location.x() + this->movementScale);
            }

            break;

        case Down:
            if(this->location.y() + this->movementScale > this->current_destination->location.y()){
                this->location.setY(this->current_destination->location.y());
                this->current_destination = this->next_destination;
                this->nextDestinationHandler();
                this->direction = this->last_clicked_button;
            }else{
                this->location.setY(this->location.y() + this->movementScale);
            }

            break;

        case Left:
            if(this->location.x() - this->movementScale < this->current_destination->location.x()){
                this->location.setX(this->current_destination->location.x());
                this->current_destination = this->next_destination;
                this->nextDestinationHandler();
                this->direction = this->last_clicked_button;
            }else{
                this->location.setX(this->location.x() - this->movementScale);
            }

            break;
    }
}

void PacMan::draw(QPainter* painter){
    QPixmap pixmap;
    switch(direction){
        case Left:
            switch(this->animation_state){
                case 1:
                    pixmap.load("media/pacman/left/1.png");
                    break;
                case 2:
                    pixmap.load("media/pacman/left/2.png");
                    break;
                case 3:
                    pixmap.load("media/pacman/left/3.png");
                    break;
                case 4:
                    pixmap.load("media/pacman/left/2.png");
                    break;
            }
        break;

        case Up:
            switch(this->animation_state){
                case 1:
                    pixmap.load("media/pacman/up/1.png");
                    break;
                case 2:
                    pixmap.load("media/pacman/up/2.png");
                    break;
                case 3:
                    pixmap.load("media/pacman/up/3.png");
                    break;
                case 4:
                    pixmap.load("media/pacman/up/2.png");
                    break;
            }
        break;

        case Right:
            switch(this->animation_state){
            case 1:
                    pixmap.load("media/pacman/right/1.png");
                    break;
            case 2:
                    pixmap.load("media/pacman/right/2.png");
                    break;
            case 3:
                    pixmap.load("media/pacman/right/3.png");
                    break;
            case 4:
                    pixmap.load("media/pacman/right/2.png");
                    break;
            }
        break;

        case Down:
            switch(this->animation_state){
            case 1:
                    pixmap.load("media/pacman/down/1.png");
                    break;
            case 2:
                    pixmap.load("media/pacman/down/2.png");
                    break;
            case 3:
                    pixmap.load("media/pacman/down/3.png");
                    break;
            case 4:
                    pixmap.load("media/pacman/down/2.png");
                    break;
            }
        break;
    }

    painter->drawPixmap(location.x(),location.y(),50,50,pixmap);
}

void PacMan::animation_state_handler(){
    if(this->animation_state == 1 || this->animation_state == 2 || this->animation_state == 3){
        this->animation_state++;
    }else{
        this->animation_state = 1;
    }
}
