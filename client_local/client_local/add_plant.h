#ifndef ADD_PLANT_H
#define ADD_PLANT_H

#include <QDialog>

namespace Ui {
class add_plant;
}

class add_plant : public QDialog
{
    Q_OBJECT

public:
    explicit add_plant(QWidget *parent = nullptr);
    ~add_plant();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::add_plant *ui;
public:
    std::string name = "";
    int xcoord = -1;
    int ycoord = -1;
};

#endif // ADD_PLANT_H
