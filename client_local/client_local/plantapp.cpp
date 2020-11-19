#include "plantapp.h"
#include "ui_plantapp.h"
#include <QLineEdit>

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


void PlantApp::on_actionAdd_Plant_triggered()
{
      QLineEdit* line = centralWidget()->findChild<QLineEdit*> ("lineEdit");
       line->insert("sajt");
}



