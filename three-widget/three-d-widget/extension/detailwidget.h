#ifndef DETAILSWIDGET_H
#define DETAILSWIDGET_H

#include <QWidget>

namespace Ui {
class DetailWidget;
}

class DetailWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DetailWidget(QWidget *parent = nullptr);
    ~DetailWidget();
    void setText(QString text);
    QString getText();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    Ui::DetailWidget *ui;
};

#endif // DETAILSWIDGET_H
