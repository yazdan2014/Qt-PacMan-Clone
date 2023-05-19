
#include "gamepanel.h"
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include<QDebug>
#include <QKeyEvent>

GamePanel::GamePanel(QWidget *parent)
: QWidget{parent}
{
    gridPointsLocator();

    this->setFocusPolicy(Qt::StrongFocus);

    this->pacman.current_destination = this->first_gridpoint->right;
    this->pacman.next_destination = this->first_gridpoint->right->right;

//    this->animationThread = new std::thread([this](){
//        while(true){
//            this->pacman.animation_state_handler();
//            this->repaint();
//            std::this_thread::sleep_for(std::chrono::milliseconds(300));
//        }
//    });

    this->movementThread = new std::thread([this](){
        while(true){
            this->pacman.moveToDestination();
            this->pacman.animation_state_handler();
            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    });
}

void GamePanel::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load("media/background.jpg");
    painter.drawPixmap(0,0,1080,720,pixmap);

    this->pacman.draw(&painter);

    QRect score_board(60,90, 50 , 50);
    QFont font=painter.font() ;
    font.setBold(true);
    font.setPointSize(30);
    painter.setPen(QColor(Qt::white));
    painter.setFont(font);
    painter.drawText(score_board, QString::fromStdString(std::to_string(this->score)));
}

void GamePanel::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Up:
        this->pacman.last_clicked_button = Up;
        break;
    case Qt::Key_Down:
        this->pacman.last_clicked_button = Down;
        break;
    case Qt::Key_Right:
        this->pacman.last_clicked_button = Right;
        break;
    case Qt::Key_Left:
        this->pacman.last_clicked_button = Left;
        break;
    }
    this->pacman.nextDestinationHandler();
}

void GamePanel::setScore(int new_score){
    score = new_score;
}

int GamePanel::getScore(){
    return score;
}

void GamePanel::gridPointsLocator(){
//    this->first_gridpoint;
    GridPoint* B1 = new GridPoint(317,297);
    GridPoint* C1 = new GridPoint(398,297);
    GridPoint* D1 = new GridPoint(398,232);
    GridPoint* E1 = new GridPoint(479,232);
    GridPoint* F1 = new GridPoint(180,170);
    GridPoint* G1 = new GridPoint(317,170);
    GridPoint* H1 = new GridPoint(398,170);
    GridPoint* I1 = new GridPoint(479,170);
    GridPoint* J1 = new GridPoint(180,108);
    GridPoint* K1 = new GridPoint(317,108);
    GridPoint* L1 = new GridPoint(398,108);
    GridPoint* M1 = new GridPoint(479,108);
    GridPoint* N1 = new GridPoint(180,25);
    GridPoint* O1 = new GridPoint(317,25);
    GridPoint* P1 = new GridPoint(479,25);

    this->first_gridpoint->right = B1;

    B1->left = this->first_gridpoint;
    B1->right = C1;
    B1->up = G1;

    C1->left = B1;
    C1->up =D1;

    D1->down = C1;
    D1->right = E1;

    E1->left = D1;
    E1->up = I1;

    F1->right = G1;
    F1->up = J1;

    G1->left = F1;
    G1->down = B1;
    G1->up = K1;

    H1->right= I1;
    H1->up = L1;

    I1->left = H1;
    I1->down = E1;

    J1->down = F1;
    J1->right = K1;
    J1->up = N1;

    K1->down = G1;
    K1->right = L1;
    K1->up =O1;
    K1->left =J1;

    L1->left = K1;
    L1->down  = H1;
    L1->right = M1;

    M1->left = L1;
    M1->up = P1;

    N1->right = O1;
    N1->down = J1;

    O1->left = N1;
    O1->down = K1;
    O1->right = P1;

    P1->left = O1;
    P1->down = M1;

}
