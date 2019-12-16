#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "json/reader.h"
#include "json/writer.h"
#include "json/value.h"

#include <QDir>
#include <QSettings>
#include <QtXml/QDomDocument>
#include <QStringList>

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , opengl_obliquePhotograpy(nullptr)
    , opengl_dimensionalInspection(nullptr)
{
    ui->setupUi(this);
    ui->tabWidget->tabBar()->hide();

    QSettings settings(GLOBAL_COMPANY,GLOBAL_NAME);
    QString modelDirectoryPath = settings.value(GLOBAL_MODELDIRECTORYPATH).toString();
    QString earthPath = QDir::currentPath() + '/' + modelDirectoryPath + "/main.earth";
    initList(earthPath);

    if(initTab0()) ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    if(3 == ui->tabWidget->count()) ui->tabWidget->removeTab(2);
    if(2 == ui->tabWidget->count()) ui->tabWidget->removeTab(1);
    if(1 == ui->tabWidget->count()) ui->tabWidget->removeTab(0);

    if(3 == ui->tabWidget->count()) DestoryThreeWidget(opengl_dimensionalInspection);
    if(2 == ui->tabWidget->count()) DestoryThreeWidget(opengl_obliquePhotograpy);
    if(1 == ui->tabWidget->count()) DestoryThreeWidget(opengl_earth);
    delete ui;
}

void MainWindow::initList(QString earthPath) {
    QFile target(earthPath);
    target.open(QFile::ReadOnly);
    QDomDocument doc;
    doc.setContent(target.readAll());
    target.close();

    QDomElement map = doc.documentElement();
    QByteArray json = "[]";

    for(int i=0;i< map.childNodes().size();i++) {
       auto nodes = map.childNodes();
       auto node = nodes.at(i);

       if("json" == node.nodeName()) {
           json = node.childNodes().at(0).toText().nodeValue().toLocal8Bit();
           break;
       }
    }

    Json::Value value;
    Json::Reader reader;

    if(!reader.parse(json.data(),value)) {
        cerr << "main.earth:<json>解析失败!" << endl;
        return;
    }

    for(int i=0;i < value.size();i++) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromLocal8Bit(value[i]["name"].asCString()));

        QStringList tiles;
        for(auto tile : value[i]["obliquePhotograpy"])
            tiles.push_back(QString::fromLocal8Bit(tile.asCString()));
        item->setData(Qt::UserRole + 0,tiles);
        item->setData(Qt::UserRole + 1,value[i]["threeDimensionalInspection"].asCString());
        item->setData(Qt::UserRole + 2,value[i]["long"].asDouble());
        item->setData(Qt::UserRole + 3,value[i]["lat"].asDouble());
        item->setData(Qt::UserRole + 4,value[i]["pitch"].asDouble());
        item->setData(Qt::UserRole + 5,value[i]["range"].asDouble());
        ui->listWidget_names->addItem(item);
    }

    ui->listWidget_names->setCurrentRow(0);
}

bool MainWindow::initTab0() {
    opengl_earth = CreateThreeEarthWidget();
    if(opengl_earth == nullptr) return false;
    bp_earth = Basic::CreateThreePlugin(opengl_earth);
    cp_earth = Controls::CreateThreePlugin(opengl_earth);
    Controls::SetMouseWheelEventHandler(cp_earth,[this](Controls::ScrollingMotion sm,double distance) {
        if(distance < 1000.0) {
            if(1 == ui->tabWidget->count()) initTab1();
            if(2 == ui->tabWidget->count()) ui->tabWidget->setCurrentIndex(1);
            Basic::Home(bp_earth);
        }
    });

    ui->tabWidget->addTab(reinterpret_cast<QWidget*>(opengl_earth),"0");
    return true;
}

bool MainWindow::initTab1() {
    if(opengl_obliquePhotograpy == nullptr) {
        opengl_obliquePhotograpy = CreateThreeWidget();
        if(opengl_obliquePhotograpy == nullptr) return false;
        bp_obliquePhotograpy = Basic::CreateThreePlugin(opengl_obliquePhotograpy);
        cp_obliquePhotograpy = Controls::CreateThreePlugin(opengl_obliquePhotograpy);
        Controls::SetMouseWheelEventHandler(cp_obliquePhotograpy,[this](Controls::ScrollingMotion,double distance) {
            float c[3],r;
            Basic::BoundBox(bp_obliquePhotograpy,c,r);
            if(distance > r * 6) {
                ui->tabWidget->setCurrentIndex(0);
                Basic::Home(bp_obliquePhotograpy);
            } else if(distance < r / 6) {
                if(2 == ui->tabWidget->count()) initTab2();
                if(3 == ui->tabWidget->count()) ui->tabWidget->setCurrentIndex(2);
                Basic::Home(bp_obliquePhotograpy);
            }
        });
    }

    auto item = ui->listWidget_names->currentItem();
    if(item == nullptr) return false;
    QList<QVariant> tiles = item->data(Qt::UserRole + 0).toList();
    if(0 == tiles.size()) return false;
    Basic::AxisRotate(bp_obliquePhotograpy,1,0,0,-90);
    for(auto tile : tiles)
        Basic::AddScene(bp_obliquePhotograpy,tile.toString().toLocal8Bit().data());
    ui->tabWidget->addTab(reinterpret_cast<QWidget*>(opengl_obliquePhotograpy),"1");
    return true;
}

bool MainWindow::initTab2() {
    if(opengl_dimensionalInspection == nullptr) {
        opengl_dimensionalInspection = CreateThreeWidget();
        if(opengl_dimensionalInspection == nullptr) return false;
        bp_dimensionalInspection = Basic::CreateThreePlugin(opengl_dimensionalInspection);
        cp_dimensionalInspection = Controls::CreateThreePlugin(opengl_dimensionalInspection);
        //bp_dimensionalInspection = Basic::CreateThreePlugin(opengl_dimensionalInspection);
        //Shadow::Lighting(sp_dimensionalInspection,true);
        Controls::SetMouseWheelEventHandler(cp_dimensionalInspection,[this](Controls::ScrollingMotion sm,double distance) {
            float c[3],r;
            Basic::BoundBox(bp_dimensionalInspection,c,r);
            if(distance > r * 6) {
                ui->tabWidget->setCurrentIndex(1);
                Basic::Home(bp_dimensionalInspection);
            }
        });
    }

    auto item = ui->listWidget_names->currentItem();
    if(item == nullptr) return false;
    QByteArray threeDimensionalInspection = item->data(Qt::UserRole + 1).toByteArray();
    if(threeDimensionalInspection.isEmpty()) return false;
    Basic::OpenScene(bp_dimensionalInspection,threeDimensionalInspection.data());

    ui->tabWidget->addTab(reinterpret_cast<QWidget*>(opengl_dimensionalInspection),"2");
    return true;
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    //if(1 == ui->tabWidget->count()) Basic::SetHandleFrame(bp_earth,true);
    if(2 == ui->tabWidget->count()) Basic::SetHandleFrame(bp_obliquePhotograpy,true);
    if(3 == ui->tabWidget->count()) Basic::SetHandleFrame(bp_dimensionalInspection,true);
    switch(index) {
    case 0:
    //    Basic::SetHandleFrame(bp_earth,false);
        break;
    case 1:
        Basic::SetHandleFrame(bp_obliquePhotograpy,false);
        break;
    case 2:
        Basic::SetHandleFrame(bp_dimensionalInspection,false);
        break;
    }
}

void MainWindow::on_listWidget_names_itemClicked(QListWidgetItem *item)
{
    if(3 == ui->tabWidget->count()) { ui->tabWidget->removeTab(2); Basic::CloseScene(bp_dimensionalInspection); }
    if(2 == ui->tabWidget->count()) { ui->tabWidget->removeTab(1); Basic::CloseScene(bp_obliquePhotograpy); }

    QByteArray obliquePhotograpy = item->data(Qt::UserRole + 0).toByteArray();
    QByteArray threeDimensionalInspection = item->data(Qt::UserRole + 1).toByteArray();
    double longitude = item->data(Qt::UserRole + 2).toDouble();
    double latitude = item->data(Qt::UserRole + 3).toDouble();
    double pitch = item->data(Qt::UserRole + 4).toDouble();
    double range = item->data(Qt::UserRole + 5).toDouble();
    Basic::SetHomePosition(bp_earth, longitude, latitude, pitch, range);
    Basic::LookingFor(bp_earth, longitude, latitude, pitch, range, 2.0);
}
