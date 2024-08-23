#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new EspServer(this);
    connect(server, &EspServer::newClientIp, this, &MainWindow::add_ip_to_list);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonStop_clicked()
{
    server->serverStop();
}


void MainWindow::on_pushButtonStart_clicked()
{
    server->startServer();
}

void MainWindow::add_ip_to_list(QString ip)
{

    ui->textBrowserIp->append(ip);
}

