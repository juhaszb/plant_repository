#include "add_plant.h"
#include "ui_add_plant.h"

#include <QMessageBox>
#include <rapidjson/rapidjson.h>

add_plant::add_plant(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::add_plant)
{
    ui->setupUi(this);
}

add_plant::~add_plant()
{
    delete ui;
}

void add_plant::on_buttonBox_accepted()
{
    if(ui->name->text() == "" || ui->xcoord->text() == "" || ui->ycoord->text() == "")
    {
        QMessageBox messageBox;
        messageBox.critical(0, "Error","All the fields must be populated");
        messageBox.setFixedSize(500,200);
        messageBox.exec();
        exit(1);
    }
    else {
         name = ui->name->text().toStdString();
         xcoord = ui->xcoord->text().toInt();
         ycoord = ui->ycoord->text().toInt();
    }
}
