#ifndef PLANTAPP_H
#define PLANTAPP_H

#include <QMainWindow>
#include <string>
#include <pistache/client.h>
//#include <QtNetwork/qnetworkaccessmanager.h>

QT_BEGIN_NAMESPACE
namespace Ui { class PlantApp; }
QT_END_NAMESPACE

class PlantApp : public QMainWindow
{
    Q_OBJECT

public:
    PlantApp(std::string ip, int port, QWidget *parent = nullptr);
    ~PlantApp();



private slots:
    void on_actionAdd_Plant_triggered();

    void update_component();

  /*  void network_message(QNetworkReply* reply);

    void plant_message(QNetworkReply* reply);

    void general_message(QNetworkReply* reply);*/



    void on_actionRequirement_triggered();

private:
    Ui::PlantApp *ui;
    std::string port;
    std::string ip;
    Pistache::Http::Client client;
   // QNetworkAccessManager * manager;
   // QNetworkAccessManager * plant;
   // QNetworkAccessManager * general;

    void populate_plants(void);
    void populate_requirements(void);
};
#endif // PLANTAPP_H
