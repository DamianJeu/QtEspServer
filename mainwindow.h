#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "espserver.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonStop_clicked();

    void on_pushButtonStart_clicked();

    void add_ip_to_list(QString ip);
    void remove_ip_address(QString ip);

private:
    Ui::MainWindow *ui;
    EspServer *server;
};
#endif // MAINWINDOW_H
