#include "grafico.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QColor>
#include <cmath>
#include <QMouseEvent>
#include <QDebug>
#include "mainwindow.h"
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>

using namespace std;

Grafico::Grafico(QWidget *parent) : QWidget(parent){

}


void Grafico::load(vector<float> _times, vector<float> _dados){
    dados = _dados;
    tempo = _times;
    vector<float>::iterator dado_min = min_element(dados.begin(), dados.end());
    yi = *dado_min;
    vector<float>::iterator dado_max = max_element(dados.begin(), dados.end());
    yf = *dado_max;
    xi = *tempo.begin();
    xf = tempo[tempo.size()-1];
    vector<float>::iterator time = max_element(dados.begin(), dados.end());

    repaint();

}


void Grafico::paintEvent(QPaintEvent *e){
    QPainter painter(this);
    QBrush brush; // preenchimento
    QPen pen; // contorno

    painter.setRenderHint(QPainter::Antialiasing);

    // caneta de desenho de contornos do fundo do grafico
    pen.setColor(QColor(255,0,0));
    painter.setPen(pen);


    brush.setColor(QColor(255,255,0));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    // desenha o fundo da tela
    painter.drawRect(0,0,width()-1, height()-1);

    // desenha linha vermelha horiz no centro do grafico
    painter.drawLine(0,height()/2,width(),height()/2);

    // redefine a caneta para desenhar com azul
    pen.setColor(QColor(0,0,255));
    pen.setWidth(3);
    painter.setPen(pen);

    int wi = 0;
    int deltaSec = xi - xf;
    xi = 0;
   for (int x = 0; x <dados.size(); x++) {
        wi += width()/tempo.size();
        //qDebug() << width();
        painter.drawLine(xi,yi,wi,dados[x]);
        //qDebug() << height();
        xi = wi; yi = dados[x];
    }

}

