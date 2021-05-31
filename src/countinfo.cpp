#include "countinfo.h"

countinfo::countinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CountInfoWidget)
{
    ui->setupUi(this);
}

countinfo::~countinfo()
{
    delete ui;
}
/**
 * @brief countinfo::setInfo  设置要显示的内容
 * @param index 序号
 * @param interval 间隔时间
 * @param time 累计时间
 */
void countinfo::setInfo(int index, QTime interval, QTime time)
{
    ui->lbl_CountIndex->setText(QString("计次 %1").arg(index));
    ui->lbl_interval->setText(QString("间隔 %1").arg(interval.toString("hh:mm:ss.zzz").remove(11,1)));
    ui->lbl_time->setText(QString("%1").arg(time.toString("hh:mm:ss.zzz").remove(11,1)));

}
/**
 * @brief countinfo::getInfo 获取显示内容
 * @return
 */
QString countinfo::getInfo()
{
    return QString("%1 : %2 : %3").arg(ui->lbl_CountIndex->text()).arg(ui->lbl_interval->text()).arg(ui->lbl_time->text());
}
