#ifndef PLANTAPP_H
#define PLANTAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class PlantApp; }
QT_END_NAMESPACE

class PlantApp : public QMainWindow
{
    Q_OBJECT

public:
    PlantApp(QWidget *parent = nullptr);
    ~PlantApp();



private slots:
    void on_actionAdd_Plant_triggered();


private:
    Ui::PlantApp *ui;
};
#endif // PLANTAPP_H
