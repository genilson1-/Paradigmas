#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QString>
#include <QDateTime>
#include <QWidget>
#include <vector>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QStringList list;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    vector<float> tempo_atual;
    vector<float> dados;

private slots:
    void on_Con_pushButton_clicked();

    void on_Disc_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_Start_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;

};

#endif // MAINWINDOW_H
