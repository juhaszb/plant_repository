#include "plantapp.h"
#include "ui_plantapp.h"

PlantApp::PlantApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlantApp)
{
    ui->setupUi(this);
}

PlantApp::~PlantApp()
{
    delete ui;
}

