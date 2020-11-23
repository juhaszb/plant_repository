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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlantApp
{
public:
    QAction *actionAdd_Plant;
    QAction *actionActor;
    QAction *actionRequirement;
    QWidget *centralwidget;
    QTableWidget *sensor_data;
    QTableWidget *plant_data;
    QLabel *label;
    QLabel *label_2;
    QTableWidget *requirements_data;
    QLabel *label_3;
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
        actionActor = new QAction(PlantApp);
        actionActor->setObjectName(QString::fromUtf8("actionActor"));
        actionRequirement = new QAction(PlantApp);
        actionRequirement->setObjectName(QString::fromUtf8("actionRequirement"));
        centralwidget = new QWidget(PlantApp);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sensor_data = new QTableWidget(centralwidget);
        sensor_data->setObjectName(QString::fromUtf8("sensor_data"));
        sensor_data->setGeometry(QRect(470, 60, 311, 271));
        plant_data = new QTableWidget(centralwidget);
        plant_data->setObjectName(QString::fromUtf8("plant_data"));
        plant_data->setGeometry(QRect(50, 60, 411, 271));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 20, 71, 21));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(520, 20, 71, 16));
        requirements_data = new QTableWidget(centralwidget);
        requirements_data->setObjectName(QString::fromUtf8("requirements_data"));
        requirements_data->setGeometry(QRect(60, 390, 721, 111));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(370, 360, 91, 21));
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
        menuPlant_Reposity->addAction(actionRequirement);

        retranslateUi(PlantApp);

        QMetaObject::connectSlotsByName(PlantApp);
    } // setupUi

    void retranslateUi(QMainWindow *PlantApp)
    {
        PlantApp->setWindowTitle(QCoreApplication::translate("PlantApp", "PlantApp", nullptr));
        actionAdd_Plant->setText(QCoreApplication::translate("PlantApp", "Plant", nullptr));
#if QT_CONFIG(shortcut)
        actionAdd_Plant->setShortcut(QCoreApplication::translate("PlantApp", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionActor->setText(QCoreApplication::translate("PlantApp", "Actor", nullptr));
        actionRequirement->setText(QCoreApplication::translate("PlantApp", "Requirement", nullptr));
        label->setText(QCoreApplication::translate("PlantApp", "Plants", nullptr));
        label_2->setText(QCoreApplication::translate("PlantApp", "Sensors", nullptr));
        label_3->setText(QCoreApplication::translate("PlantApp", "Requirements", nullptr));
        menuPlant_Reposity->setTitle(QCoreApplication::translate("PlantApp", "Add", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlantApp: public Ui_PlantApp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANTAPP_H
