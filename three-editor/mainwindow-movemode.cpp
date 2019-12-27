#include "mainwindow.h"
#include "ui_mainwindow.h"

struct MainWindow::MoveMode : public MainWindow::WatchMode {
    string draggerClicked,draggerPicked;
    vec3 beginPos;
    virtual function<bool(Controls::MouseButton,Controls::MouseEventType,vec2,vec2)> Handler();
};

void MainWindow::MainWindow_MoveMode() {}

void MainWindow::on_action_move_toggled(bool checked) {
    if(checked) {
        auto mode = make_shared<MoveMode>();
        *dynamic_cast<WatchMode*>(mode.get()) = *currentMode;
        currentMode = mode;
        auto box = ep->BoundBoxOfPick();

        mode->draggerPicked = ep->MakeTranslateAxisDragger(box.first,box.second,0b100);
        cp->SetMouseClickEventHandler(currentMode->Handler());
    } else {
        auto mode = dynamic_cast<MoveMode*>(currentMode.get());
        ep->RemoveModel(mode->draggerPicked);
    }
}

function<bool(Controls::MouseButton,Controls::MouseEventType,vec2,vec2)> MainWindow::MoveMode::Handler() {
    return [=](auto mb,auto met,auto xy,auto xyNormalized)->bool {
        if(mb != Controls::Left) return false;

        switch(met) {
        case Controls::DoubleClick:{
            auto c = bp->Intersect(xy[0],xy[1],0b11);
            if(!c.first.empty()) op->LookingFor(c.first);
            break;}
        case Controls::Push:{
            auto name = bp->Intersect(xy,0b100);
            if(name.empty()) {
                leftTopNormalized = xyNormalized;
                leftTop = xy;
                break;
            }

            draggerClicked = name;
            return false;}
        case Controls::Drag:{
            if(draggerClicked.empty()) {
                ep->MakePlane("picker",leftTopNormalized,xyNormalized);
                break;
            }

            auto beginPos = ep->BoundBoxOfPick().first;
            auto endPos = ep->ModelTrans(draggerClicked);
            movePicksToPos(beginPos,endPos);
            fullPicksToSpinBox();
            return false;}
        case Controls::Release:
            draggerClicked.clear();

            if(leftTop.empty()) break;

            ep->RemoveModel(draggerPicked);
            draggerPicked.clear();

            set<string> modelNamesPicked;
            if((leftTopNormalized[0] - xyNormalized[0]) < 0.1 && (leftTopNormalized[1] - xyNormalized[1]) < 0.05 ) {
                auto modelName = bp->Intersect(leftTop,0b10);
                if(!modelName.empty()) modelNamesPicked = { modelName };
            } else {
                modelNamesPicked = ep->PlaneIntersect(leftTop,xy,0b10);
            }

            unpickAll();

            for(auto name : modelNamesPicked) {
                ep->Pick(name);
                auto box = ep->BoundBox(name);
                picks[ep->MakePick(box.first,box.second,0b100)] = name;
            }

            if(modelNamesPicked.empty()) {
                ui->widget_matrix->hide();
            } else {
                ui->widget_matrix->show();
                auto box = ep->BoundBoxOfPick();
                draggerPicked = ep->MakeTranslateAxisDragger(box.first,box.second,0b100);
                fullPicksToSpinBox();
            }

            ep->MakePlane("picker",{0,0},{0,0});
            leftTop.clear();
            leftTopNormalized.clear();
        }
        return true;
    };
}
