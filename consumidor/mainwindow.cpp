#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QString>
#include <ctime>
#include<algorithm>

using namespace std;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Con_pushButton_clicked()
{
    QString a;
    a = ui->Ip_plainTextEdit->toPlainText();
    socket->connectToHost(a,1234);
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
      //ui->plainTextEdit->appendPlainText("Conectado ao servidor");
    }
    else{
      qDebug() << "Disconnected";
    }
}

void MainWindow::on_Disc_pushButton_2_clicked()
{
    socket->close();
    if(socket->waitForConnected(3000)){
      qDebug() << "Connected";
    }
    else{
      qDebug() << "Disconnected";
      //ui->plainTextEdit->appendPlainText("Servidor desconectado");
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString str;
    ui->Host_listWidget->clear();

    if (socket->isOpen()) {
        socket->write("list\r\n");
        socket->waitForBytesWritten(3000);
        socket->waitForReadyRead(3000);
        qDebug() << socket->bytesAvailable();
        while(socket->bytesAvailable()){
          str = socket->readLine().replace("\n","").replace("\r","");
          qDebug() << str;
        }
        ui->Host_listWidget->addItem(str);

    }

}

void MainWindow::on_Start_pushButton_2_clicked()
{
    QString host, str;
    QDateTime aux;
    QDateTime primeiro,ultimo, current;
    current = QDateTime::currentDateTime();
    qDebug() <<"teste" << current;
    vector <float> tempo_dados;
    host = "get " + ui->Host_listWidget->currentItem()->text() + "\r\n";
    qDebug() << host;
    if(socket->isOpen()){
      socket->write(host.toStdString().c_str());
      socket->waitForBytesWritten(3000);
      socket->waitForReadyRead(3000);
      qDebug() << socket->bytesAvailable();

      int i = 0;
      while(socket->bytesAvailable()){
        str = socket->readLine().replace("\n","").replace("\r","");
        list = str.split(" ");
        qDebug() << list;
       // qDebug() << list.at(0);
      //  qDebug() << list.at(1);
        dados.push_back(list.at(1).toFloat());
        aux.fromString(list.at(0), Qt::ISODate);
//        qDebug() << "curr: " << current;
//        qDebug() << QDateTime::fromString(list.at(0), Qt::ISODate);
        tempo_atual.push_back((float)QDateTime::fromString(list.at(0), Qt::ISODate).secsTo(current));
         //current.secsTo(QDateTime::fromString(list.at(0), Qt::ISODate));
        //i++;

      }


    }

    if (tempo_atual.size() > 2) {
        if (tempo_atual.size() > 30) {
            tempo_atual.erase(tempo_atual.begin(), tempo_atual.end() -30);
        }
    }

    if (dados.size() > 2) {
        if (dados.size() > 30) {
            dados.erase(dados.begin(), dados.end() -30);
        }
    }

    for (int var = 0; var <tempo_atual.size(); var++) {
        tempo_atual[var] =( (tempo_atual[var] - tempo_atual[0])/(tempo_atual[tempo_atual.size() - 1] - tempo_atual[0]) );
        qDebug() << tempo_atual[var];

    }


    //qDebug() << dados[10];
    ui->widget->load(tempo_atual,dados);
}

