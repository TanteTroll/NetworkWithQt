#include <QDesktopWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "server.h"
#include "client.h"
#include "message.h"

#include <QDebug>
#include <iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QDesktopWidget *desktop = QApplication::desktop();

    ui->setupUi(this);
    Server *server = new Server();
    server->move(0,0);
    server->show();


    Client *client = new Client();
    client->move(desktop->width()/2,0);
    client->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
