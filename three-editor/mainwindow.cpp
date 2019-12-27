#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QTreeWidgetItem>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    radios(this)
{
    ui->setupUi(this);
    ui->widget_matrix->hide();
    radios.addAction(ui->action_watch);
    radios.addAction(ui->action_move);
    radios.addAction(ui->action_absorption);

    tw = CreateThreeWidget();
    reinterpret_cast<QWidget*>(tw)->setFocusPolicy(Qt::StrongFocus);
    reinterpret_cast<QWidget*>(tw)->setMouseTracking(true);
    delete centralWidget();
    setCentralWidget(reinterpret_cast<QWidget*>(tw));

    importModels("./default-models");

    bp = new Basic(tw);
    ep = new Editor(tw);
    op = new Observer(tw);
    cp = new Controls(tw);
    sp = new Shadow(tw);
    skp = new SkyBox(tw);

    ep->MakeBase("base.osg",{0,0,0},250,1000);
    ep->MaskModel(bp->OpenScene("base.osg"),0b1);

    skp->CreateSkyBox("sky/");

    MainWindow_WatchMode();
    MainWindow_MoveMode();
    MainWindow_AbsorptionMode();
    ui->action_watch->activate(QAction::Trigger);
}

MainWindow::~MainWindow()
{
    delete bp;
    delete skp;
    delete sp;
    delete ep;
    delete cp;
    delete op;
    DestoryThreeWidget(tw);
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

void MainWindow::on_action_open_triggered() {
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
    auto url = QFileDialog::getOpenFileName(this,"","",QString::fromLocal8Bit("模型文件 (*osgb *.OSGB *.osg *.OSG *.fbx *.FBX)"));
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
    if(url.isEmpty()) return;

    if(!ep->OpenScene(url.toLocal8Bit().data())) {cout << "failed to open scene." ;return;}
    filePath = url.toLocal8Bit().data();

    this->setWindowTitle(filePath.data());
}

void MainWindow::on_action_save_triggered()
{
    QString url;
    if(filePath.empty()) {
        reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
        url = QFileDialog::getSaveFileName(this,"","","Scene (*.osgb)");
        if(-1 == url.indexOf(".osgb")) url += ".osgb";
        reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
    }

    if(url.isEmpty() && filePath.empty()) return;
    currentMode->unpickAll();
    if(ep->SaveScene(filePath.empty() ? url.toLocal8Bit().data() : filePath)) {
        if(filePath.empty())
            filePath = url.toLocal8Bit().data();
        this->setWindowTitle(filePath.data());
        QMessageBox::information(nullptr,"Three Qt Editor","Save scene to osgb file success!");
    } else
        QMessageBox::critical(nullptr,"Three Qt Editor","Export scene to osgb file success!");
}

void MainWindow::on_action_close_triggered()
{
    delete ep;
    ep = new Editor(tw);
    filePath.clear();
    this->setWindowTitle("Three Qt Editor");
}

void MainWindow::on_action_export_triggered()
{
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
    auto url = QFileDialog::getSaveFileName(this,"","","Web Scene (*.obj)");
    if(-1 == url.indexOf(".obj")) url += ".obj";
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);

    if(url.isEmpty()) return;
    currentMode->unpickAll();
    if(ep->SaveScene(url.toLocal8Bit().data()))
        QMessageBox::information(nullptr,"Three Qt Editor","Export scene to obj file success!");
    else
        QMessageBox::critical(nullptr,"Three Qt Editor","Export scene to obj file success!");
}

void MainWindow::on_action_undo_triggered()
{
    if(currentMode->snapshoots.empty()) return;
    auto ss = currentMode->snapshoots.back();
    currentMode->snapshoots.pop_back();
    ep->Snapshoot(ss);
    cout << "snapshoot:" << ss << endl;
}

void MainWindow::on_action_redo_triggered()
{

}

void MainWindow::on_action_shadow_toggled(bool arg1)
{
    sp->Lighting(arg1);
}
