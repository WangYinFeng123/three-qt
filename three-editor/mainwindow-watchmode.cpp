#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::MainWindow_WatchMode() {
    currentMode = make_shared<WatchMode>();
    currentMode->bp = bp;
    currentMode->ep = ep;
    currentMode->cp = cp;
    currentMode->op = op;
    currentMode->ui = ui;
    currentMode->mw = this;
}

void MainWindow::on_action_watch_triggered()
{
    auto mode = make_shared<WatchMode>();
    *mode = *currentMode;
    cp->SetMouseClickEventHandler(mode->Handler());
    currentMode = mode;
    mode->changed = false;
}

void MainWindow::on_spinBox_x_valueChanged(int) {on_spinBox_z_valueChanged(0);}

void MainWindow::on_spinBox_y_valueChanged(int) {on_spinBox_z_valueChanged(0);}

void MainWindow::on_spinBox_z_valueChanged(int) {
    auto mode = currentMode;
    if(mode->picks.empty()) return;
    mode->movePicksToPos(ep->BoundBoxOfPick().first,{double(ui->spinBox_x->value()),double(ui->spinBox_y->value()),double(ui->spinBox_z->value())});
    currentMode->changed = true;
}

void MainWindow::on_spinBox_degrees_valueChanged(int degrees) {
    auto mode = currentMode;
    if(mode->picks.empty()) return;
    for(auto name : mode->picks) ep->ModelRotateH(name.second,degrees);
    if(degrees == 360) ui->spinBox_degrees->setValue(0);
    currentMode->changed = true;
}

void MainWindow::on_doubleSpinBox_ratio_valueChanged(double ratio) {
    auto mode = currentMode;
    if(mode->picks.empty()) return;
    for(auto name : mode->picks) ep->ModelScale(name.second,ratio);
    currentMode->changed = true;
}

void MainWindow::WatchMode::snapshoot() {
    auto ss = ep->Snapshoot();
    snapshoots.emplace_back(ss);
    cout << "snapshoot:" << ss << endl;
}

function<bool(Controls::MouseButton,Controls::MouseEventType,vec2,vec2)> MainWindow::WatchMode::Handler() {
    return [=](auto mb,auto met,auto xy,auto xyNormalized)->bool {
        if(mb != Controls::Left) return false;

        switch(met) {
        case Controls::DoubleClick:{
            auto c = bp->Intersect(xy[0],xy[1],0b11);
            if(!c.first.empty()) op->LookingFor(c.first);
            break;}
        case Controls::Push:
            leftTopNormalized = xyNormalized;
            leftTop = xy;
            break;
        case Controls::Drag:
            ep->MakePlane("picker",leftTopNormalized,xyNormalized);
            break;
        case Controls::Release:
            if(leftTop.empty()) break;

            set<string> modelNamesPicked;
            if((leftTopNormalized[0] - xyNormalized[0]) < 0.1 && (leftTopNormalized[1] - xyNormalized[1]) < 0.05 ) {
                auto modelName = bp->Intersect(leftTop,0b10);
                if(!modelName.empty()) modelNamesPicked = { modelName };
            } else {
                modelNamesPicked = ep->PlaneIntersect(leftTop,xy,0b10);
            }

            unpickAll();

            for(auto name : modelNamesPicked) {
                cout << "picked:" << name << endl;
                ep->Pick(name);
                auto box = ep->BoundBox(name);
                picks[ep->MakePick(box.first,box.second,0b100)] = name;
            }

            if(modelNamesPicked.empty()) {
                ui->widget_matrix->hide();
            } else {
                ui->widget_matrix->show();
                fullPicksToSpinBox();
            }

            ep->MakePlane("picker",{0,0},{0,0});
            leftTop.clear();
            leftTopNormalized.clear();
        }

        return true;
    };
}

void MainWindow::WatchMode::unpickAll() {
    for(auto pick : picks) ep->RemoveModel(pick.first);
    ep->UnpickAll();

    if(changed) snapshoot();
    changed = false;
    picks.clear();
}

void MainWindow::WatchMode::movePicksToPos(vec3 begin ,vec3 end) {
    vec3 offsetPos {end[0] - begin[0],end[1] - begin[1],end[2] - begin[2]};

    for(auto pick : picks) {
        auto modelPos = ep->ModelTrans(pick.second);
        modelPos = {modelPos[0] + offsetPos[0],modelPos[1] +  offsetPos[1],modelPos[2] +  offsetPos[2]};
        ep->ModelTrans(pick.second,modelPos);

        auto draggerTrans = ep->ModelTrans(pick.first);
        draggerTrans = {draggerTrans[0] + offsetPos[0],draggerTrans[1] +  offsetPos[1],draggerTrans[2] +  offsetPos[2]};
        ep->ModelTrans(pick.first,draggerTrans);
    }
}

void MainWindow::WatchMode::fullPicksToSpinBox() {
    if(picks.empty()) return;

    vec3 modelTrans;
    if(1 < picks.size())
        modelTrans = ep->BoundBoxOfPick().first;
    else
        modelTrans = ep->BoundBox(picks.begin()->second).first;


    ui->spinBox_x->disconnect(SIGNAL(valueChanged(int)));
    ui->spinBox_y->disconnect(SIGNAL(valueChanged(int)));
    ui->spinBox_z->disconnect(SIGNAL(valueChanged(int)));

    ui->spinBox_x->setValue(modelTrans[0]);
    ui->spinBox_y->setValue(modelTrans[1]);
    ui->spinBox_z->setValue(modelTrans[2]);

    mw->connect(ui->spinBox_x,SIGNAL(valueChanged(int)),SLOT(on_spinBox_x_valueChanged(int)));
    mw->connect(ui->spinBox_z,SIGNAL(valueChanged(int)),SLOT(on_spinBox_y_valueChanged(int)));
    mw->connect(ui->spinBox_y,SIGNAL(valueChanged(int)),SLOT(on_spinBox_z_valueChanged(int)));

    if(1 < picks.size()) {
        ui->doubleSpinBox_ratio->clear();
        ui->spinBox_degrees->clear();
        return;
    }

    ui->spinBox_degrees->disconnect(SIGNAL(valueChanged(int)));
    ui->doubleSpinBox_ratio->disconnect(SIGNAL(valueChanged(double)));

    auto name = picks.begin()->second;
    auto modelRotate = ep->ModelRotate(name);
    auto modelScale = ep->ModelScale(name);
    ui->spinBox_degrees->setValue(get<0>(modelRotate));
    ui->doubleSpinBox_ratio->setValue(modelScale);

    mw->connect(ui->spinBox_degrees,SIGNAL(valueChanged(int)),SLOT(on_spinBox_degrees_valueChanged(int)));
    mw->connect(ui->doubleSpinBox_ratio,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_ratio_valueChanged(double)));
}
