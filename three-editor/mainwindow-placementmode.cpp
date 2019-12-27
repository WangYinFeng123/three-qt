#include "mainwindow.h"
#include "ui_mainwindow.h"

struct MainWindow::PlacementMode : public WatchMode {

};

static bool changed = false;

void MainWindow::on_treeWidget_models_itemDoubleClicked(QTreeWidgetItem *item, int column) {
    if(nullptr == item) return;
    auto path = item->data(0,Qt::ItemDataRole::UserRole).toString();
    if(path.isEmpty()) return;

    ui->action_cancel->activate(QAction::Trigger);
    modelPlaced = ep->AddModel(path.toLocal8Bit().data());
    ep->ModelTrans(modelPlaced,{0,0,0});
    ep->AxisRotate(modelPlaced,{1,0,0},90);
    ep->MaskModel(modelPlaced,0b100);

    cp->SetMouseOverEventHandler([=](auto xy)->bool {
        auto xyz = bp->Intersect(xy[0],xy[1],0b11).first;
        if(xyz.empty()) return false;
        ep->ModelTrans(modelPlaced,xyz);
        return true;
    });

    cp->SetMouseClickEventHandler([=](auto mb,auto met,auto xy,auto xyNormalized)->bool {
        if(met != Controls::Push) return false;
        switch(mb) {
        case Controls::Left:{
            auto newModelName = ep->CopyModel(modelPlaced);
            ep->MaskModel(newModelName,0b10);
            changed = true;
            break;}
        default:
            return false;
        }

        return true;
    });
}

void MainWindow::on_action_cancel_triggered()
{
    //清除放置对象
    ep->RemoveModel(modelPlaced);
    cp->SetMouseOverEventHandler(function<bool(vec2)>());
    cp->SetMouseClickEventHandler(currentMode->Handler());
    if(changed) currentMode->snapshoot();
}

void MainWindow::on_action_copy_triggered()
{
    changed = false;
    ui->action_cancel->activate(QAction::Trigger);

    if(currentMode->picks.empty()) return;
    auto model = currentMode->picks.begin()->second;
    modelPlaced = ep->CopyModel(model);
    ep->ModelTrans(modelPlaced,{0,0,0});
    ep->MaskModel(modelPlaced,0b100);

    cp->SetMouseOverEventHandler([=](auto xy)->bool {
        auto xyz = bp->Intersect(xy[0],xy[1],0b11).first;
        if(xyz.empty()) return false;
        ep->ModelTrans(modelPlaced,xyz);
        return true;
    });

    cp->SetMouseClickEventHandler([=](auto mb,auto met,auto xy,auto xyNormalized)->bool {
        if(met != Controls::Push) return false;
        switch(mb) {
        case Controls::Left:{
            auto newModelName = ep->CopyModel(modelPlaced);
            ep->MaskModel(newModelName,0b10);
            changed = true;
            break;}
        default:
            return false;
        }

        return true;
    });
}
