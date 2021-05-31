#ifndef COUNTINFO_H
#define COUNTINFO_H

#include <QWidget>
#include <QTime>
#include "ui_countinfo.h"

class countinfo : public QWidget
{
    Q_OBJECT
public:
    explicit countinfo(QWidget *parent = nullptr);
    ~countinfo();
    void setInfo(int index, QTime interval, QTime time);
    QString getInfo();
signals:


private:
    Ui::CountInfoWidget *ui;
public slots:
};

#endif // COUNTINFO_H
