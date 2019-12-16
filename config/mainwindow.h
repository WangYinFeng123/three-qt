#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QSettings& settings,QWidget *parent = NULL);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_choose_clicked();
    void on_pushButton_chooseFont_clicked();
    void on_pushButton_choosePluginDirectory_clicked();
private:
    Ui::MainWindow *ui;
    QSettings& settings;
};

#endif // MAINWINDOW_H
