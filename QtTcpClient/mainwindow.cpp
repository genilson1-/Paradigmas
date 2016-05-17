#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  //tcpConnect();
  //putData();
  getData();
}


void MainWindow::on_Connect_pushButton_clicked()
{
    QString a;
    a = ui->IP_plainTextEdit->toPlainText();
    socket->connectToHost(a,1234);
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
    }
    else{
      qDebug() << "Disconnected";
    }
}



void MainWindow::getData()
{
  QString str;
  QByteArray array;
  QStringList list;
  QDateTime datetime;
  if(socket->isOpen()){
    socket->write("get 127.0.0.1\r\n");
    socket->waitForBytesWritten(3000);
    socket->waitForReadyRead(3000);
    qDebug() << socket->bytesAvailable();
    while(socket->bytesAvailable()){
      str = socket->readLine().replace("\n","").replace("\r","");
      list = str.split(" ");
      if(list.size() == 2){
        datetime.fromString(list.at(0),Qt::ISODate);
        str = list.at(1);
        qDebug() << datetime << ": " << str;
      }
    }
  }
}


void MainWindow::on_Start_pushButton_clicked()
{
    tempo = ui->horizontalSlider->value();
    startTimer(tempo*1000);

    min = ui->Min_plainTextEdit->toPlainText();
    max = ui -> Max_plainTextEdit -> toPlainText();
    maximo = max.toInt();
    minimo = min.toInt();
}

void MainWindow::timerEvent(QTimerEvent *e){
    id = e->timerId();
    QString txt;
    if(socket->isOpen()){
//      for(int i=0; i<10; i++){
        datetime = QDateTime::currentDateTime();
        str = "set "+
            datetime.toString(Qt::ISODate)+
            " "+
            QString::number(minimo + qrand()%(minimo - maximo))+"\r\n";

        qDebug() << str;
        ui->plainTextEdit->appendPlainText(str);
        socket->write(str.toStdString().c_str());
        socket->waitForBytesWritten(3000);


      }
 //   }

}


MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}



void MainWindow::on_Disconnect_pushButton_clicked()
{
    socket->close();
    //delete socket;
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
    }
    else{
      qDebug() << "Disconnected";
    }
}

void MainWindow::on_Stop_pushButton_clicked()
{
  killTimer(id);
}
