#ifndef API_SERVER_H
#define API_SERVER_H

#include <QDialog>
#include "plantapp.h"

namespace Ui {
class api_server;
}

class api_server : public QDialog
{
    Q_OBJECT

public:
    explicit api_server(QWidget *parent = nullptr);
    ~api_server();



private slots:
    void on_buttonBox_accepted();

private:
    Ui::api_server *ui;
    PlantApp * p;
public:
    std::string ip= "127.0.0.1";
    int port = 6666;
};

#endif // API_SERVER_H
