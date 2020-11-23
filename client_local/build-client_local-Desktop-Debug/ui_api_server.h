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
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_api_server
{
public:
    QDialogButtonBox *buttonBox;
    QLineEdit *ip;
    QLineEdit *port;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QDialog *api_server)
    {
        if (api_server->objectName().isEmpty())
            api_server->setObjectName(QString::fromUtf8("api_server"));
        api_server->resize(399, 207);
        buttonBox = new QDialogButtonBox(api_server);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 170, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ip = new QLineEdit(api_server);
        ip->setObjectName(QString::fromUtf8("ip"));
        ip->setGeometry(QRect(130, 80, 113, 26));
        port = new QLineEdit(api_server);
        port->setObjectName(QString::fromUtf8("port"));
        port->setGeometry(QRect(130, 120, 113, 26));
        label = new QLabel(api_server);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(50, 80, 58, 18));
        label_2 = new QLabel(api_server);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(50, 120, 58, 18));
        label_3 = new QLabel(api_server);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 30, 151, 16));

        retranslateUi(api_server);
        QObject::connect(buttonBox, SIGNAL(accepted()), api_server, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), api_server, SLOT(reject()));

        QMetaObject::connectSlotsByName(api_server);
    } // setupUi

    void retranslateUi(QDialog *api_server)
    {
        api_server->setWindowTitle(QCoreApplication::translate("api_server", "Dialog", nullptr));
        ip->setText(QCoreApplication::translate("api_server", "192.168.2.152", nullptr));
        port->setText(QCoreApplication::translate("api_server", "6969", nullptr));
        label->setText(QCoreApplication::translate("api_server", "Host", nullptr));
        label_2->setText(QCoreApplication::translate("api_server", "Port", nullptr));
        label_3->setText(QCoreApplication::translate("api_server", "Connection Details", nullptr));
    } // retranslateUi

};

namespace Ui {
    class api_server: public Ui_api_server {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_API_SERVER_H
