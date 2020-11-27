#ifndef ADD_REQUIREMENT_H
#define ADD_REQUIREMENT_H

#include <QDialog>
#include <pistache/client.h>

namespace Ui {
class add_requirement;
}

class add_requirement : public QDialog
{
    Q_OBJECT

public:
    explicit add_requirement(QWidget *parent = nullptr);
    ~add_requirement();

private:
    Ui::add_requirement *ui;
    Pistache::Http::Client client;
public:
    std::string json = "";

private slots:
    void on_buttonBox_accepted();
};

#endif // ADD_REQUIREMENT_H
