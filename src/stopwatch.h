#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QLCDNumber>
#include <QElapsedTimer>
#include <QTimer>
#include <QTime>
#include <QMenu>
#include <QMenuBar>
#include <QAction>

class Stopwatch : public QLCDNumber
{
    Q_OBJECT

public:
    Stopwatch(QWidget *parent = nullptr);
    ~Stopwatch();
    void record();
    bool isRun(){return timer->isActive();}
    void reset();
private:
    long num=0;
    long interval;
    int count = 0;
    bool isRecord = false;
    QTimer *timer;
signals:
    void counttime(int, QTime, QTime);
    void intervaltime(QTime t);
    void timerstatus(bool state);
private slots:
    void showTime();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};
#endif // STOPWATCH_H
