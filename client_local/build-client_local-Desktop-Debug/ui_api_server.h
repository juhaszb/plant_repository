/********************************************************************************
** Form generated from reading UI file 'api_server.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_API_SERVER_H
#define UI_API_SERVER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_api_server
{
public:
    QFormLayout *formLayout;
    QLabel *label_3;
    QLabel *label;
    QLineEdit *ip;
    QLabel *label_2;
    QLineEdit *port;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *api_server)
    {
        if (api_server->objectName().isEmpty())
            api_server->setObjectName(QString::fromUtf8("api_server"));
        api_server->resize(399, 207);
        formLayout = new QFormLayout(api_server);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label_3 = new QLabel(api_server);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(0, QFormLayout::FieldRole, label_3);

        label = new QLabel(api_server);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        ip = new QLineEdit(api_server);
        ip->setObjectName(QString::fromUtf8("ip"));

        formLayout->setWidget(1, QFormLayout::FieldRole, ip);

        label_2 = new QLabel(api_server);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        port = new QLineEdit(api_server);
        port->setObjectName(QString::fromUtf8("port"));

        formLayout->setWidget(2, QFormLayout::FieldRole, port);

        buttonBox = new QDialogButtonBox(api_server);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(3, QFormLayout::SpanningRole, buttonBox);


        retranslateUi(api_server);
        QObject::connect(buttonBox, SIGNAL(accepted()), api_server, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), api_server, SLOT(reject()));

        QMetaObject::connectSlotsByName(api_server);
    } // setupUi

    void retranslateUi(QDialog *api_server)
    {
        api_server->setWindowTitle(QCoreApplication::translate("api_server", "Connection Details", nullptr));
        label_3->setText(QCoreApplication::translate("api_server", "Connection Details", nullptr));
        label->setText(QCoreApplication::translate("api_server", "Host", nullptr));
        ip->setText(QCoreApplication::translate("api_server", "192.168.2.152", nullptr));
        label_2->setText(QCoreApplication::translate("api_server", "Port", nullptr));
        port->setText(QCoreApplication::translate("api_server", "7000", nullptr));
    } // retranslateUi

};

namespace Ui {
    class api_server: public Ui_api_server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_API_SERVER_H
