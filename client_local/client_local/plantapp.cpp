#include "plantapp.h"
#include "ui_plantapp.h"
#include "ui_control_actor.h"
#include "api_server.h"
#include "dialog.h"
#include <QLineEdit>
#include <QTimer>
#include <iostream>
#include <QtNetwork/qnetworkreply.h>
#include <QTableWidget>

#include <pistache/http.h>
#include <pistache/client.h>
#include <pistache/net.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>



PlantApp::PlantApp(std::string ip, int port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlantApp)
{
    //QDialog * qdialog = new QDialog();
   // api_server * api_server = new class api_server(this);
   // api_server->show();


    manager = new QNetworkAccessManager();
    connect(manager, &QNetworkAccessManager::finished, this, &PlantApp::network_message);

    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_component()));
    timer->start(1000);



    ui->setupUi(this);

    QTableWidget * tw = centralWidget()->findChild<QTableWidget*> ("sensor_data");



}



PlantApp::~PlantApp()
{
    delete ui;
}


void PlantApp::update_component()
{

    QNetworkRequest request(QUrl("http://192.168.2.152:11111/list_sensors/"));
    manager->get(request);

}

void PlantApp::on_actionAdd_Plant_triggered()
{
      QLineEdit* line = centralWidget()->findChild<QLineEdit*> ("lineEdit");
       line->insert("sajt");
}

void PlantApp::network_message(QNetworkReply * reply)
{
    if(reply->error())
    {
        qDebug() << reply->errorString();
    }
    else
    {
        std::string json = reply->readAll().toStdString();
        rapidjson::Document d;
        rapidjson::StringStream s(json.c_str());
        d.ParseStream(s);

        rapidjson::Value v(rapidjson::kArrayType);
        v = d["sensors"];

        for (auto& value : v.GetArray())
        {
            for ( auto & values : value.GetObject())
            {
                std::cout<< values.name.GetString() <<"Value is:";
                if ( values.value.IsString())
                    std::cout<< values.value.GetString();
                else if( values.value.IsInt())
                    std::cout << values.value.GetInt();
                std::cout<<std::endl;
            }
        }


        //QString answer = reply->readAll();
        //qDebug() << answer;
    }
}




void PlantApp::on_actionActor_triggered()
{
    QDialog * d = new QDialog();
Ui::Dialog * dialog = new Ui::Dialog;
dialog->setupUi(d);
d->show();
}
