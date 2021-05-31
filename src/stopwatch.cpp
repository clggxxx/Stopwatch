#include "stopwatch.h"

Stopwatch::Stopwatch(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Stopwatch::showTime);
    this->setDigitCount(11);
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
    QTime time(0,0,0);
    QTime t = time.addMSecs(num+=10);
    if(isRecord)
    {
        emit intervaltime(time.addMSecs(interval+=10));
    }

    QString text = t.toString("hh:mm:ss.zzz").remove(11,1);

    display(text);
}
//! [2]
void Stopwatch::mousePressEvent(QMouseEvent *event)
{

    Q_UNUSED(event);
    if(timer->isActive())
    {
        timer->stop();
        emit timerstatus(false);
    }
    else
    {
        timer->start(10);
        emit timerstatus(true);
    }

}
/**
 * @brief Stopwatch::mouseDoubleClickEvent 暂时屏蔽了双击事件，清空通过alt+C 来实现
 * @param event
 */
void Stopwatch::mouseDoubleClickEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
#if 0
    num = 0;
    interval = 0;
    isRecord = false;
    timer->stop();
    display("00:00:00:00");
#endif

}
/**
 * @brief Stopwatch::record 单圈标记记录
 */
void Stopwatch::record()
{
    isRecord = true;
    QTime time(0,0,0);
    QTime intervaltime;
    if(0 == interval)
    {
         intervaltime= time.addMSecs(num);
    }
    else
    {
        intervaltime= time.addMSecs(interval);
    }
    interval = 0;//重置间隔
    QTime t = time.addMSecs(num);
    emit counttime(++count, intervaltime, t);

}
/**
 * @brief Stopwatch::reset 通过UI重置
 */
void Stopwatch::reset()
{
    num = 0;
    interval = 0;
    count = 0;
    isRecord = false;
    timer->stop();
    display("00:00:00:00");
}
