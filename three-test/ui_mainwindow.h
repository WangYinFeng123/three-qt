/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_2;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_4;
    QDoubleSpinBox *doubleSpinBox_r;
    QDoubleSpinBox *doubleSpinBox_g;
    QDoubleSpinBox *doubleSpinBox_b;
    QPushButton *pushButton_setColor;
    QLineEdit *lineEdit;
    QPushButton *pushButton_8;
    QSpinBox *spinBox_frameRate;
    QCheckBox *checkBox;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_teleport;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_7;
    QComboBox *comboBox;
    QPushButton *pushButton_2;
    QCheckBox *checkBox_3;
    QDoubleSpinBox *doubleSpinBox_value;
    QPushButton *pushButton_7;
    QHBoxLayout *horizontalLayout_2;
    QDoubleSpinBox *doubleSpinBox_x;
    QDoubleSpinBox *doubleSpinBox_y;
    QDoubleSpinBox *doubleSpinBox_z;
    QDoubleSpinBox *doubleSpinBox_degress;
    QPushButton *pushButton_trunAxis;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(833, 533);
        MainWindow->setAutoFillBackground(false);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QString::fromUtf8("action_2"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setFocusPolicy(Qt::NoFocus);

        verticalLayout->addWidget(widget);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        doubleSpinBox_r = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_r->setObjectName(QString::fromUtf8("doubleSpinBox_r"));
        doubleSpinBox_r->setDecimals(1);
        doubleSpinBox_r->setMaximum(1.000000000000000);
        doubleSpinBox_r->setSingleStep(0.100000000000000);
        doubleSpinBox_r->setValue(1.000000000000000);

        horizontalLayout_4->addWidget(doubleSpinBox_r);

        doubleSpinBox_g = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_g->setObjectName(QString::fromUtf8("doubleSpinBox_g"));
        doubleSpinBox_g->setDecimals(1);
        doubleSpinBox_g->setMaximum(1.000000000000000);
        doubleSpinBox_g->setSingleStep(0.100000000000000);
        doubleSpinBox_g->setValue(1.000000000000000);

        horizontalLayout_4->addWidget(doubleSpinBox_g);

        doubleSpinBox_b = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_b->setObjectName(QString::fromUtf8("doubleSpinBox_b"));
        doubleSpinBox_b->setDecimals(1);
        doubleSpinBox_b->setMaximum(1.000000000000000);
        doubleSpinBox_b->setSingleStep(0.100000000000000);
        doubleSpinBox_b->setValue(1.000000000000000);

        horizontalLayout_4->addWidget(doubleSpinBox_b);

        pushButton_setColor = new QPushButton(centralWidget);
        pushButton_setColor->setObjectName(QString::fromUtf8("pushButton_setColor"));

        horizontalLayout_4->addWidget(pushButton_setColor);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_4->addWidget(lineEdit);

        pushButton_8 = new QPushButton(centralWidget);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));

        horizontalLayout_4->addWidget(pushButton_8);

        spinBox_frameRate = new QSpinBox(centralWidget);
        spinBox_frameRate->setObjectName(QString::fromUtf8("spinBox_frameRate"));
        spinBox_frameRate->setValue(24);

        horizontalLayout_4->addWidget(spinBox_frameRate);

        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout_4->addWidget(checkBox);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_3->addWidget(lineEdit_2);

        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(pushButton_6);

        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout_3->addWidget(pushButton);

        checkBox_4 = new QCheckBox(centralWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));

        horizontalLayout_3->addWidget(checkBox_4);

        checkBox_6 = new QCheckBox(centralWidget);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));

        horizontalLayout_3->addWidget(checkBox_6);

        checkBox_5 = new QCheckBox(centralWidget);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));

        horizontalLayout_3->addWidget(checkBox_5);

        checkBox_teleport = new QCheckBox(centralWidget);
        checkBox_teleport->setObjectName(QString::fromUtf8("checkBox_teleport"));

        horizontalLayout_3->addWidget(checkBox_teleport);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox_2 = new QCheckBox(centralWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

        horizontalLayout->addWidget(checkBox_2);

        checkBox_7 = new QCheckBox(centralWidget);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));

        horizontalLayout->addWidget(checkBox_7);

        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(comboBox);

        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        checkBox_3 = new QCheckBox(centralWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));

        horizontalLayout->addWidget(checkBox_3);

        doubleSpinBox_value = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_value->setObjectName(QString::fromUtf8("doubleSpinBox_value"));
        doubleSpinBox_value->setMinimum(0.000000000000000);
        doubleSpinBox_value->setMaximum(9999.000000000000000);

        horizontalLayout->addWidget(doubleSpinBox_value);

        pushButton_7 = new QPushButton(centralWidget);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));

        horizontalLayout->addWidget(pushButton_7);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        doubleSpinBox_x = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_x->setObjectName(QString::fromUtf8("doubleSpinBox_x"));
        doubleSpinBox_x->setDecimals(0);
        doubleSpinBox_x->setMaximum(1.000000000000000);
        doubleSpinBox_x->setValue(1.000000000000000);

        horizontalLayout_2->addWidget(doubleSpinBox_x);

        doubleSpinBox_y = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_y->setObjectName(QString::fromUtf8("doubleSpinBox_y"));
        doubleSpinBox_y->setDecimals(0);
        doubleSpinBox_y->setMaximum(1.000000000000000);

        horizontalLayout_2->addWidget(doubleSpinBox_y);

        doubleSpinBox_z = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_z->setObjectName(QString::fromUtf8("doubleSpinBox_z"));
        doubleSpinBox_z->setDecimals(0);
        doubleSpinBox_z->setMaximum(1.000000000000000);

        horizontalLayout_2->addWidget(doubleSpinBox_z);

        doubleSpinBox_degress = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_degress->setObjectName(QString::fromUtf8("doubleSpinBox_degress"));
        doubleSpinBox_degress->setDecimals(1);
        doubleSpinBox_degress->setMaximum(360.000000000000000);
        doubleSpinBox_degress->setValue(90.000000000000000);

        horizontalLayout_2->addWidget(doubleSpinBox_degress);

        pushButton_trunAxis = new QPushButton(centralWidget);
        pushButton_trunAxis->setObjectName(QString::fromUtf8("pushButton_trunAxis"));
        sizePolicy2.setHeightForWidth(pushButton_trunAxis->sizePolicy().hasHeightForWidth());
        pushButton_trunAxis->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(pushButton_trunAxis);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 833, 31));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action_2);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "\350\201\224\347\263\273\344\275\234\350\200\205", nullptr));
        pushButton_setColor->setText(QApplication::translate("MainWindow", "\350\203\214\346\231\257\350\211\262", nullptr));
        pushButton_8->setText(QApplication::translate("MainWindow", "\350\203\214\346\231\257\345\233\276", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "\351\231\220\345\210\266\345\270\247\347\216\207", nullptr));
        pushButton_6->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\345\234\272\346\231\257", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "\347\247\273\345\212\250\347\233\270\346\234\272", nullptr));
        checkBox_4->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\346\260\224\346\263\241", nullptr));
        checkBox_6->setText(QApplication::translate("MainWindow", "\345\274\200\345\220\257\345\205\211\345\275\261", nullptr));
        checkBox_5->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\351\224\256\344\275\215", nullptr));
        checkBox_teleport->setText(QApplication::translate("MainWindow", "\347\236\254\347\247\273\346\250\241\345\274\217", nullptr));
        checkBox_2->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225\345\212\250\347\224\273", nullptr));
        checkBox_7->setText(QApplication::translate("MainWindow", "\351\274\240\346\240\207\350\277\275\350\270\252", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "\345\256\232\344\275\215\346\250\241\345\236\213", nullptr));
        checkBox_3->setText(QApplication::translate("MainWindow", "\351\253\230\344\272\256\346\250\241\345\236\213", nullptr));
        pushButton_7->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225\345\205\263\350\201\224", nullptr));
        pushButton_trunAxis->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\350\275\264\345\220\221\357\274\210X,Y,Z,\345\272\246\357\274\211", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\345\270\256\345\212\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
