#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "interfaces.h"
#include "plugins/basic.h"
#include "plugins/animations.h"
#include "plugins/shadow.h"
#include "plugins/controls.h"
#include "plugins/observer.h"

#include <QMainWindow>
#include <QTimer>

using namespace ThreeQt;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = NULL);
    ~MainWindow();

    QTimer timer;
private slots:
    void paintGL();

private slots:
    void on_pushButton_2_clicked();
    void on_action_2_triggered();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_setColor_clicked();
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_pushButton_clicked();
    void on_checkBox_3_stateChanged(int arg1);
    void on_checkBox_5_stateChanged(int arg1);
    void on_checkBox_4_stateChanged(int arg1);
    void on_checkBox_7_stateChanged(int arg1);
    void on_checkBox_6_stateChanged(int arg1);
    void on_pushButton_trunAxis_clicked();
    void on_checkBox_teleport_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    ThreeWidget* tw;
    Basic* bp;
    Animations* ap;
    Shadow* sp;
    Controls* cp;
    Observer* op;
};

#endif // MAINWINDOW_H
