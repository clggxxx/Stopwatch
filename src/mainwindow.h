#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include <QTime>
#include <QGridLayout>
#include "version.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void oncounttime(int index, QTime interval, QTime time);
    void onupdate_statusbar(QTime t);
    void onupdate_action(bool);
    void on_actionRecord_triggered();

    void on_actionReset_triggered();

    void on_actionSave_as_triggered();

    void on_actionAbout_triggered();

    void on_actionExit_triggered();

private:
    Ui::MainWindow *ui;
    QString *m_docPath;
};

#endif // MAINWINDOW_H
