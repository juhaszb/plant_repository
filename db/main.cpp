#define EXPAND_SSQLS_STATICS

#include <iostream>
#include <vector>
#include <mysql++.h>
#include "dbtables.h"
#include "dao.hpp"

int main() {
    mysqlpp::Connection conn;

    if (conn.connect("plantdb", "vm.fured.cloud.bme.hu", "plant", "verysecurepassword", 18719)) {
        dao<sensor> sensor_dao{conn};

        std::vector<sensor> rows = sensor_dao.get(
                {"id", "name"},
                {
                        {"name", "cekla"},
                        {"id",   "4"}
                }
        );

        std::cout << rows[0].name << rows[0].id << std::endl;

        std::vector<sensor> all = sensor_dao.get_all_ids();
        for (const auto &h : all) {
            sensor row = sensor_dao.get(h.id);
            std::cout << row.id << ". " << row.name << std::endl;
        }
    }
}