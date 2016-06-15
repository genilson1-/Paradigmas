#ifndef GRAFICO_H
#define GRAFICO_H
#include<vector>

#include <QWidget>
using namespace std;

class Grafico : public QWidget{
    Q_OBJECT
public:
    explicit Grafico(QWidget *parent = 0);
    void load(vector<float> _times, vector<float> _dados);
    vector<float> dados, tempo;
    float xi, yi, xf, yf;

protected:
  void paintEvent(QPaintEvent *e);
//  void timerEvent(QTimerEvent *e);
  //void mouseMoveEvent(QMouseEvent *e);

};

#endif // GRAFICO_H
