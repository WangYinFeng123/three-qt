#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <QThread>
#include <QTimer>

#include "interfaces.h"
#include "plugins/basic.h"
#include "plugins/controls.h"
#include "plugins/shadow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class ThreeWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initList(QString earthPath);
    bool initTab0();
    bool initTab1();
    bool initTab2();

private slots:
    void on_tabWidget_currentChanged(int index);
    void on_listWidget_names_itemClicked(QListWidgetItem *item);

private:
    Ui::MainWindow *ui;
    ThreeEarthWidget *opengl_earth;
    ThreeWidget *opengl_obliquePhotograpy,*opengl_dimensionalInspection;
    Basic::EarthPlugin *bp_earth;
    Basic::Plugin *bp_obliquePhotograpy,*bp_dimensionalInspection;
    Shadow::Plugin *sp_dimensionalInspection;
    Controls::EarthPlugin *cp_earth;
    Controls::Plugin *cp_obliquePhotograpy,*cp_dimensionalInspection;

};
#endif // MAINWINDOW_H
