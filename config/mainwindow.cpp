#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork/QNetworkInterface>
#include <QFile>
#include <QFileDialog>
#include <QCryptographicHash>
#include <iostream>


QString getHostmacAddress() {
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();

    for(int i=0;i < nets.count();i++) {
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) &&
        nets[i].flags().testFlag(QNetworkInterface::IsRunning) &&
        !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
            return nets[i].hardwareAddress();
    }

    return "";
}

MainWindow::MainWindow(QSettings& settings,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    settings(settings)
{
    ui->setupUi(this);
    QByteArray md5 = QCryptographicHash::hash(getHostmacAddress().toLocal8Bit(), QCryptographicHash::Md5);
    ui->lineEdit_machineCode->setText(md5.toHex());
    QString filePath = settings.value("authorizationFilePath").toString();
    ui->lineEdit_filePath->setText(filePath);
    QString fontFilePath = settings.value("fontFilePath").toString();
    if(!fontFilePath.isEmpty()) ui->lineEdit_fontFilePath->setText(fontFilePath);
    QString modelDirectoryPath = settings.value("modelDirectoryPath").toString();
    if(!modelDirectoryPath.isEmpty()) ui->lineEdit_modelDirectoryPath->setText(modelDirectoryPath);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    settings.setValue("authorizationFilePath",ui->lineEdit_filePath->text());
    settings.setValue("fontFilePath",ui->lineEdit_fontFilePath->text());
    settings.setValue("modelDirectoryPath",ui->lineEdit_modelDirectoryPath->text());
    close();
}

void MainWindow::on_pushButton_choose_clicked()
{
    QString url = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择一个授权文件"),"./","authorizations (*.key)");
    if(url.isEmpty()) return;
    ui->lineEdit_filePath->setText(url);
}

void MainWindow::on_pushButton_chooseFont_clicked()
{
    QString url = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择一个授权文件"),"./","font (*.ttc *.ttf)");
    if(url.isEmpty()) return;
    ui->lineEdit_fontFilePath->setText(url);
}

void MainWindow::on_pushButton_choosePluginDirectory_clicked()
{
    QString url = QFileDialog::getExistingDirectory(this,QString::fromLocal8Bit("选择一个目录"),"./");
    if(url.isEmpty()) return;
    ui->lineEdit_modelDirectoryPath->setText(url);
}
