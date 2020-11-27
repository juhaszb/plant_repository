#ifndef DB_DAO_HPP
#define DB_DAO_HPP

#include <string>
#include <vector>
#include <map>
#include <string>
#include <mysql++.h>
#include "dbtables.h"

template <typename ROW_TYPE> class dao {
	mysqlpp::Connection conn;
	std::string table_name;

    public:
	explicit dao(const mysqlpp::Connection &conn) : conn{ conn }
	{
		ROW_TYPE row;
		table_name = row.table();
	}

	ROW_TYPE get(int id)
	{
		mysqlpp::Query query = conn.query();
		query << "select * from " << table_name << " where id = " << id;
		mysqlpp::StoreQueryResult res = query.store();
		if (res.num_rows() == 0)
			throw mysqlpp::BadQuery{ "The given id does not exist" };
		return res[0];
	}

	std::vector<ROW_TYPE>
	get(const std::vector<std::string> &fields,
	    const std::map<std::string, std::string> &filters)
	{
		mysqlpp::Query query = conn.query();

		query << "select ";
		for (auto it = fields.begin(); it != fields.end(); ++it) {
			if (it != fields.begin())
				query << ",";
			query << *it;
		}

		query << " from " << table_name << " where ";
		for (auto it = filters.begin(); it != filters.end(); ++it) {
			if (it != filters.begin())
				query << " and ";
			query << it->first << " = " << mysqlpp::quote
			      << it->second;
		}

		std::vector<ROW_TYPE> res;
		query.storein(res);
		return res;
	}

	std::vector<ROW_TYPE>
	get(const std::map<std::string, std::string> &filters)
	{
		return get(std::vector<std::string>{ "*" }, filters);
	}

	std::vector<ROW_TYPE> get_all_ids()
	{
		mysqlpp::Query query = conn.query();
		query << "select id from " << table_name;
		std::vector<ROW_TYPE> rows;
		query.storein(rows);
		return rows;
	}

	bool insert(const ROW_TYPE &item)
	{
		mysqlpp::Query query = conn.query();
		query.insert(item);
		return query.execute();
	}

	bool insert(const std::vector<ROW_TYPE> &items)
	{
		mysqlpp::Query query = conn.query();
		query.insert(items.begin(), items.end());
		return query.execute();
	}

	bool remove(int id)
	{
		mysqlpp::Query query = conn.query();
		query << "delete from " << table_name << " where id = " << id;
		return query.execute();
	}

	bool update(int id, const ROW_TYPE &updated)
	{
		mysqlpp::Query query = conn.query();
		query.update(ROW_TYPE{ id }, updated);
		return query.execute();
	}
};

#endif //DB_DAO_HPP
