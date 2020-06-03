#include "mainwindow.h"
#include "pathconfigform.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>

#include <iostream>
#include <sstream>
using namespace std;

#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //用三维窗体替换默认的窗体
    tw = ThreeQt::createThreeWidget();
    reinterpret_cast<QWidget*>(tw)->setFocusPolicy(Qt::StrongFocus);
    reinterpret_cast<QWidget*>(tw)->setMouseTracking(true);
    delete centralWidget();
    setCentralWidget(reinterpret_cast<QWidget*>(tw));

    importModels("./default-models"); //导入默认模型到列表

    bp = new ThreeQt::Basic(tw);
    ep = new ThreeQt::Editor(tw);
    op = new ThreeQt::Observer(tw);
    bop = new ThreeQt::Board(tw);
    rp = new ThreeQt::Recorder(ep);
    pip = make_shared<ThreeQt::Picker>(ep);
    setModelEventHandler(pip);

    auto baseName = bp->createBase({-300 * 1000,-300 * 1000,0},600,1000);
    op->fixViewpoint();

    skp = new ThreeQt::SkyBox(tw);
    skp->skyBoxDraw("sky/");

    sp = new ThreeQt::Shadow(tw);
    sp->lighting(true);

    rp->snapshot();


}

MainWindow::~MainWindow()
{
    pip.reset();
    plp.reset();
    stp.reset();

    delete sp;
    delete rp;
    delete bop;
    delete bp;
    delete skp;
    delete ep;
    delete op;

    ThreeQt::destoryThreeWidget(tw);
    delete ui;
}

void MainWindow::importModels(QString url) {
    QDir d(url);
    const QString dir = d.dirName();
    const QString dirPath = d.path();

    ui->treeWidget_models->clear();
    auto rootItem = new QTreeWidgetItem({dir});

    QIcon models(":/ui/project/project"),folder(":/ui/project/folder"),document(":/ui/project/document");

    rootItem->setIcon(0,QIcon(models));
    rootItem->setData(0,Qt::ItemDataRole::ToolTipRole,dirPath);
    ui->treeWidget_models->addTopLevelItem(rootItem);
    ui->treeWidget_models->expandItem(rootItem);

    std::function<void(QDir,QTreeWidgetItem*)> listFiles;

    listFiles = [&](QDir dir,QTreeWidgetItem* currentItem) { //获取文件列表
        for(QFileInfo fileInfo : dir.entryInfoList(QDir::NoFilter,QDir::DirsFirst)) {
            if (fileInfo.fileName()=="." || fileInfo.fileName() == ".." || fileInfo.suffix() == "fbm")
                continue;

            auto fileName = fileInfo.isDir() ? fileInfo.fileName() + '/' : fileInfo.fileName();
            auto filePath = fileInfo.isDir() ? fileInfo.absoluteFilePath() + '/' : fileInfo.absoluteFilePath();
            auto fileItem = new QTreeWidgetItem(currentItem);
            fileItem->setText(0,fileName);
            fileItem->setIcon(0,fileInfo.isDir() ? folder : document);
            fileItem->setData(0,Qt::ItemDataRole::ToolTipRole,filePath);
            if(fileInfo.isDir()) listFiles(fileInfo.absoluteFilePath(),fileItem);
            else fileItem->setData(0,Qt::ItemDataRole::UserRole,filePath);
        }
    };

    listFiles(QDir(dirPath),rootItem);
}

void MainWindow::setModelEventHandler(decltype(pip) pip) {
    pip->setPickedEventHandler([this](set<string> names) {
        disconnect(ui->doubleSpinBox_horizontalDegrees,SIGNAL(valueChanged(double)),this,SLOT(on_doubleSpinBox_horizontalDegrees_valueChanged(double)));
        disconnect(ui->doubleSpinBox_xRatio,SIGNAL(valueChanged(double)),this,SLOT(on_doubleSpinBox_xRatio_valueChanged(double)));
        disconnect(ui->doubleSpinBox_yRatio,SIGNAL(valueChanged(double)),this,SLOT(on_doubleSpinBox_yRatio_valueChanged(double)));
        disconnect(ui->doubleSpinBox_zRatio,SIGNAL(valueChanged(double)),this,SLOT(on_doubleSpinBox_zRatio_valueChanged(double)));
        disconnect(ui->doubleSpinBox_xPos,SIGNAL(valueChanged(double)),this,SLOT(on_doubleSpinBox_xPos_valueChanged(double)));
        disconnect(ui->doubleSpinBox_yPos,SIGNAL(valueChanged(double)),this,SLOT(on_doubleSpinBox_yPos_valueChanged(double)));
        disconnect(ui->doubleSpinBox_zPos,SIGNAL(valueChanged(double)),this,SLOT(on_doubleSpinBox_zPos_valueChanged(double)));

        if(0 == names.size()) { //没有选中
            nameOfPosChanged = "";
            ui->doubleSpinBox_horizontalDegrees->setDisabled(true);
            ui->doubleSpinBox_xRatio->setDisabled(true);
            ui->doubleSpinBox_yRatio->setDisabled(true);
            ui->doubleSpinBox_zRatio->setDisabled(true);
            ui->doubleSpinBox_xPos->setDisabled(true);
            ui->doubleSpinBox_yPos->setDisabled(true);
            ui->doubleSpinBox_zPos->setDisabled(true);
            ui->checkBox_scaleAll->setDisabled(true);
        } else if(1 == names.size()) { //选中1个
            nameOfPosChanged = *names.begin();
            auto name = *names.begin();
            auto r = ep->modelRotate(name);
            auto s = ep->modelScale(name);
            auto p = ep->modelTrans(name);

            ui->doubleSpinBox_horizontalDegrees->setValue(get<1>(r));
            ui->doubleSpinBox_xRatio->setValue(get<0>(s));
            ui->doubleSpinBox_yRatio->setValue(get<1>(s));
            ui->doubleSpinBox_zRatio->setValue(get<2>(s));
            ui->doubleSpinBox_xPos->setValue(get<0>(p) / 1000);
            ui->doubleSpinBox_yPos->setValue(get<1>(p) / 1000);
            ui->doubleSpinBox_zPos->setValue(get<2>(p) / 1000);

            ui->doubleSpinBox_horizontalDegrees->setEnabled(true);
            ui->doubleSpinBox_xRatio->setEnabled(true);
            ui->doubleSpinBox_yRatio->setEnabled(true);
            ui->doubleSpinBox_zRatio->setEnabled(true);
            ui->doubleSpinBox_xPos->setEnabled(true);
            ui->doubleSpinBox_yPos->setEnabled(true);
            ui->doubleSpinBox_zPos->setEnabled(true);
            ui->checkBox_scaleAll->setEnabled(true);

        } else { //选中多个
            for(auto name : names) {
                nameOfPosChanged += nameOfPosChanged.empty() ? "" : ";";
                nameOfPosChanged += name;
            }

            ui->doubleSpinBox_horizontalDegrees->setEnabled(true);
            ui->doubleSpinBox_xRatio->setEnabled(true);
            ui->doubleSpinBox_yRatio->setEnabled(true);
            ui->doubleSpinBox_zRatio->setEnabled(true);
            ui->doubleSpinBox_xPos->setEnabled(true);
            ui->doubleSpinBox_yPos->setEnabled(true);
            ui->doubleSpinBox_zPos->setEnabled(true);
            ui->checkBox_scaleAll->setEnabled(true);
        }

        connect(ui->doubleSpinBox_horizontalDegrees,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_horizontalDegrees_valueChanged(double)));
        connect(ui->doubleSpinBox_xRatio,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_xRatio_valueChanged(double)));
        connect(ui->doubleSpinBox_yRatio,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_yRatio_valueChanged(double)));
        connect(ui->doubleSpinBox_zRatio,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_zRatio_valueChanged(double)));
        connect(ui->doubleSpinBox_xPos,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_xPos_valueChanged(double)));
        connect(ui->doubleSpinBox_yPos,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_yPos_valueChanged(double)));
        connect(ui->doubleSpinBox_zPos,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_zPos_valueChanged(double)));
    });

    static bool changed = false;
    pip->setChangedEventHandler([&](string name,ThreeQt::vec3 pos) {
        nameOfPosChanged = name;
        if(!ui->checkBox_xPosLocked->isChecked()) ui->doubleSpinBox_xPos->setValue(get<0>(pos) / 1000);
        if(!ui->checkBox_yPosLocked->isChecked()) ui->doubleSpinBox_yPos->setValue(get<1>(pos) / 1000);
        if(!ui->checkBox_zPosLocked->isChecked()) ui->doubleSpinBox_zPos->setValue(get<2>(pos) / 1000);

        changed = true;
    });

    pip->setChangedFinishedEventHandler([&]() {
        if(changed) {
            rp->snapshot();
        }
        changed = false;
    });
}

void MainWindow::on_action_exportScene_triggered()
{
    ui->action_cancel->activate(QAction::Trigger);

    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
    auto url = QFileDialog::getSaveFileName(this,"","","Web Scene (*.obj)");
    if(-1 == url.indexOf(".obj")) url += ".obj";
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
    if(url == ".obj") return;

    try {
        try { while(true) ep->modelRemove("line",false); } catch(...) {} //线段不兼容
        rp->snapshot();
        ep->sceneExport(url.toLocal8Bit().data());
        rp->restore();
    } catch(...) {
        QMessageBox::information(nullptr,"Three Qt Editor","Failed export scene to obj file!");
        return;
    }

    QFile file(url.replace(".obj",".mtl"));
    file.open(QFile::ReadOnly);
    QString mtl = file.readAll();
    mtl = mtl.replace(QRegularExpression(R"(map_Kd .+\.fbm/)"),"map_Kd ./maps/");
    file.close();

    QFile wfile(url);
    wfile.open(QFile::WriteOnly);
    wfile.write(mtl.toLocal8Bit());
    wfile.close();

    QMessageBox::information(nullptr,"Three Qt Editor","Export scene to obj file success!");
}

void MainWindow::on_action_importPath_triggered()
{
    ui->action_cancel->activate(QAction::Trigger);
    PathConfigForm dialog;
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
    auto ret = dialog.exec();
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
    if(ret == QDialog::Rejected) return;

    auto points = dialog.points;
    auto lines = dialog.lines;
    auto square = ep->modelAdd("path/square.FBX");
    ep->modelAxis(square,{1,0,0},90);
    ep->modelScale(square,{dialog.pointRatio,dialog.pointRatio,dialog.pointRatio});

    for(auto path : points) {
        auto isPoint = get<0>(path) == "Point";
        string name = ep->modelClone(square);
        string newName;
        int seed = 0;
        while(true) {
            newName = "nc_xunjianzuobiao:" + to_string(seed) + name;
            try { ep->modelRename(name,newName); } catch(...) { seed++; continue; }
            break;
        }

        ep->modelTrans(newName,{
           get<1>(path),
           get<2>(path),
           get<3>(path) + (isPoint ? dialog.pointZ : dialog.lineZ)
        });
    }

    for(auto path : lines) {
        ep->lineDraw({ get<1>(path)[0], get<1>(path)[1], dialog.lineZ },{ get<2>(path)[0], get<2>(path)[1], dialog.lineZ },5);
        //ep->lineDraw({ get<1>(path)[0], get<1>(path)[1], dialog.lineZ },{ get<2>(path)[0], get<2>(path)[1], dialog.lineZ });
    }

    ep->modelRemove(square);
    on_action_lockPath_triggered();
    rp->snapshot();
}

void MainWindow::on_action_clearPath_triggered()
{
    try { while(true) ep->modelRemove("line",false); } catch(...) {}
    try { while(true) ep->modelRemove("nc_xunjianzuobiao", false); } catch(...) {}
    rp->snapshot();
}

void MainWindow::on_action_openScene_triggered()
{
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
    auto url = QFileDialog::getOpenFileName(this,"","",QString::fromLocal8Bit("模型文件 (*osgb *.OSGB *.osg *.OSG *.fbx *.FBX)"));
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
    if(url.isEmpty()) return;

    try {
        ep->sceneOpen(url.toLocal8Bit().data());
        filePath = url;
        this->setWindowTitle(filePath);

        rp->snapshot();
    } catch(exception ex) {
        QMessageBox::information(nullptr,"Three Qt Editor",ex.what());
    }
}

void MainWindow::on_action_saveScene_triggered()
{
    ui->action_cancel->activate(QAction::Trigger);

    QString url;
    if(filePath.isEmpty()) {
        reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
        url = QFileDialog::getSaveFileName(this,"","","Scene (*.osgb)");
        if(-1 == url.indexOf(".osgb")) url += ".osgb";
        reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
        if(url == ".osgb") return;
    }

    if(url.isEmpty() && filePath.isEmpty()) return;

    try {
        ep->sceneSave(filePath.isEmpty() ? url.toLocal8Bit().data() : filePath.toLocal8Bit().data());
        if(filePath.isEmpty()) filePath = url.toLocal8Bit().data();
        this->setWindowTitle(filePath);
        QMessageBox::information(nullptr,"Three Qt Editor","Save scene to osgb file success!");
    } catch(exception ex) {
        QMessageBox::information(nullptr,"Three Qt Editor",ex.what());
    }
}

void MainWindow::on_treeWidget_models_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    stp = nullptr;
    pip = nullptr; //关闭选择模式
    ui->doubleSpinBox_horizontalDegrees->setDisabled(true);
    ui->doubleSpinBox_xRatio->setDisabled(true);
    ui->doubleSpinBox_yRatio->setDisabled(true);
    ui->doubleSpinBox_zRatio->setDisabled(true);
    ui->doubleSpinBox_xPos->setDisabled(true);
    ui->doubleSpinBox_yPos->setDisabled(true);
    ui->doubleSpinBox_zPos->setDisabled(true);

    if(nullptr == item) return;
    auto path = item->data(0,Qt::ItemDataRole::UserRole).toString();
    if(path.isEmpty()) return;

    plp = make_shared<ThreeQt::Placer>(ep);
    plp->modelPlaced(path.toLocal8Bit().data());
    plp->setPlacedEventHandler([&]() {
        rp->snapshot();
    });
}

void MainWindow::on_action_cancel_triggered()
{
    stp = nullptr;
    plp = nullptr;
    pip = make_shared<ThreeQt::Picker>(ep);
    setModelEventHandler(pip);
}

void MainWindow::on_action_undo_triggered()
{
    ui->action_cancel->activate(QAction::Trigger);
    rp->restore();
}

void MainWindow::on_action_redo_triggered()
{
 //   rp->redo();
}

void MainWindow::on_checkBox_scaleAll_stateChanged(int arg1)
{
    if(arg1 == 2) {
        ui->doubleSpinBox_ratio->setEnabled(true);
    } else if(arg1 == 0) {
        ui->doubleSpinBox_ratio->setDisabled(true);
    }
}

void MainWindow::on_doubleSpinBox_ratio_valueChanged(double arg1)
{
    for(auto kv : pip->picks()) {
        ep->modelScale(kv.first,{arg1,arg1,arg1});
        //pip->modelScale(kv.second,{x,ui->doubleSpinBox_yRatio->value(),ui->doubleSpinBox_zRatio->value()});
    }

    disconnect(ui->doubleSpinBox_xRatio,SIGNAL(valueChanged(double)));
    disconnect(ui->doubleSpinBox_yRatio,SIGNAL(valueChanged(double)));
    disconnect(ui->doubleSpinBox_zRatio,SIGNAL(valueChanged(double)));
    ui->doubleSpinBox_xRatio->setValue(arg1);
    ui->doubleSpinBox_yRatio->setValue(arg1);
    ui->doubleSpinBox_zRatio->setValue(arg1);
    connect(ui->doubleSpinBox_xRatio,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_xRatio_valueChanged(double)));
    connect(ui->doubleSpinBox_yRatio,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_yRatio_valueChanged(double)));
    connect(ui->doubleSpinBox_zRatio,SIGNAL(valueChanged(double)),SLOT(on_doubleSpinBox_zRatio_valueChanged(double)));
}

void MainWindow::on_doubleSpinBox_xRatio_valueChanged(double x)
{
    for(auto kv : pip->picks()) {
        ep->modelScale(kv.first,{x,ui->doubleSpinBox_yRatio->value(),ui->doubleSpinBox_zRatio->value()});
        //pip->modelScale(kv.second,{x,ui->doubleSpinBox_yRatio->value(),ui->doubleSpinBox_zRatio->value()});
    }
}

void MainWindow::on_doubleSpinBox_yRatio_valueChanged(double y)
{
    for(auto kv : pip->picks()) {
        ep->modelScale(kv.first,{ui->doubleSpinBox_xRatio->value(),y,ui->doubleSpinBox_zRatio->value()});
        //pip->modelScale(kv.second,{ui->doubleSpinBox_xRatio->value(),y,ui->doubleSpinBox_zRatio->value()});
    }
}

void MainWindow::on_doubleSpinBox_zRatio_valueChanged(double z)
{
    for(auto kv : pip->picks()) {
        ep->modelScale(kv.first,{ui->doubleSpinBox_xRatio->value(),ui->doubleSpinBox_yRatio->value(),z});
        //pip->modelScale(kv.second,{ui->doubleSpinBox_xRatio->value(),ui->doubleSpinBox_yRatio->value(),z});
    }
}

void MainWindow::on_doubleSpinBox_horizontalDegrees_valueChanged(double arg1)
{
    for(auto kv : pip->picks()) {
        pip->modelRotate(kv.first,{0,0,1},arg1);
    }
}

void MainWindow::on_doubleSpinBox_xPos_valueChanged(double x)
{
    pip->modelTrans(nameOfPosChanged,{x * 1000,ui->doubleSpinBox_yPos->value() * 1000,ui->doubleSpinBox_zPos->value() * 1000});
}

void MainWindow::on_doubleSpinBox_yPos_valueChanged(double y) {
    pip->modelTrans(nameOfPosChanged,{ui->doubleSpinBox_xPos->value() * 1000,y * 1000,ui->doubleSpinBox_zPos->value() * 1000});
}

void MainWindow::on_doubleSpinBox_zPos_valueChanged(double z) {
    pip->modelTrans(nameOfPosChanged,{ui->doubleSpinBox_xPos->value() * 1000,ui->doubleSpinBox_yPos->value() * 1000,z * 1000});
}

void MainWindow::on_action_remove_triggered() {
    if(!pip) return;
    for(auto kv : pip->picks()) {
        ep->modelRemove(kv.first);
    }

    pip->clear();

    if(!pip->picks().empty()) rp->snapshot();
}

void MainWindow::on_action_copy_triggered() {
    if(!pip) return;
    for(auto kv : pip->picks()) {
        cout << kv.first << endl;
        pip = nullptr; //关闭选择模式
        ui->doubleSpinBox_horizontalDegrees->setDisabled(true);
        ui->doubleSpinBox_xRatio->setDisabled(true);
        ui->doubleSpinBox_yRatio->setDisabled(true);
        ui->doubleSpinBox_zRatio->setDisabled(true);
        ui->doubleSpinBox_xPos->setDisabled(true);
        ui->doubleSpinBox_yPos->setDisabled(true);
        ui->doubleSpinBox_zPos->setDisabled(true);

        plp = make_shared<ThreeQt::Placer>(ep);
        plp->modelPlacedByName(kv.first);
        plp->setPlacedEventHandler([&]() {
            rp->snapshot();
        });
        break;
    }
}

void MainWindow::on_action_lockPath_triggered()
{
    auto names = ep->models();
    for(auto name : names) {
        if(-1 != name.find("line") || -1 != name.find("nc_xunjianzuobiao"))
            ep->modelMask(name,0b100);
    }
}

void MainWindow::on_action_unlockPath_triggered()
{
    auto names = ep->models();
    for(auto name : names) {
        if(-1 != name.find("line") || -1 != name.find("nc_xunjianzuobiao"))
            ep->modelMask(name,0b010);
    }
}

void MainWindow::on_action_group_triggered()
{
//    set<string> names;
//    for(auto kv : pip->picks()) names.insert(kv.first);
//    ui->action_cancel->activate(QAction::Trigger);
//    ep->group(names,0b010);
}

void MainWindow::on_action_ungroup_triggered()
{
//    set<string> names;
//    for(auto kv : pip->picks()) names.insert(kv.first);
//    ui->action_cancel->activate(QAction::Trigger);
//    for(auto name : names) ep->ungroup(name);
}

void MainWindow::on_action_stretch_triggered()
{
    pip = nullptr;
    plp = nullptr;
    stp = make_shared<ThreeQt::Stretcher>(ep);
}
