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
    ui->verticalLayout->insertWidget(0,reinterpret_cast<QWidget*>(tw));
    ui->verticalLayout->removeWidget(ui->widget);

    bp = Basic::CreateThreePlugin(tw);
    ap = Animations::CreateThreePlugin(tw);
    sp = Shadow::CreateThreePlugin(tw);
    cp = Controls::CreateThreePlugin(tw);
    op = Observer::CreateThreePlugin(tw);
    Basic::AxisRotate(bp,1,0,0,90);
}

MainWindow::~MainWindow()
{
    Basic::DestoryThreePlugin(bp);
    Animations::DestoryThreePlugin(ap);
    Shadow::DestoryThreePlugin(sp);
    Controls::DestoryThreePlugin(cp);
    Observer::DestoryThreePlugin(op);
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Observer::LookingFor(op,ui->comboBox->currentText().toUtf8().data());
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
    Basic::OpenScene(bp,url.toLocal8Bit().data());
    ui->comboBox->clear();
    set<string> ns = Basic::Models(bp);
    for(set<string>::iterator it = ns.begin();it != ns.end();it++) {
        ui->comboBox->addItem(QString::fromUtf8(it->data()));
    }
}

void MainWindow::on_pushButton_7_clicked()
{
    Animations::SetModelState(ap,ui->comboBox->currentText().toUtf8().data(),ui->doubleSpinBox_value->value());
}

void MainWindow::on_pushButton_8_clicked()
{
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(false);
    QString url = QFileDialog::getOpenFileName(this,QString::fromLocal8Bit("选择一个圖片文件"));
    reinterpret_cast<QWidget*>(tw)->setUpdatesEnabled(true);
    ui->lineEdit->setText(url);
    Basic::SetBackground(bp,url.toLocal8Bit().data());
}

void MainWindow::on_pushButton_setColor_clicked()
{
    Basic::SetBackground(bp,ui->doubleSpinBox_r->value(),ui->doubleSpinBox_g->value(),ui->doubleSpinBox_b->value(),1);
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) {
        timer.stop();
        disconnect(&timer,SIGNAL(timeout()),this,SLOT(paintGL()));
        Basic::SetHandleFrame(bp,false);
    } else {
        Basic::SetHandleFrame(bp,true);
        timer.setInterval(1000 / ui->spinBox_frameRate->value());
        timer.start();
        connect(&timer,SIGNAL(timeout()),this,SLOT(paintGL()));
    }
}

void MainWindow::paintGL() {
    Basic::RunFrame(bp);
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) Animations::TestAnimations(ap,false);
    else Animations::TestAnimations(ap,true);
}

void MainWindow::on_pushButton_clicked()
{
    if(op!=NULL) return;
    float e[3],c[3],u[3];
    Observer::HomePosition(op,e,c,u);
    cout << "eye:" << e[0] << "," << e[1] << "," << e[2] << endl;
    cout << "center:" << c[0] << "," << c[1] << "," << c[2] << endl;
    cout << "up:" << u[0] << "," << u[1] << "," << u[2] << endl;
    float r;

    Basic::BoundBox(bp,c,r);
    cout << "radius:" << r << endl;
    float s[3] = {r * 4,r * 4,r * 4};
    Observer::SetCameraPosition(op,s,c,u);
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) Basic::HeightLight(bp,ui->comboBox->currentText().toUtf8().data(),false);
    else Basic::HeightLight(bp,ui->comboBox->currentText().toUtf8().data(),true);
}

void MainWindow::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) Controls::SetMouseButton(cp,Controls::LEFT_MOUSE_BUTTON,Controls::MIDDLE_MOUSE_BUTTON,Controls::RIGHT_MOUSE_BUTTON);
    else Controls::SetMouseButton(cp,Controls::MIDDLE_MOUSE_BUTTON,Controls::LEFT_MOUSE_BUTTON,Controls::RIGHT_MOUSE_BUTTON);
}

void MainWindow::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) Basic::Bubbles(bp,false);
    else Basic::Bubbles(bp,true);
}

void MainWindow::on_checkBox_7_stateChanged(int arg1)
{
#if defined(QT5)
    if(arg1 == Qt::Unchecked) {
        reinterpret_cast<QWidget*>(tw)->setMouseTracking(false);
        function<bool(string,float[3])> f;
        Controls::SetMouseOverEventHandler(cp,f);
    } else {
        reinterpret_cast<QWidget*>(tw)->setMouseTracking(true);
        Controls::SetMouseOverEventHandler(cp,[this](string name,float xyz[3])->bool {
            ui->comboBox->setCurrentIndex(ui->comboBox->findText(QString::fromLocal8Bit(name.data())));
            cout << name << endl;
            return false;
        });
    }
#else
    if(arg1 == Qt::Unchecked) {
        reinterpret_cast<QWidget*>(tw)->setMouseTracking(false);
        Controls::SetMouseOverEventHandler(cp,NULL);
    } else {
        struct moeh : public Controls::MouseOverEventHandler {
            MainWindow* mw;
            moeh(MainWindow* mw) : mw(mw) {}
            bool operator()(string name,float xyz[3]) {
                ui->comboBox->setCurrentIndex(ui->comboBox->findText(QString::fromLocal8Bit(name.data())));
                cout << "over:" << name << endl;
                return false;
            }
        };

        reinterpret_cast<QWidget*>(tw)->setMouseTracking(true);
        Controls::SetMouseOverEventHandler(cp,new moeh(this));
    }
#endif
}

void MainWindow::on_checkBox_6_stateChanged(int arg1)
{
    if(arg1 == Qt::Unchecked) Shadow::Lighting(sp,false);
    else Shadow::Lighting(sp,true);
}

void MainWindow::on_pushButton_trunAxis_clicked()
{
    Basic::AxisRotate(bp,ui->doubleSpinBox_x->value(),ui->doubleSpinBox_y->value(),ui->doubleSpinBox_z->value(),ui->doubleSpinBox_degress->value());
}

void MainWindow::on_checkBox_teleport_stateChanged(int arg1)
{
#if defined(QT5)
    if(arg1 == Qt::Unchecked) {
        Observer::SwitchFirstPerson(op,false);
    } else {
        Observer::SwitchFirstPerson(op,true);
    }
#else
    if(arg1 == Qt::Unchecked) {
        Controls::SetMouseClickEventHandler(cp,NULL);
    } else {
        struct mceh : public Controls::MouseClickEventHandler {
            MainWindow* mw;
            mceh(MainWindow* mw) : mw(mw){}
            bool operator()(Controls::MouseButtonMask mb,string name,float xyz[3]) {
                if(mb==Controls::LEFT_MOUSE_BUTTON) {
                    cout << "left:" << mb << endl;
                    Basic::LookingFor(mw->bp,xyz,0);
                    return true;
                }
                return false;
            }
        };

        Controls::SetMouseClickEventHandler(cp,new mceh(this));
    }
#endif
}
