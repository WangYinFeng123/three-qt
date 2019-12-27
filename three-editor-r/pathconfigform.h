#ifndef PATHCONFIGFORM_H
#define PATHCONFIGFORM_H

#include <QDialog>
#include <list>

using namespace std;

namespace Ui {
class PathConfigForm;
}

class PathConfigForm : public QDialog
{
    Q_OBJECT

public:
    explicit PathConfigForm(QWidget *parent = nullptr);
    ~PathConfigForm();

    list<tuple<string,double,double,double>> points;
    list<tuple<string,vector<double>,vector<double>>> lines;
    double pointRatio,lineRatio;
    int pointZ,lineZ;
    bool locked;

private slots:
    void on_pushButton_selectFile_clicked();
    void on_pushButton_ok_clicked();

private:
    Ui::PathConfigForm *ui;
};

#endif // PATHCONFIGFORM_H
