#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "countinfo.h"
#include <QScrollBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Stopwatchwidget, &Stopwatch::counttime, this, &MainWindow::oncounttime);
    connect(ui->Stopwatchwidget, &Stopwatch::intervaltime, this, &MainWindow::onupdate_statusbar);
    connect(ui->Stopwatchwidget, &Stopwatch::timerstatus, this, &MainWindow::onupdate_action);
    ui->actionReset->setEnabled(false);
    ui->actionRecord->setEnabled(false);

    m_docPath = new QString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::oncounttime(int index, QTime interval, QTime time)
{

    countinfo *info = new countinfo();
    info->setInfo(index, interval, time);
    ui->scrollAreaWidgetContents_Info->layout()->addWidget(info);
    ui->scrollArea->verticalScrollBar()->setValue(ui->scrollArea->verticalScrollBar()->maximumHeight());
}
/**
 * @brief MainWindow::on_actionRecord_triggered 单圈标记
 */
void MainWindow::on_actionRecord_triggered()
{
    if(ui->Stopwatchwidget->isRun())
    {
        ui->Stopwatchwidget->record();
    }

}
/**
 * @brief MainWindow::on_update_statusbar 开始记录以后在状态栏显示间隔时间，在此通过信号更新
 * @param t
 */
void MainWindow::onupdate_statusbar(QTime t)
{
    ui->statusbar->showMessage(QString("%1").arg(t.toString("hh:mm:ss.zzz").remove(11,1)));
}
/**
 * @brief MainWindow::on_actionReset_triggered 重置秒表 所有消息清空
 */
void MainWindow::on_actionReset_triggered()
{
    if(!ui->Stopwatchwidget->isRun())
    {
        ui->Stopwatchwidget->reset();
        ui->statusbar->showMessage("");
        int count = ui->scrollAreaWidgetContents_Info->layout()->count();
        if(!count)
        {
            return;
        }
        do
        {
            //删除列表内所有数据
            QWidget *p = ui->scrollAreaWidgetContents_Info->layout()->itemAt(--count)->widget();
            ui->scrollAreaWidgetContents_Info->layout()->removeWidget(p);
            delete p;

        }
        while(count);
    }
}

void MainWindow::onupdate_action(bool state)
{
    ui->actionRecord->setEnabled(state);
    ui->actionReset->setEnabled(!state);
}
/**
 * @brief MainWindow::on_actionSave_as_triggered 保存数据
 */
void MainWindow::on_actionSave_as_triggered()
{
    int count = ui->scrollAreaWidgetContents_Info->layout()->count();
    if(!count)
    {
        QMessageBox::warning(this, tr("Warning"),
                             tr("There is no data to save."));
        return;
    }
    QString strData = "";
    for(int i=0;i<count;++i)
    {
        countinfo *info = (countinfo*)ui->scrollAreaWidgetContents_Info->layout()->itemAt(i)->widget();
        strData += info->getInfo();
        strData += "\r\n";


    }


    QString filter = "Text File (*.txt)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save"), *m_docPath, filter, &filter,  QFileDialog::HideNameFilterDetails);
    if (fileName.isEmpty()) {
        return;
    }
    qDebug()<<fileName;
    *m_docPath = QFileInfo(fileName).path();


    QFile file(fileName);

    if (file.open(QFile::WriteOnly)) {
        file.write(strData.toUtf8());
        file.close();
    }
}
/**
 * @brief MainWindow::on_actionAbout_triggered about
 */
void MainWindow::on_actionAbout_triggered()
{

    QMessageBox::information(this, tr("About Stopwatch"),
                             tr(   "<b>Stopwatch</b><br>"
                                   "Version: " SOFTWARE_VERSION "<br>"
                                   "Email: 362002000@qq.com<br>"
                                   "Home Page: <a href=\"https://gitee.com/clggxxx/Stopwatch\">View Code On Gitee</a><br>"
                                   "Build Date: " __DATE__ "<br>" // 编译时间
                                   COPYRIGHT
                               ));
}
/**
 * @brief MainWindow::on_actionExit_triggered 退出
 */
void MainWindow::on_actionExit_triggered()
{
    close();
}
