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
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_add_plant
{
public:
    QFormLayout *formLayout;
    QLabel *label_4;
    QLabel *label;
    QLineEdit *name;
    QLabel *label_2;
    QLineEdit *xcoord;
    QLabel *label_3;
    QLineEdit *ycoord;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *add_plant)
    {
        if (add_plant->objectName().isEmpty())
            add_plant->setObjectName(QString::fromUtf8("add_plant"));
        add_plant->resize(400, 246);
        formLayout = new QFormLayout(add_plant);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_4 = new QLabel(add_plant);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, label_4);

        label = new QLabel(add_plant);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        name = new QLineEdit(add_plant);
        name->setObjectName(QString::fromUtf8("name"));

        formLayout->setWidget(1, QFormLayout::FieldRole, name);

        label_2 = new QLabel(add_plant);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        xcoord = new QLineEdit(add_plant);
        xcoord->setObjectName(QString::fromUtf8("xcoord"));

        formLayout->setWidget(2, QFormLayout::FieldRole, xcoord);

        label_3 = new QLabel(add_plant);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_3);

        ycoord = new QLineEdit(add_plant);
        ycoord->setObjectName(QString::fromUtf8("ycoord"));

        formLayout->setWidget(3, QFormLayout::FieldRole, ycoord);

        buttonBox = new QDialogButtonBox(add_plant);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(add_plant);
        QObject::connect(buttonBox, SIGNAL(accepted()), add_plant, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), add_plant, SLOT(reject()));

        QMetaObject::connectSlotsByName(add_plant);
    } // setupUi

    void retranslateUi(QDialog *add_plant)
    {
        add_plant->setWindowTitle(QCoreApplication::translate("add_plant", "Add", nullptr));
        label_4->setText(QCoreApplication::translate("add_plant", "Add plant", nullptr));
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
