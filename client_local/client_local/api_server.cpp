#include "api_server.h"
#include "ui_api_server.h"
#include "plantapp.h"

#include <iostream>

api_server::api_server(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::api_server)
{
    ui->setupUi(this);
}



api_server::~api_server()
{
    delete ui;
}


void api_server::on_buttonBox_accepted()
{
    ip  = ui->ip->text().toStdString();
    std::string port_string = ui->port->text().toStdString();
    std::cout << port_string << std::endl;
    port = std::stoi(port_string);
}

void api_server::on_buttonBox_rejected()
{
    exit(1);
}
