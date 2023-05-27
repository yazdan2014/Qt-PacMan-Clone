
#include "gamepanel.h"
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QDebug>
#include <QKeyEvent>

GamePanel::GamePanel(QWidget *parent)
: QWidget{parent}
{
    this->red_ghost.color = "red";
    this->blue_ghost.color = "blue";

    gridPointsLocator();
    coinLocator();


    this->setFocusPolicy(Qt::StrongFocus);

    this->pacman.current_destination = this->first_gridpoint->right;
    this->pacman.next_destination = this->first_gridpoint->right->right;

    this->red_ghost.current_destination = this->ghost_first_gridpoint->left;
    this->blue_ghost.current_destination =this->ghost_first_gridpoint->left;

    this->animationThread = new std::thread([this](){
        while(true){
            this->pacman.animation_state_handler();
//            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));

        }
    });

    this->movementThread = new std::thread([this](){
        while(true){
            this->pacman.moveToDestination();
            this->red_ghost.moveToDestination();
            this->blue_ghost.moveToDestination();
            this->checkCoinCollected();
//            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            if (checkLose()){
                break;
            }
        }
    });

    this->repaintThread = new std::thread([this](){
        while(true){
            this->repaint();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            if (checkLose()){
                break;
            }
        }
    });
}

void GamePanel::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load("media/background.jpg");
    painter.drawPixmap(0,0,1080,720,pixmap);

    for(Coin* coin:coins){
        if(coin->is_collected) continue;
        coin->draw(&painter);
    }
    this->coins[50]->draw(&painter);

    this->pacman.draw(&painter);
    this->red_ghost.draw(&painter);
    this->blue_ghost.draw(&painter);



    QRect score_board(60,90, 100 , 50);
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

void GamePanel::checkCoinCollected(){
    for(Coin* coin:coins){
        if(coin->is_collected) continue;
        if((pacman.location.x() <= coin->location.x()+3 &&  pacman.location.x() + 30 >= coin->location.x() + 3)
            && (pacman.location.y() <= coin->location.y()+3 &&  pacman.location.y() + 30 >= coin->location.y() + 3)
            ){
            coin->is_collected = true;
            score++;
        }
    }

}

void GamePanel::setScore(int new_score){
    score = new_score;
}

int GamePanel::getScore(){
    return score;
}

bool GamePanel::checkLose(){
    if(((this->pacman.location.x()+15 <= this->blue_ghost.location.x()+30 &&  this->pacman.location.x()+15 >= this->blue_ghost.location.x())
         && (this->pacman.location.y()+15 <= this->blue_ghost.location.y()+30 &&  this->pacman.location.y()+15 >= this->blue_ghost.location.y()))
        ||
        ((this->pacman.location.x()+15 <= this->red_ghost.location.x()+30 &&  this->pacman.location.x()+15 >= this->red_ghost.location.x())
         && (this->pacman.location.y()+15 <= this->red_ghost.location.y()+30 &&  this->pacman.location.y()+15 >= this->red_ghost.location.y()))
        ){
        return true;
    }
    return false;
}

void GamePanel::coinLocator(){
    struct Coordinate{
        int x;
        int y;
    };

    std::vector<Coordinate> locations = {
        {334,289}, {334,268}, {334,247}, {334,226}, {334,205}, {334,184},
        {334,121}, {334,100}, {334,79},  {334,58},  {334,37},  {307,121},{334,163},
        {281,121}, {255,121}, {228,121}, {307,184}, {281,184}, {255,184},
        {229,184}, {202,184}, {202,163}, {202,142}, {202,121}, {202,100},
        {202,79},  {202,58},  {202,37},  {228,37},  {252,37},  {281,37},  //Layer 57
        {308,37},  {361,121}, {413,121}, {440,121}, {466,121}, {493,121}, //Layer 64
        {493,100}, {493,79},  {493,58},  {493,37},  {466,37},  {413,37},  //Layer 70
        {440,37},  {387,37},  {361,37},  {413,142}, {413,164}, {413,184}, //Layer 76
        {440,184}, {493,184}, {519,121}, {546,121}, {572,121}, //{465,184}, Layer 82
        {573,183}, {626,184}, {652,184}, {652,163}, {652,142}, {599,122}, //Layer 89
        {626,121}, {652,121}, {572,100}, {572,79},  {572,58},  {572,37},  //Layer 95
        {678,121}, {599,37},  {626,37},  {652,37},  {678,37},  {705,37},  //Layer 101
        {731,37},  {731,58},  {731,79},  {731,100}, {704,121}, {731,121}, //Layer 107
        {785,121}, {758,37},  {785,37},  {811,37},  {837,37},  {864,37},  //Layer 113
        {864,58},  {864,79},  {864,100}, {864,121}, {837,121}, {758,121}, //Layer 119
        {811,121}, {731,142}, {731,163}, {731,184}, {864,142}, {864,163}, //Layer 125
        {864,184}, {758,184}, {785,184}, {811,184}, {837,184}, {731,205}, //Layer 131
        {731,226}, {731,247}, {731,268}, {731,289}, {731,310}, {731,331}, //Layer 137
        {731,352}, {731,373}, {731,394}, {731,415}, {731,436}, {731,457}, //Layer 143
        {731,478}, {731,499}, {731,520}, {731,541}, {731,562}, {758,562}, //Layer 149
        {758,436}, {785,436}, {811,436}, {837,436}, {864,436}, {864,457}, //Layer 155
        {864,478}, {864,499}, {837,499}, {811,499}, {811,520}, {811,541}, //Layer 161
        {785,562}, {811,562}, {837,562}, {864,562}, {864,583}, {864,604}, //Layer 167
        {864,625}, {837,625}, {811,625}, {784,625}, {758,625}, {731,625}, //Layer 173
        {705,625}, {678,625}, {652,625}, {625,625}, {599,625}, {573,625}, //Layer 179
        {546,625}, {519,625}, {493,625}, {466,625}, {440,625}, {387,625}, //Layer 186
        {361,625}, {334,625}, {308,625}, {281,625}, {255,625}, {228,625}, //Layer 192
        {202,625}, {202,604}, {202,583}, {202,562}, {228,562}, {255,562}, //Layer 198
        {281,562}, {308,562}, {334,562}, {334,541}, {334,520}, {334,499}, //Layer 204
        {360,499}, {334,478}, {334,457}, {254,541}, {254,520}, {255,499}, //Layer 210
        {228,499}, {202,499}, {202,478}, {202,457}, {202,436}, {228,436}, //Layer 216
        {255,436}, {281,436}, {308,436}, {334,436}, {361,436}, {334,415}, //Layer 222
        {334,394}, {334,373}, {334,352}, {334,332}, {334,310}, {387,436}, //Layer 228
        {413,436}, {440,436}, {466,436}, {493,436}, {493,457}, {493,478}, //Layer 234
        {493,499}, {387,499}, {413,499}, {440,499}, {467,499}, {413,519}, //Layer 240
        {413,542}, {413,562}, {440,562}, {466,562}, {493,562}, {493,583}, //Layer 246
        {493,604}, {573,604}, {573,583}, {573,562}, {599,562}, {626,562}, //Layer 252
        {652,562}, {652,541}, {652,519}, {652,499}, {679,499}, {705,499}, //Layer 258
        {626,499}, {599,499}, {572,499}, {572,478}, {572,457}, {572,436}, //Layer 264
        {599,436}, {626,436}, {652,436}, {678,436}, {705,436}, {413,625}, //Layrt 270
        {599,184}, {387,121}, {334,142}
    };

    for(auto coordinate:locations){
        Coin* new_coin = new Coin(coordinate.x, coordinate.y);
        this->coins.push_back(new_coin);

    }
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


    GridPoint* A2 = new GridPoint(643,297);
    GridPoint* B2 = new GridPoint(721,297);
    GridPoint* C2 = new GridPoint(858,297);
    GridPoint* D2 = new GridPoint(559,232);
    GridPoint* E2 = new GridPoint(643,232);
    GridPoint* F2 = new GridPoint(559,170);
    GridPoint* G2 = new GridPoint(643,170);
    GridPoint* H2 = new GridPoint(721,170);
    GridPoint* I2 = new GridPoint(858,170);
    GridPoint* J2 = new GridPoint(559,108);
    GridPoint* K2 = new GridPoint(643,108);
    GridPoint* L2 = new GridPoint(721,108);
    GridPoint* M2 = new GridPoint(858,108);
    GridPoint* N2 = new GridPoint(559,25);
    GridPoint* O2 = new GridPoint(721,25);
    GridPoint* P2 = new GridPoint(858,25);

    GridPoint* A3 = new GridPoint(398,360);
    GridPoint* B3 = new GridPoint(180,424);
    GridPoint* C3 = new GridPoint(317,424);
    GridPoint* D3 = new GridPoint(398,424);
    GridPoint* E3 = new GridPoint(479,424);
    GridPoint* F3 = new GridPoint(180,485);
    GridPoint* G3 = new GridPoint(237,485);
    GridPoint* H3 = new GridPoint(317,485);
    GridPoint* I3 = new GridPoint(398,485);
    GridPoint* J3 = new GridPoint(479,485);
    GridPoint* K3 = new GridPoint(180,549);
    GridPoint* L3 = new GridPoint(237,549);
    GridPoint* M3 = new GridPoint(317,549);
    GridPoint* N3 = new GridPoint(398,549);
    GridPoint* O3 = new GridPoint(479,549);
    GridPoint* P3 = new GridPoint(180,613);
    GridPoint* Q3 = new GridPoint(479,613);

    GridPoint* A4 = new GridPoint(643,360);
    GridPoint* B4 = new GridPoint(559,424);
    GridPoint* C4 = new GridPoint(643,424);
    GridPoint* D4 = new GridPoint(721,424);
    GridPoint* E4 = new GridPoint(858,424);
    GridPoint* F4 = new GridPoint(559,485);
    GridPoint* G4 = new GridPoint(643,485);
    GridPoint* H4 = new GridPoint(721,485);
    GridPoint* I4 = new GridPoint(801,485);
    GridPoint* J4 = new GridPoint(858,485);
    GridPoint* K4 = new GridPoint(559,548);
    GridPoint* L4 = new GridPoint(643,548);
    GridPoint* M4 = new GridPoint(721,548);
    GridPoint* N4 = new GridPoint(801,548);
    GridPoint* O4 = new GridPoint(858,548);
    GridPoint* P4 = new GridPoint(559,613);
    GridPoint* Q4 = new GridPoint(858,613);

    this->first_gridpoint->right = B1;

    B1->left = this->first_gridpoint;
    B1->right = C1;
    B1->up = G1;
    B1->down = C3;

    C1->left = B1;
    C1->up =D1;
    C1->down = A3;

    D1->down = C1;
    D1->right = E1;

    E1->left = D1;
    E1->up = I1;
    E1->right = D2;

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
    M1->right = J2;

    N1->right = O1;
    N1->down = J1;

    O1->left = N1;
    O1->down = K1;
    O1->right = P1;

    P1->left = O1;
    P1->down = M1;



    A2->up = E2;
    A2->right = B2;
    A2->down = A4;

    B2->up = H2;
    B2->left = A2;
    B2->right = C2;
    B2->down = D4;

    C2->left = B2;
    this->ghost_first_gridpoint = C2;

    D2->right = E2;
    D2->left = E1;
    D2->up = F2;

    E2->down = A2;
    E2->left = D2;

    F2->right = G2;
    F2->down = D2;

    G2->left = F2;
    G2->up = K2;

    H2->right = I2;
    H2->up = L2;
    H2->down = B2;

    I2->left = H2;
    I2->up = M2;

    J2->right = K2;
    J2->up = N2;
    J2->left = M1;

    K2->right = L2;
    K2->down = G2;
    K2->left = J2;

    L2->up = O2;
    L2->right = M2;
    L2->left = K2;
    L2->down = H2;

    M2->up = P2;
    M2->left = L2;
    M2->down = I2;

    N2->right = O2;
    N2->down = J2;

    O2->left = N2;
    O2->down = L2;
    O2->right = P2;

    P2->left = O2;
    P2->down = M2;



    A3->up = C1;
    A3->down = D3;
    A3->right = A4;

    B3->right = C3;
    B3->down = F3;

    C3->up = B1;
    C3->left = B3;
    C3->right = D3;
    C3->down = H3;

    D3->up = A3;
    D3->right = E3;
    D3->left = C3;

    E3->left = D3;
    E3->down = J3;

    F3->right = G3;
    F3->up = B3;

    G3->left = F3;
    G3->down = L3;

    H3->up = C3;
    H3->right = I3;
    H3->down = M3;

    I3->right = J3;
    I3->down = N3;
    I3->left = H3;

    J3->up = E3;
    J3->left = I3;
    J3->right = F4;

    K3->right = L3;
    K3->down = P3;

    L3->left = K3;
    L3->up = G3;
    L3->right = M3;

    M3->up = H3;
    M3->left = L3;

    N3->up = I3;
    N3->right = O3;

    O3->left = N3;
    O3->down = Q3;

    P3->right = Q3;
    P3->up = K3;

    Q3->up= O3;
    Q3->left = P3;
    Q3->right = P4;



    A4->up = A2;
    A4->left = A3;
    A4->down = C4;

    B4->right = C4;
    B4->down = F4;

    C4->up = A4;
    C4->right = D4;
    C4->left = B4;

    D4->up = B2;
    D4->left = C4;
    D4->down = H4;
    D4->right = E4;

    E4->left = D4;
    E4->down = J4;

    F4->left = J3;
    F4->up = B4;
    F4->right =G4;

    G4->left = F4;
    G4->down = L4;
    G4->right= H4;

    H4->up = D4;
    H4->left = G4;
    H4->down = M4;

    I4->down = N4;
    I4->right = J4;

    J4->up = E4;
    J4->left = I4;

    K4->right = L4;
    K4->down = P4;

    L4->left = K4;
    L4->up = G4;

    M4->up = H4;
    M4->right = N4;

    N4->left = M4;
    N4->up = I4;
    N4->right = O4;

    O4->left = N4;
    O4->down = Q4;

    P4->left = Q3;
    P4->right = Q4;
    P4->up = K4;

    Q4->up = O4;
    Q4->left = P4;
}


