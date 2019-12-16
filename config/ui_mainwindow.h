/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Dec 10 14:58:07 2019
**      by: Qt User Interface Compiler version 4.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_machineCode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_filePath;
    QPushButton *pushButton_choose;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_modelDirectoryPath;
    QPushButton *pushButton_choosePluginDirectory;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_fontFilePath;
    QPushButton *pushButton_chooseFont;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(449, 237);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        lineEdit_machineCode = new QLineEdit(centralWidget);
        lineEdit_machineCode->setObjectName(QString::fromUtf8("lineEdit_machineCode"));

        horizontalLayout->addWidget(lineEdit_machineCode);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_filePath = new QLineEdit(centralWidget);
        lineEdit_filePath->setObjectName(QString::fromUtf8("lineEdit_filePath"));

        horizontalLayout_2->addWidget(lineEdit_filePath);

        pushButton_choose = new QPushButton(centralWidget);
        pushButton_choose->setObjectName(QString::fromUtf8("pushButton_choose"));

        horizontalLayout_2->addWidget(pushButton_choose);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_modelDirectoryPath = new QLineEdit(centralWidget);
        lineEdit_modelDirectoryPath->setObjectName(QString::fromUtf8("lineEdit_modelDirectoryPath"));

        horizontalLayout_5->addWidget(lineEdit_modelDirectoryPath);

        pushButton_choosePluginDirectory = new QPushButton(centralWidget);
        pushButton_choosePluginDirectory->setObjectName(QString::fromUtf8("pushButton_choosePluginDirectory"));

        horizontalLayout_5->addWidget(pushButton_choosePluginDirectory);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_fontFilePath = new QLineEdit(centralWidget);
        lineEdit_fontFilePath->setObjectName(QString::fromUtf8("lineEdit_fontFilePath"));

        horizontalLayout_3->addWidget(lineEdit_fontFilePath);

        pushButton_chooseFont = new QPushButton(centralWidget);
        pushButton_chooseFont->setObjectName(QString::fromUtf8("pushButton_chooseFont"));

        horizontalLayout_3->addWidget(pushButton_chooseFont);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_4->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_4);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\216\210\346\235\203", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "\346\234\272\345\231\250\346\240\207\350\257\206", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "\346\216\210\346\235\203\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        lineEdit_filePath->setText(QString());
        pushButton_choose->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "\346\250\241\345\236\213\347\233\256\345\275\225", 0, QApplication::UnicodeUTF8));
        lineEdit_modelDirectoryPath->setText(QApplication::translate("MainWindow", "./CSNC/3DModels", 0, QApplication::UnicodeUTF8));
        pushButton_choosePluginDirectory->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "\346\260\224\346\263\241\345\255\227\344\275\223", 0, QApplication::UnicodeUTF8));
        lineEdit_fontFilePath->setText(QApplication::translate("MainWindow", "./CSNC/fonts/msyhbd.ttc", 0, QApplication::UnicodeUTF8));
        pushButton_chooseFont->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
