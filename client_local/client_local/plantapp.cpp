#include "plantapp.h"
#include "ui_plantapp.h"

#include "api_server.h"
#include "add_plant.h"
#include "add_requirement.h"
#include <QLineEdit>
#include <QTimer>
#include <iostream>
//#include <QtNetwork/qnetworkreply.h>
#include <QTableWidget>
#include <string>

#include <pistache/http.h>
#include <pistache/client.h>
#include <pistache/net.h>

#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>



PlantApp::PlantApp(std::string ip, int port, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlantApp)
{

    this->ip = ip;
    this->port = std::to_string(port);


    QTimer * timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update_component()));
    timer->start(5000);

    auto opts = Pistache::Http::Client::options().threads(1).maxConnectionsPerHost(8);
    client.init(opts);




    ui->setupUi(this);

    QTableWidget * tw = centralWidget()->findChild<QTableWidget*> ("sensor_data");
    tw->setColumnCount(3);
    QStringList header;
    header << "ID" << "Sensor name" << "Sensor data";
    tw->setHorizontalHeaderLabels(header);

    QTableWidget * pw = centralWidget()->findChild<QTableWidget*> ("plant_data");
    pw->setColumnCount(4);

    QTableWidget * rw = centralWidget()->findChild<QTableWidget*> ("requirements_data");
    rw->setColumnCount(5);

    //Get all plants
    populate_plants();
    populate_requirements();

}


void PlantApp::populate_plants(void)
{


    std::string url = "http://" + this->ip  +":" + this->port + "/list_plants/";
    auto resp = client.get(url).send();
    resp.then([&](Pistache::Http::Response response)
    {
        std::string json = response.body();
        rapidjson::Document d;
        rapidjson::StringStream s(json.c_str());
        d.ParseStream(s);

        rapidjson::Value v(rapidjson::kArrayType);
        v = d["plants"];

        QTableWidget * tw = centralWidget()->findChild<QTableWidget*> ("plant_data");
        tw->clear();
        tw->setRowCount(v.GetArray().Size());

        tw->setColumnCount(4);
        QStringList header;
        header << "ID" << "Name" << "X" << "Y";
        tw->setHorizontalHeaderLabels(header);


        int row = 0;
        for ( auto & value : v.GetArray())
        {
            int column = 0;
            for ( auto & values : value.GetObject())
            {
                std::cout<< values.name.GetString() <<"Value is:";
                if ( values.value.IsString())
                {
                    tw->model()->setData(QModelIndex(tw->model()->index(row,column++)),values.value.GetString());
                    std::cout<< values.value.GetString();

                }
                else if( values.value.IsInt())
                {
                    tw->model()->setData(QModelIndex(tw->model()->index(row,column++)),values.value.GetInt());
                    std::cout << values.value.GetInt();
                }
                std::cout<<std::endl;
            }
            row++;

        }

    },[&](std::exception_ptr exc)
    {
        ;
    });
}


void PlantApp::populate_requirements(void)
{
    std::string url = "http://" + this->ip  +":" + this->port + "/list_requirements/";
    auto resp = client.get(url).send();
    resp.then([&](Pistache::Http::Response response)
    {
        std::string json = response.body();
        rapidjson::Document d;
        rapidjson::StringStream s(json.c_str());
        d.ParseStream(s);

        rapidjson::Value v(rapidjson::kArrayType);
        v = d["requirements"];

        QTableWidget * tw = centralWidget()->findChild<QTableWidget*> ("requirements_data");
        tw->clear();
        tw->setRowCount(v.GetArray().Size());

        tw->setColumnCount(5);
        QStringList header;
        header << "ID" << "Plant ID" << "Sensor ID" << "Min Value" << "Max Value";
        tw->setHorizontalHeaderLabels(header);


        int row = 0;
        for ( auto & value : v.GetArray())
        {
            int column = 0;
            for ( auto & values : value.GetObject())
            {
                std::cout<< values.name.GetString() <<"Value is:";
                if ( values.value.IsString())
                {
                    tw->model()->setData(QModelIndex(tw->model()->index(row,column++)),values.value.GetString());
                    std::cout<< values.value.GetString();

                }
                else if( values.value.IsInt())
                {
                    tw->model()->setData(QModelIndex(tw->model()->index(row,column++)),values.value.GetInt());
                    std::cout << values.value.GetInt();
                }
                std::cout<<std::endl;
            }
            row++;

        }

    },[&](std::exception_ptr exc)
    {
        ;
    });
}


PlantApp::~PlantApp()
{
    delete ui;
}


void PlantApp::update_component()
{
    std::string url = "http://" + ip + ":" + port +"/list_sensors/";
    auto resp = client.get(url).send();

    resp.then(
    [&](Pistache::Http::Response response)
    {
        std::string json =response.body();
        rapidjson::Document d;
        rapidjson::StringStream s(json.c_str());
        d.ParseStream(s);

        rapidjson::Value v(rapidjson::kArrayType);
        v = d["sensors"];

        QTableWidget * tw = centralWidget()->findChild<QTableWidget*> ("sensor_data");
        tw->clear();
        tw->setRowCount(v.GetArray().Size());

        tw->setColumnCount(3);
        QStringList header;
        header << "ID" << "Sensor name" << "Sensor data";
        tw->setHorizontalHeaderLabels(header);

        int row = 0;
        for (auto& value : v.GetArray())
        {
            rapidjson::Value id(rapidjson::kNumberType);
            rapidjson::Value name(rapidjson::kStringType);
            rapidjson::Value val(rapidjson::kNumberType);

            id = value["id"];
            name = value["name"];
            val = value["data"];

            QModelIndex id_index = tw->model()->index(row, 0);
            QModelIndex name_index = tw->model()->index(row, 1);
            QModelIndex data_index = tw->model()->index(row, 2);

            tw->model()->setData(id_index, id.GetInt());
            tw->model()->setData(name_index, name.GetString());
            tw->model()->setData(data_index, val.GetInt());
            row++;

        }
    },[&](std::exception_ptr exc)
    {
        std::cout<< "exception happened" << std::endl;
    });





}

void PlantApp::on_actionAdd_Plant_triggered()
{

    add_plant p;
    p.exec();

    if(p.name != "" || p.xcoord != -1 || p.ycoord != -1)
    {
        rapidjson::Document d;
        d.SetObject();
        d.AddMember("name", rapidjson::StringRef(p.name.c_str()),d.GetAllocator());
        d.AddMember("xcoord", p.xcoord, d.GetAllocator());
        d.AddMember("ycoord", p.ycoord, d.GetAllocator());

        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        d.Accept(writer);



        std::string url = "http://" + ip + ":" + port +"/add_plant/";
        std::string json = buffer.GetString();
        auto resp = client.put(url).body(json).send();
        resp.then([&](Pistache::Http::Response response)
        {
            std::cout<< response.code() <<std::endl;
            std::cout<< response.body()<<std::endl;
            populate_plants();
        }, [&] (std::exception_ptr exc)
        {
            try {
                std::rethrow_exception(exc);
            }  catch (const Pistache::Error& e) {
                std::cerr << e.what();
            }
           std::cout<<"Exception happened" << std::endl;
        }
        );
    }


}






void PlantApp::on_actionRequirement_triggered()
{
    std::string url = "http://" + ip + ":" + port + "/add_requirements/";
    add_requirement req;
    req.exec();
    if( req.json != "")
    {
           auto resp = client.put(url).body(req.json).send();
           while(!resp.isFulfilled())
           {
               ;
           }
           populate_requirements();
    }
}
