#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QLCDNumber>
#include <QElapsedTimer>
#include <QTimer>
#include <QTime>

class Stopwatch : public QLCDNumber
{
    Q_OBJECT

public:
    Stopwatch(QWidget *parent = nullptr);
    ~Stopwatch();
private:
    long num=0;
    QTimer *timer;
private slots:
    void showTime();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
};
#endif // STOPWATCH_H
