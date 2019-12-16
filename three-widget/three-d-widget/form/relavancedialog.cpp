#include "relavancedialog.h"
#include "ui_relavancedialog.h"

#include <QTableWidgetItem>
#include <QTextStream>
#include <QEventLoop>
#include <QFile>

#include <iostream>
using namespace std;

RelavanceDialog::RelavanceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RelavanceDialog)
{
    ui->setupUi(this);
    setFocusPolicy(Qt::StrongFocus);
}

RelavanceDialog::~RelavanceDialog()
{
    delete ui;
}

int RelavanceDialog::exec() {
    ui->listWidget->clear();
    QStringList fileFilters;
    fileFilters.append("*.ncm");
    fileFilters.append("*.fbx");
    fileFilters.append("*.osgb");
    fileFilters.append("*.osg");
    fileFilters.append("*.nc");
    QStringList files = workingDir.entryList(fileFilters,QDir::Files);
    for(QStringList::Iterator i=files.begin();files.end()!=i;i++) {
        QString fileName = *i;
        QListWidgetItem* item = new QListWidgetItem(fileName);
        item->setData(Qt::UserRole,fileName);
        item->setData(Qt::UserRole+1,workingDir.path() + '/' + fileName);
        ui->listWidget->addItem(item);
        if(fileName == modelName) {
            item->setSelected(true);
            on_listWidget_itemDoubleClicked(item);
        }
    }

    return QDialog::exec();
}

void RelavanceDialog::on_buttonBox_accepted()
{
    if(sceneConfigFilePath.isEmpty()) reject();
    QFile target(sceneConfigFilePath);
    target.open(QFile::WriteOnly);
    QTextStream out(&target);
    doc.save(out,2);
    target.close();

    QDomElement root = doc.documentElement();
    if(0 == root.childNodes().size()) return;
    QDomNode nodes = root.childNodes().at(0);
    int count = nodes.childNodes().size();

    animationNames.clear();
    for(int i=0;i < count;i++) {
        QDomNode node = nodes.childNodes().at(i);
        animationNames.insertMulti(node.attributes().namedItem("oid").nodeValue(),node.attributes().namedItem("name").nodeValue());
    }

    accept();
}

void RelavanceDialog::on_tableWidget_cellChanged(int row, int column)
{
    if(0 == column) return;
    QDomElement root = doc.documentElement();
    if(0 == root.childNodes().size()) return;
    QDomNode nodes = root.childNodes().at(0);
    int count = nodes.childNodes().size();
    QString name = ui->tableWidget->item(row,0)->text();
    QString oid = ui->tableWidget->item(row,1)->text();
    QString oidDesc = column == 2 ? ui->tableWidget->item(row,2)->text() : "";

    for(int i=0;i < count;i++) {
        QDomNode node = nodes.childNodes().at(i);
        if(name != node.attributes().namedItem("name").nodeValue()) continue;
        node.attributes().namedItem("oid").setNodeValue(oid);
        if(!oidDesc.isEmpty()) node.attributes().namedItem("oid_desc").setNodeValue(oidDesc);
        break;
    }
}

void RelavanceDialog::on_tableWidget_cellClicked(int row, int column)
{
    QString name = ui->tableWidget->item(row,0)->text();
    ui->openGLWidget->lookingFor(name);

    if(0 != column) return;
    QTableWidgetItem* item = ui->tableWidget->item(row,1);
    QTableWidgetItem* item2 = ui->tableWidget->item(row,2);
    QString oid = item->text();
    QString newOid;
    QString description;
    emit requestOid(oid,newOid,description);
    item->setText(newOid);
    item2->setText(description);
    on_tableWidget_cellChanged(row,1);
}

void RelavanceDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *current)
{
    sceneFileName = current->data(Qt::UserRole).toString();
    QString sceneFilePath = current->data(Qt::UserRole+1).toString();
    sceneConfigFilePath = sceneFilePath + ".xml";

    QDir configDir = workingDir;
    configDir.cdUp();
    configDir.cd("config");
    QString newSceneConfigFilePath = configDir.path() +'/'+ sceneFileName + ".xml";

    if(!QFile::exists(newSceneConfigFilePath)) {
        QStringList args(sceneFilePath);
        QProcess::execute(QApplication::instance()->applicationDirPath() + "/export-interaction-config",args);
        QFile::copy(sceneConfigFilePath,newSceneConfigFilePath);
        QFile::remove(sceneConfigFilePath);
    }

    sceneConfigFilePath = newSceneConfigFilePath;

    QFile target(sceneConfigFilePath);
    target.open(QFile::ReadOnly);
    doc.setContent(target.readAll());
    target.close();
    QDomElement root = doc.documentElement();
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    if(0 < root.childNodes().size()) {
        QDomNode nodes = root.childNodes().at(0);
        int count = nodes.childNodes().size();
        ui->tableWidget->setRowCount(count);
        for(int i=0;i < count;i++) {
            QDomNode node = nodes.childNodes().at(i);
            QTableWidgetItem* x = new QTableWidgetItem(node.attributes().namedItem("name").nodeValue());
            x->setFlags(Qt::ItemIsSelectable);
            ui->tableWidget->setItem(i,0,x);
            ui->tableWidget->setItem(i,1,new QTableWidgetItem(node.attributes().namedItem("oid").nodeValue()));
            ui->tableWidget->setItem(i,2,new QTableWidgetItem(node.attributes().namedItem("oid_desc").nodeValue()));
        }
    }

    QApplication::processEvents();
    ui->openGLWidget->openScene(sceneFilePath);
}

