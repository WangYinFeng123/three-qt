#ifndef RELAVANCEDIALOG_H
#define RELAVANCEDIALOG_H
#include <QtXml/QDomDocument>
#include <QDialog>
#include <QDir>
#include <QListWidgetItem>
#include <QMultiMap>
#include <QProcess>
#include <QApplication>

namespace Ui {
class RelavanceDialog;
}

class RelavanceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RelavanceDialog(QWidget *parent = NULL);
    virtual ~RelavanceDialog();
    int exec();
    QDir workingDir;
    QString modelName;
    QString sceneConfigFilePath,sceneFileName;
    QMultiMap<QString,QString> animationNames;

Q_SIGNALS:
    void requestOid(QString oldOid,QString& newOid, QString& description);

private slots:
    void on_buttonBox_accepted();
    void on_tableWidget_cellChanged(int row, int column);
    void on_tableWidget_cellClicked(int row, int column);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);
private:
    Ui::RelavanceDialog *ui;
//    QProcess exe;
    QDomDocument doc;
};

#endif // RELAVANCEDIALOG_H
