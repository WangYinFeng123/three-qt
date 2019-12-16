/********************************************************************************
** Form generated from reading UI file 'relavancedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RELAVANCEDIALOG_H
#define UI_RELAVANCEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include "threedwidget.h"

QT_BEGIN_NAMESPACE

class Ui_RelavanceDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout_2;
    ThreeDWidget *openGLWidget;
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *RelavanceDialog)
    {
        if (RelavanceDialog->objectName().isEmpty())
            RelavanceDialog->setObjectName(QString::fromUtf8("RelavanceDialog"));
        RelavanceDialog->resize(1011, 714);
        verticalLayout = new QVBoxLayout(RelavanceDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(RelavanceDialog);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMinimumSize(QSize(200, 0));

        horizontalLayout->addWidget(listWidget);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        openGLWidget = new ThreeDWidget(RelavanceDialog);
        openGLWidget->setObjectName(QString::fromUtf8("openGLWidget"));
        openGLWidget->setFocusPolicy(Qt::StrongFocus);

        verticalLayout_2->addWidget(openGLWidget);

        tableWidget = new QTableWidget(RelavanceDialog);
        if (tableWidget->columnCount() < 3)
            tableWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

        verticalLayout_2->addWidget(tableWidget);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(RelavanceDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(RelavanceDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), RelavanceDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RelavanceDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RelavanceDialog);
    } // setupUi

    void retranslateUi(QDialog *RelavanceDialog)
    {
        RelavanceDialog->setWindowTitle(QApplication::translate("RelavanceDialog", "\345\205\263\350\201\224\351\205\215\347\275\256", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("RelavanceDialog", "\345\212\250\347\224\273\345\220\215", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("RelavanceDialog", "OID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("RelavanceDialog", "\346\217\217\350\277\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RelavanceDialog: public Ui_RelavanceDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RELAVANCEDIALOG_H
