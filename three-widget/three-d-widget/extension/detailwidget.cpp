#include "detailwidget.h"
#include "ui_detailwidget.h"
#include <QPainter>
#include <QFocusEvent>

DetailWidget::DetailWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetailWidget)
{
    ui->setupUi(this);

    setAttribute(Qt::WA_TransparentForMouseEvents);
    setAttribute(Qt::WA_TranslucentBackground);

    setWindowFlags (Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
}

DetailWidget::~DetailWidget()
{
    delete ui;
}

void DetailWidget::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.setBrush(QColor(114, 159, 207, 100));
    painter.setPen(Qt::NoPen);
    painter.drawRoundRect(rect().x(),
                          rect().y(),
                          rect().width(),
                          rect().height());  //QColor最后一个参数80代表背景的透明度
}

void DetailWidget::setText(QString text) {
    setGeometry(0,0,800,20);
    ui->label->setText(text);
    adjustSize();
}

QString DetailWidget::getText() {
    return ui->label->text();
}
