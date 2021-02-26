#include "stopwatch.h"

Stopwatch::Stopwatch(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::showTime);
    //timer->start(10);
    this->setDigitCount(11);
    //showTime();
    display("00:00:00:00");

    setWindowTitle(tr("Stopwatch"));
    resize(400, 100);
}

Stopwatch::~Stopwatch()
{
}
//! [0]

//! [1]
void Stopwatch::showTime()
//! [1] //! [2]
{
    //QTime time = QTime::currentTime();

    QTime time(0,0,0);
    QTime t = time.addMSecs(num+=10);
    //t = time.addSecs()
    QString text = t.toString("hh:mm:ss.zzz").remove(11,1);
    //    if ((time.second() % 2) == 0)
    //        text[2] = ' ';
    display(text);
}
//! [2]
void Stopwatch::mousePressEvent(QMouseEvent *event)
{

    if(timer->isActive())
    {
        timer->stop();
    }
    else
    {
        timer->start(10);
    }
}
//! [3]
void Stopwatch::mouseDoubleClickEvent(QMouseEvent *event)
{
    num =0;
    timer->stop();
    display("00:00:00:00");
}
