/********************************************************************************
** Form generated from reading UI file 'plantapp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANTAPP_H
#define UI_PLANTAPP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlantApp
{
public:
    QAction *actionAdd_Plant;
    QWidget *centralwidget;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QMenuBar *menubar;
    QMenu *menuPlant_Reposity;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *PlantApp)
    {
        if (PlantApp->objectName().isEmpty())
            PlantApp->setObjectName(QString::fromUtf8("PlantApp"));
        PlantApp->resize(800, 600);
        actionAdd_Plant = new QAction(PlantApp);
        actionAdd_Plant->setObjectName(QString::fromUtf8("actionAdd_Plant"));
        centralwidget = new QWidget(PlantApp);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(40, 10, 581, 251));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        PlantApp->setCentralWidget(centralwidget);
        menubar = new QMenuBar(PlantApp);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 23));
        menuPlant_Reposity = new QMenu(menubar);
        menuPlant_Reposity->setObjectName(QString::fromUtf8("menuPlant_Reposity"));
        PlantApp->setMenuBar(menubar);
        statusbar = new QStatusBar(PlantApp);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        PlantApp->setStatusBar(statusbar);

        menubar->addAction(menuPlant_Reposity->menuAction());
        menuPlant_Reposity->addAction(actionAdd_Plant);

        retranslateUi(PlantApp);

        QMetaObject::connectSlotsByName(PlantApp);
    } // setupUi

    void retranslateUi(QMainWindow *PlantApp)
    {
        PlantApp->setWindowTitle(QCoreApplication::translate("PlantApp", "PlantApp", nullptr));
        actionAdd_Plant->setText(QCoreApplication::translate("PlantApp", "Add Plant", nullptr));
        menuPlant_Reposity->setTitle(QCoreApplication::translate("PlantApp", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlantApp: public Ui_PlantApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANTAPP_H
