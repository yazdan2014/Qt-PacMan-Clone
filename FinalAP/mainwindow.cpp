
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamepanel.h"
#include <QSize>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setContentsMargins(0,0,0,0);
    GamePanel* panel = new GamePanel(this);
    this->setCentralWidget(panel);
    this->setFixedSize(QSize(1080, 720));
    this->statusBar()->setSizeGripEnabled(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}


