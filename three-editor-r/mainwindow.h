#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "interfaces.h"
#include "plugins/basic.h"
#include "plugins/editor.h"
#include "plugins/skybox.h"
#include "plugins/observer.h"
#include "plugins/picker.h"
#include "plugins/placer.h"
#include "plugins/stretcher.h"
#include "plugins/controller.h"
#include "plugins/recorder.h"
#include "plugins/shadow.h"

#include <QMainWindow>
#include <QTreeWidgetItem>

#include <memory>
using std::shared_ptr;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    ThreeQt::ThreeWidget* tw;
    ThreeQt::SkyBox* skp;
    ThreeQt::Editor* ep;
    ThreeQt::Basic* bp;
    ThreeQt::Observer* op;
    ThreeQt::Board* bop;
    ThreeQt::Recorder* rp;
    ThreeQt::Shadow* sp;

    shared_ptr<ThreeQt::Placer> plp;
    shared_ptr<ThreeQt::Picker> pip;

    QString filePath;
    string nameOfPosChanged;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void importModels(QString url);
    void setModelEventHandler(decltype(pip) pip);

private slots:
    void on_action_exportScene_triggered();
    void on_action_importPath_triggered();
    void on_action_clearPath_triggered();
    void on_action_openScene_triggered();
    void on_action_saveScene_triggered();
    void on_treeWidget_models_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_checkBox_scaleAll_stateChanged(int arg1);
    void on_doubleSpinBox_ratio_valueChanged(double arg1);
    void on_doubleSpinBox_xRatio_valueChanged(double arg1);
    void on_doubleSpinBox_yRatio_valueChanged(double arg1);
    void on_doubleSpinBox_zRatio_valueChanged(double arg1);
    void on_doubleSpinBox_horizontalDegrees_valueChanged(double arg1);
    void on_doubleSpinBox_xPos_valueChanged(double arg1);
    void on_doubleSpinBox_yPos_valueChanged(double arg1);
    void on_doubleSpinBox_zPos_valueChanged(double arg1);
    void on_action_cancel_triggered();
    void on_action_undo_triggered();
    void on_action_redo_triggered();
    void on_action_remove_triggered();
    void on_action_copy_triggered();
    void on_action_lockPath_triggered();
    void on_action_unlockPath_triggered();
    void on_action_group_triggered();
    void on_action_ungroup_triggered();
    void on_action_stretch_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
