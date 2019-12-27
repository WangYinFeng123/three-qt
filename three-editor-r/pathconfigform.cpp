#include "pathconfigform.h"
#include "ui_pathconfigform.h"

#include <QFileDialog>

PathConfigForm::PathConfigForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PathConfigForm)
{
    ui->setupUi(this);
}

PathConfigForm::~PathConfigForm()
{
    delete ui;
}

void PathConfigForm::on_pushButton_selectFile_clicked()
{
    auto url = QFileDialog::getOpenFileName(this,"Path File");
    ui->pushButton_ok->setEnabled(!url.isEmpty());
    ui->lineEdit_path->setText(url);
}

void PathConfigForm::on_pushButton_ok_clicked()
{
    QFile file(ui->lineEdit_path->text());
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    while(!file.atEnd()) {
        QString row = file.readLine();
        auto columns = row.trimmed().split(QRegExp("[\\s]+"));
        if(columns.empty()) continue;
        while(columns.size() < 5) columns.append("0");

        auto size = ui->spinBox_size->value();
        auto beginNum = columns[ui->spinBox_type->value()];
        string type = beginNum == '0' ? "Point" : "Line";

        if(type == "Point") {
            auto path = make_tuple(
                type,
                columns[ui->spinBox_x->value()].toFloat() * size,
                -columns[ui->spinBox_y->value()].toFloat() * size,
                columns[ui->spinBox_z->value()].toFloat() * size
            );

            points.emplace_back(path);
            continue;
        }

        auto beginPos = vector<double> {
            columns[ui->spinBox_x->value()].toFloat() * size,
            -columns[ui->spinBox_y->value()].toFloat() * size,
            columns[ui->spinBox_z->value()].toFloat() * size
        };

        row = file.readLine();
        columns = row.trimmed().split(QRegExp("[\\s]+"));
        while(columns.size() < 5) columns.append("0");
        auto endNum = columns[ui->spinBox_type->value()];
        type = endNum == '0' ? "Point" : "Line";

        if(type == "Point") {
            auto path = make_tuple(
                type,
                columns[ui->spinBox_x->value()].toFloat() * size,
                -columns[ui->spinBox_y->value()].toFloat() * size,
                columns[ui->spinBox_z->value()].toFloat() * size
            );

            points.emplace_back(path);
            continue;
        }

        auto endPos = vector<double> {
            columns[ui->spinBox_x->value()].toFloat() * size,
            -columns[ui->spinBox_y->value()].toFloat() * size,
            columns[ui->spinBox_z->value()].toFloat() * size
        };

        lines.emplace_back(make_tuple("Line",beginPos,endPos));
    }

    file.close();

    pointRatio = ui->doubleSpinBox_pointRatio->value();
    pointZ = ui->spinBox_pointZ->value();

    accept();
}
