#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>

#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    tw = CreateThreeWidget();
    reinterpret_cast<QWidget*>(tw)->setFocusPolicy(Qt::ClickFocus);
    ui->verticalLayout->replaceWidget(ui->widget,reinterpret_cast<QWidget*>(tw));

    bp = new Basic(tw);
    ap = new Animations(tw);
    sp = new Shadow(tw);
    cp = new Controls(tw);
    op = new Observer(tw);
    bp->AxisRotate(1,0,0,90);
}

MainWindow::~MainWindow()
{
    delete bp;
    delete ap;
    delete sp;
    delete cp;
    delete op;
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    op->LookingFor(ui->comboBox->currentText().toUtf8().data());
}

void MainWindow::on_action_2_triggered()
{
    QMessageBox::about(this,QString::fromLocal8Bit("遇到问题呼叫"),QString::fromLocal8Bit("邮箱：sl.truman@live.com\n电话：17352892637\n微信：XFSkyL"));
}

void MainWindow::on_pushButton_6_clicked()
{
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
    QString url = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择一个场景文件"));
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
    ui->lineEdit_2->setText(url);
    bp->OpenScene(url.toLocal8Bit().data());
    ui->comboBox->clear();
    set<string> ns = bp->Models();
    for(set<string>::iterator it = ns.begin();it != ns.end();it++) {
        ui->comboBox->addItem(QString::fromUtf8(it->data()));
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    ap->SetModelState(ui->comboBox->currentText().toUtf8().data(),ui->doubleSpinBox_value->value());
}

void MainWindow::on_pushButton_8_clicked()
{
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
    QString url = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择一个圖片文件"));
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
    ui->lineEdit->setText(url);
    bp->SetBackground(url.toLocal8Bit().data());
}

void MainWindow::on_pushButton_setColor_clicked()
{
    bp->SetBackground(ui->doubleSpinBox_r->value(),ui->doubleSpinBox_g->value(),ui->doubleSpinBox_b->value(),1);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) {
        timer.stop();
        disconnect(&timer,SIGNAL(timeout()),this,SLOT(paintGL()));
        bp->SetHandleFrame(false);
    } else {
        bp->SetHandleFrame(true);
        timer.setInterval(1000 / ui->spinBox_frameRate->value());
        timer.start();
        connect(&timer,SIGNAL(timeout()),this,SLOT(paintGL()));
    }
}

void MainWindow::paintGL() {
    bp->RunFrame();
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) ap->TestAnimations(false);
    else ap->TestAnimations(true);
}

void MainWindow::on_pushButton_clicked()
{
    if(op!=NULL) return;
    float e[3],c[3],u[3];
    op->HomePosition(e,c,u);
    cout << "eye:" << e[0] << "," << e[1] << "," << e[2] << endl;
    cout << "center:" << c[0] << "," << c[1] << "," << c[2] << endl;
    cout << "up:" << u[0] << "," << u[1] << "," << u[2] << endl;
    float r;

    bp->BoundBox(c,r);
    cout << "radius:" << r << endl;
    float s[3] = {r * 4,r * 4,r * 4};
    op->SetCameraPosition(s,c,u);
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    float rgba[4] = {1.0,0.0,0.0,0.5};
    if(arg1 == Qt::Unchecked) bp->HeightLight(ui->comboBox->currentText().toUtf8().data(),false);
    else bp->HeightLight(ui->comboBox->currentText().toUtf8().data(),rgba);
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) cp->SetMouseButton(Controls::Left,Controls::Middle,Controls::Right);
    else cp->SetMouseButton(Controls::Middle,Controls::Left,Controls::Right);
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) bp->Bubbles(false);
    else bp->Bubbles(true);
}

void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) {
        reinterpret_cast<QWidget*>(tw)->setMouseTracking(false);
        function<bool(vec2)> f;
        cp->SetMouseOverEventHandler(f);
    } else {
        reinterpret_cast<QWidget*>(tw)->setMouseTracking(true);
        cp->SetMouseOverEventHandler([this](vec2 xy)->bool {
            auto kv = bp->Intersect(xy,0b1);
            if(kv.second.empty()) return false;
            ui->comboBox->setCurrentIndex(ui->comboBox->findText(QString::fromLocal8Bit(kv.second.data())));
            cout << kv.second << endl;
            return false;
        });
    }
}

void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) sp->Lighting(false);
    else sp->Lighting(true);
}

void MainWindow::on_pushButton_trunAxis_clicked()
{
    bp->AxisRotate(ui->doubleSpinBox_x->value(),ui->doubleSpinBox_y->value(),ui->doubleSpinBox_z->value(),ui->doubleSpinBox_degress->value());
}

void MainWindow::on_checkBox_teleport_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) {
        op->SwitchFirstPerson(false);
    } else {
        op->SwitchFirstPerson(true);
    }
}
