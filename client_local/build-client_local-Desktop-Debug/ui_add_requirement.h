/********************************************************************************
** Form generated from reading UI file 'add_requirement.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_REQUIREMENT_H
#define UI_ADD_REQUIREMENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_add_requirement
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLineEdit *plant_id;
    QLineEdit *sensor_id;
    QLineEdit *max_value;
    QLineEdit *min_value;
    QLabel *label_5;

    void setupUi(QDialog *add_requirement)
    {
        if (add_requirement->objectName().isEmpty())
            add_requirement->setObjectName(QString::fromUtf8("add_requirement"));
        add_requirement->resize(400, 312);
        buttonBox = new QDialogButtonBox(add_requirement);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(add_requirement);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 58, 18));
        label_2 = new QLabel(add_requirement);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 90, 58, 18));
        label_3 = new QLabel(add_requirement);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 120, 71, 16));
        label_4 = new QLabel(add_requirement);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 150, 71, 16));
        plant_id = new QLineEdit(add_requirement);
        plant_id->setObjectName(QString::fromUtf8("plant_id"));
        plant_id->setGeometry(QRect(120, 60, 113, 26));
        sensor_id = new QLineEdit(add_requirement);
        sensor_id->setObjectName(QString::fromUtf8("sensor_id"));
        sensor_id->setGeometry(QRect(120, 90, 113, 26));
        max_value = new QLineEdit(add_requirement);
        max_value->setObjectName(QString::fromUtf8("max_value"));
        max_value->setGeometry(QRect(120, 120, 113, 26));
        min_value = new QLineEdit(add_requirement);
        min_value->setObjectName(QString::fromUtf8("min_value"));
        min_value->setGeometry(QRect(120, 150, 113, 26));
        label_5 = new QLabel(add_requirement);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(160, 20, 131, 16));

        retranslateUi(add_requirement);
        QObject::connect(buttonBox, SIGNAL(accepted()), add_requirement, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), add_requirement, SLOT(reject()));

        QMetaObject::connectSlotsByName(add_requirement);
    } // setupUi

    void retranslateUi(QDialog *add_requirement)
    {
        add_requirement->setWindowTitle(QCoreApplication::translate("add_requirement", "Add", nullptr));
        label->setText(QCoreApplication::translate("add_requirement", "plant_id", nullptr));
        label_2->setText(QCoreApplication::translate("add_requirement", "sensor_id", nullptr));
        label_3->setText(QCoreApplication::translate("add_requirement", "max_value", nullptr));
        label_4->setText(QCoreApplication::translate("add_requirement", "min_value", nullptr));
        label_5->setText(QCoreApplication::translate("add_requirement", "Add requirement", nullptr));
    } // retranslateUi

};

namespace Ui {
    class add_requirement: public Ui_add_requirement {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_REQUIREMENT_H
