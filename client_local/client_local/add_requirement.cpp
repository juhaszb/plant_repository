#include "add_requirement.h"
#include "ui_add_requirement.h"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <pistache/net.h>
#include <pistache/http.h>
#include <pistache/client.h>

add_requirement::add_requirement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_requirement)
{
    ui->setupUi(this);
}

add_requirement::~add_requirement()
{
    delete ui;
}

void add_requirement::on_buttonBox_accepted()
{
    rapidjson::Document d;
    d.SetObject();
    d.AddMember("plant_id", ui->plant_id->text().toInt(),d.GetAllocator());
    d.AddMember("sensor_id", ui->sensor_id->text().toInt(), d.GetAllocator());
    d.AddMember("min_value", ui->min_value->text().toInt(), d.GetAllocator());
    d.AddMember("max_value", ui->max_value->text().toInt(), d.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    d.Accept(writer);

    json = buffer.GetString();
}
