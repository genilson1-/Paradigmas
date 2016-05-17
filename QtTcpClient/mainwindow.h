#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include<QString>
#include<QDateTime>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();
   QDateTime datetime;
   QString str, min, max;
   int maximo, minimo;
   int tempo;
   int id;

  
//  void tcpConnect();
  void getData();
//  void putData();
  void timerEvent(QTimerEvent *e);
private slots:
  void on_Connect_pushButton_clicked();

  void on_Start_pushButton_clicked();


  void on_Disconnect_pushButton_clicked();

  void on_Stop_pushButton_clicked();

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
