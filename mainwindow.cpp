#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GLPanel = new QOpenGLPanel(this);
    setCentralWidget(GLPanel);
}

MainWindow::~MainWindow()
{
    delete ui;
}
