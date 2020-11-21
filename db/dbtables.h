#ifndef PLANT_REPOSITORY_DBTABLES_H
#define PLANT_REPOSITORY_DBTABLES_H

#if !defined(EXPAND_SSQLS_STATICS)
#define MYSQLPP_SSQLS_NO_STATICS
#endif

#include <mysql++.h>
#include <ssqls.h>

sql_create_2(sensor, 1, 2,
             mysqlpp::sql_int, id,
             mysqlpp::sql_varchar, name)

sql_create_4(sensor_data, 1, 4,
             mysqlpp::sql_int, id,
             mysqlpp::sql_int, sensor_id,
             mysqlpp::sql_int, timestamp,
             mysqlpp::sql_int, data)

sql_create_3(actor, 1, 3,
             mysqlpp::sql_int, id,
             mysqlpp::sql_varchar, name,
             mysqlpp::sql_int, sensor_id)

sql_create_4(plant, 1, 4,
             mysqlpp::sql_int, id,
             mysqlpp::sql_varchar, name,
             mysqlpp::sql_int, gridx,
             mysqlpp::sql_int, gridy)

sql_create_5(requirement, 1, 5,
             mysqlpp::sql_int, id,
             mysqlpp::sql_int, plant_id,
             mysqlpp::sql_int, sensor_id,
             mysqlpp::sql_int, min_value,
             mysqlpp::sql_int, max_value)

#endif //PLANT_REPOSITORY_DBTABLES_H
