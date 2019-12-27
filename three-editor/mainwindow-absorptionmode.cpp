#include "mainwindow.h"
#include "ui_mainwindow.h"

struct MainWindow::AbsorptionMode : public MainWindow::WatchMode {
    vec3 beginPos;
    string beginMark,nameMarked;
    virtual function<bool(Controls::MouseButton,Controls::MouseEventType,vec2,vec2)> Handler();
};

void MainWindow::MainWindow_AbsorptionMode() {}

void MainWindow::on_action_absorption_toggled(bool checked) {
    if(checked) {
        auto mode = make_shared<AbsorptionMode>();
        *dynamic_cast<WatchMode*>(mode.get()) = *currentMode;
        currentMode = mode;
        auto box = ep->BoundBoxOfPick();
        cp->SetMouseOverEventHandler([=](auto xy) {
            auto it = bp->Intersect(xy[0],xy[1],0b10);

            if(mode->picks.end() == find_if(mode->picks.begin(),mode->picks.end(),[=](auto kv){
                return kv.second == it.second;
            })) return;

            ep->RemoveModel(mode->beginMark);
            if(!it.first.empty()) mode->beginMark = ep->makeMark(it.first);
            mode->nameMarked = it.second;
        });
        cp->SetMouseClickEventHandler(currentMode->Handler());
    } else {
        cp->SetMouseOverEventHandler(function<void(vec2)>());
        auto mode = dynamic_cast<AbsorptionMode*>(currentMode.get());
        ep->RemoveModel(mode->beginMark);
    }
}

function<bool(Controls::MouseButton,Controls::MouseEventType,vec2,vec2)> MainWindow::AbsorptionMode::Handler() {
    return [=](auto mb,auto met,auto xy,auto xyNormalized)->bool {
        if(mb != Controls::Left) return false;

        switch(met) {
        case Controls::DoubleClick:{
            auto c = bp->Intersect(xy[0],xy[1],0b11);
            if(!c.first.empty()) op->LookingFor(c.first);
            break;}
        case Controls::Push:{
            if(beginMark.empty()) break;
            auto it = bp->Intersect(xy[0],xy[1],0b10);
            beginPos = it.first;
            ep->MaskModel(nameMarked,0b100);
            break;}
        case Controls::Drag:{
            if(beginPos.empty() || beginMark.empty()) return false;
            auto endPos = bp->Intersect(xy[0],xy[1],0b11).first;
            if(endPos.empty()) return false;
            movePicksToPos(beginPos,endPos);
            fullPicksToSpinBox();
            beginPos=endPos;
            return false;}
        case Controls::Release:
            ep->MaskModel(nameMarked,0b10);
            ep->RemoveModel(beginMark);
            beginMark.clear();
            nameMarked.clear();
        }
        return true;
    };
}
