/********************************************************************************
** Form generated from reading UI file 'add_plant.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_PLANT_H
#define UI_ADD_PLANT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_add_plant
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *name;
    QLineEdit *xcoord;
    QLineEdit *ycoord;

    void setupUi(QDialog *add_plant)
    {
        if (add_plant->objectName().isEmpty())
            add_plant->setObjectName(QString::fromUtf8("add_plant"));
        add_plant->resize(400, 300);
        buttonBox = new QDialogButtonBox(add_plant);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(add_plant);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 60, 58, 18));
        label_2 = new QLabel(add_plant);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 90, 58, 18));
        label_3 = new QLabel(add_plant);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 120, 58, 18));
        name = new QLineEdit(add_plant);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(180, 60, 113, 26));
        xcoord = new QLineEdit(add_plant);
        xcoord->setObjectName(QString::fromUtf8("xcoord"));
        xcoord->setGeometry(QRect(180, 90, 113, 26));
        ycoord = new QLineEdit(add_plant);
        ycoord->setObjectName(QString::fromUtf8("ycoord"));
        ycoord->setGeometry(QRect(180, 120, 113, 26));

        retranslateUi(add_plant);
        QObject::connect(buttonBox, SIGNAL(accepted()), add_plant, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), add_plant, SLOT(reject()));

        QMetaObject::connectSlotsByName(add_plant);
    } // setupUi

    void retranslateUi(QDialog *add_plant)
    {
        add_plant->setWindowTitle(QCoreApplication::translate("add_plant", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("add_plant", "name", nullptr));
        label_2->setText(QCoreApplication::translate("add_plant", "xcoord", nullptr));
        label_3->setText(QCoreApplication::translate("add_plant", "ycoord", nullptr));
    } // retranslateUi

};

namespace Ui {
    class add_plant: public Ui_add_plant {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_PLANT_H
