#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new EspServer(this);
    connect(server, &EspServer::newClientIp, this, &MainWindow::add_ip_to_list);
    connect(server, &EspServer::clientDisconnected, this, &MainWindow::remove_ip_address);
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

void MainWindow::remove_ip_address(QString ip)
{
    QString allText = ui->textBrowserIp->toPlainText();

    QStringList lines = allText.split("\n");

    QStringList processedLines;

    for (const QString &line : lines) {
        if (!line.contains(ip)) {
            processedLines.append(line);
        }
    }

    ui->textBrowserIp->clear();
    ui->textBrowserIp->setPlainText(processedLines.join("\n"));
}

