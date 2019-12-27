#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "interfaces.h"
#include "plugins/basic.h"
#include "plugins/animations.h"
#include "plugins/shadow.h"
#include "plugins/controls.h"
#include "plugins/observer.h"
#include "plugins/editor.h"
#include "plugins/skybox.h"
using namespace ThreeQt;

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QActionGroup>

#include <iostream>
#include <functional>
#include <map>
#include <memory>
#include <tuple>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void MainWindow_WatchMode();
    void MainWindow_MoveMode();
    void MainWindow_AbsorptionMode();
    ~MainWindow();

    void importModels(QString url);
private slots:
    void on_action_open_triggered();
    void on_treeWidget_models_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_action_cancel_triggered();
    void on_spinBox_degrees_valueChanged(int arg1);
    void on_doubleSpinBox_ratio_valueChanged(double arg1);
    void on_spinBox_x_valueChanged(int arg1);
    void on_spinBox_y_valueChanged(int arg1);
    void on_spinBox_z_valueChanged(int arg1);
    void on_action_watch_triggered();
    void on_action_move_toggled(bool arg1);
    void on_action_absorption_toggled(bool arg1);
    void on_action_save_triggered();
    void on_action_close_triggered();
    void on_action_export_triggered();
    void on_action_import_triggered();
    void on_action_copy_triggered();
    void on_action_undo_triggered();
    void on_action_redo_triggered();

    void on_action_shadow_toggled(bool arg1);

private:
    Ui::MainWindow *ui;
    QActionGroup radios;
    string modelPlaced,filePath;

    ThreeWidget* tw;
    Basic* bp;
    Editor* ep;
    Observer* op;
    Controls* cp;
    Shadow* sp;
    SkyBox* skp;

    struct WatchMode {
        MainWindow* mw;
        Ui::MainWindow* ui;
        Basic* bp;
        Controls* cp;
        Observer* op;
        Editor* ep;
        bool changed;
        list<string> snapshoots;
        vec3 leftTopNormalized,leftTop;
        map<string,string> picks;
        virtual function<bool(Controls::MouseButton,Controls::MouseEventType,vec2,vec2)> Handler();
        void unpickAll();
        void fullPicksToSpinBox();
        void movePicksToPos(vec3 begin ,vec3 end);
        void snapshoot();
    };

    struct MoveMode;
    struct AbsorptionMode;
    struct PlacementMode;
    shared_ptr<WatchMode> currentMode;
};

#endif // MAINWINDOW_H
